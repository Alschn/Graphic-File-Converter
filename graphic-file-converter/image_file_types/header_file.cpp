//Created by Gustaw Daczkowski
#include "header_file.h"
#include <fstream>
#include "../image.h"
#include "../utils.h"
#include <sstream>
#include <string>


std::string HeaderFile::generateFileInfo(ImageContent* content)
{
	std::string type = "GENERIC";
	return this->generateFileInfo(this->variable_name, content->getType(), this->variable_name, type);
}

std::string HeaderFile::generateFileInfo(std::string& font_name, int content_type, std::string& variable_name, std::string& type) const
{
	std::string output;
	auto new_name = font_name;
	for (auto& c : new_name) c = toupper(c);
	output += "#ifndef ";
	output += "_" + new_name + "_" + type;
	output += "\n";
	output += "#define _";
	output += new_name;
	output += "_" + type;
	output += "\n";
	output += "/* Bpp: ";
	output += std::to_string(content_type);
	output += "\n";
	output += " * TYPE: ";
	output += type;
	output += "\n */";
	output += "\n";
	output += "static const uint8_t ";
	output += variable_name;
	output += "[] = {\n";
	return output;
}

std::string HeaderFile::generateFileContent(ImageContent* content, unsigned char letter) const
{
	std::string output;
	const auto row_size = 8;
	output += "// ";
	if (letter != 0)
	{
		output += "Char: " + std::string(1, letter) + " | ";
	}
	output += "W: ";
	output += std::to_string(content->getWidth());
	output += " | H: ";
	output += std::to_string(content->getHeight());
	output += "\n";

	auto buf_size = content->getBufferSize();
	int counter = 0;
	const auto rows = buf_size >> 3;
	for (int j = 0; j < rows; ++j)
	{
		for (int i = 0; i < row_size; ++i)
		{
			output += "0x";
			char hex_string[4];
			auto byte = content->getByte(counter);
			sprintf_s(hex_string, "%02X", byte);
			output += hex_string;
			output += ", ";
			counter++;
		}
		output.pop_back();
		output.push_back('\n');
	}
	for (int i = 0; i < counter - buf_size; ++i)
	{
		output += "0x";
		char hex_string[4];
		auto byte = content->getByte(counter);
		sprintf_s(hex_string, "%02X", byte);
		output += hex_string;
		output += ", ";
		counter++;
	}
	output.pop_back();
	output.push_back('\n');

	return output;
}

std::string HeaderFile::pathToVariableName(const std::string& path)
{
	const auto dot_pos = path.rfind('.');
	const auto slash_pos = path.rfind('/');

	if (dot_pos == std::string::npos)
		throw std::runtime_error("Provided path is not correct. It has to have .h extension");

	const auto output = path.substr(slash_pos + 1, dot_pos - slash_pos - 1);
	if (output.size() < 3)
		throw std::runtime_error(
			"Provided path is not correct. It is too short and probably doesn't contain needed information. Proper format example arial_A.h | arial_B.h ");
	return output;
}


void HeaderFile::saveStringToFile(const std::string& content, const std::string& path)
{
	File::directoryExistsFromFile(path); //throws an exception if file does not exist
	std::ofstream out(path);
	out << content;
	out.close();
}

ImageContent* HeaderFile::loadForContent(const std::string& filename)
{
	auto resolved_path = HeaderFile::resolvePath(filename);
	if (!File::fileExists(resolved_path))
		throw std::runtime_error("File does not exist!");

	this->name = pathToVariableName(filename);;

	const auto letter_index = HeaderFile::getLetterIndexFromFName(this->name);
	auto lines = HeaderFile::fileToLines(resolved_path);
	std::string content_type, header_type;

	size_t counter = 0;

	while (counter < lines.size())
	{
		auto line = lines.at(counter);
		Utils::findMatch(line, this->image_content_type, content_type);
		Utils::findMatch(line, this->header_t, header_type);

		if (line.find("static const uint8_t") != std::string::npos)
			break;
		++counter;
	}

	if (header_type.empty() || content_type.empty())
		throw std::runtime_error("Provided header file is not valid!");

	ImageContent* content = Image::content_type_map[std::stoi(content_type)]();
	unsigned int width = 0;
	unsigned int height = 0;
	if (header_type == "FONT")
	{
		bool found = false;


		while (!found && counter < lines.size())
		{
			found = this->extractLetterInformation(lines.at(counter), letter_index, width, height);
			++counter;
		}

		if (counter == lines.size())
		{
			throw std::runtime_error("Letter not found in font file. Maybe it's corrupted");
		}
	}
	else
	{
		std::vector<std::string> output;
		output.reserve(2);
		const auto found = Utils::findMatches(lines.at(++counter), this->generic_information, output);
		if (!found)
		{
			throw std::runtime_error("Incorrect header file format. Could not read width or height of the image!");
		}
		width = std::atoi(output.at(0).c_str());
		height = std::atoi(output.at(1).c_str());
		++counter;
	}

	content->resize(width, height);


	int bytes_write_index = 0;
	while (bytes_write_index < content->getBufferSize())
	{
		auto line = lines.at(counter);
		std::vector<std::string> words = Utils::splitString(line, ',');
		for (auto w : words)
		{
			uint8_t hex_byte = std::stoi(w, nullptr, 16);
			content->putByte(hex_byte, bytes_write_index++);
		}
		++counter;
	}
	return content;
}

void HeaderFile::save(ImageContent* content, const std::string& path)
{
	this->variable_name = HeaderFile::pathToVariableName(path);
	auto file = this->generateFileInfo(content);
	file += this->generateFileContent(content);
	file += this->epilogue;
	saveStringToFile(file, path);
}


void HeaderFile::saveFont(std::vector<Image*> font, std::string& path) const
{
	File::directoryExistsFromFile(path); //throws an exception if filename is not valid
	auto var_name = pathToVariableName(path);
	std::string type = "FONT";
	std::string file;
	file += this->generateFileInfo(var_name, font.at(0)->type, var_name, type);
	int counter = 0;
	Font::generateAlphabet();
	for (auto letter : font)
	{
		file += this->generateFileContent(letter->getContent(), Font::alphabet[counter]);
		++counter;
	}
	file += this->epilogue;
	HeaderFile::saveStringToFile(file, path);
}

std::vector<std::string> HeaderFile::fileToLines(const std::string& filename)
{
	std::vector<std::string> output;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (line != "  ")
			{
				output.push_back(line);
			}
		}
		file.close();
	}
	return output;
}

unsigned char HeaderFile::getLetterIndexFromFName(std::string& name)
{
	const auto found = name.rfind('_');
	if (found != std::string::npos)
	{
		return name[found + 1];
	}
	return 0;
}

bool HeaderFile::extractLetterInformation(std::string& line, unsigned char desired_letter, unsigned& width,
                                          unsigned& height) const
{
	std::vector<std::string> output;
	output.reserve(3);
	const auto found = Utils::findMatches(line, this->letter_information, output);
	if (!found)
		return false;
	if (output.at(0).c_str()[0] != desired_letter)
		return false;
	width = std::atoi(output.at(1).c_str());
	height = std::atoi(output.at(2).c_str());
	return true;
}

std::string HeaderFile::resolvePath(const std::string& path)
{
	std::string correct_path;
	auto slash_pos = path.rfind('/');
	if (slash_pos == std::string::npos)
	{
		correct_path = "./" + path;
		slash_pos = 2;
	}
	else
	{
		correct_path = path;
	}

	const auto underscore_pos = correct_path.rfind('_');
	if (underscore_pos == std::string::npos || underscore_pos <= slash_pos)
	{
		return correct_path;
	}

	return correct_path.substr(0, underscore_pos) + ".h";
}

HeaderFile::~HeaderFile()
{
	// delete this->content;
}
