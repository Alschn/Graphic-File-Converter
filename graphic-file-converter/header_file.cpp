#include "header_file.h"
#include <fstream>
#include "image.h"
#include "bpp1.h"
#include "utils.h"
#include <sstream>

std::string HeaderFile::generateFileInfo() const
{
	std::string output;
	auto new_name = this->variable_name;
	for (auto& c : new_name) c = toupper(c);
	output += "#ifndef ";
	output += "_" + new_name + "_\n";
	output += "/*\n* RES: ";
	output += this->content->getType();
	output += "\n";
	output += "* WIDTH: ";
	output += std::to_string(this->content->getWidth());
	output += "\n";
	output += "* HEIGHT: ";
	output += std::to_string(this->content->getHeight());
	output += '\n';
	output += "* TYPE: FONT (to be implemented) \n*/";
	output += "\n";
	output += "static const uint8_t ";
	output += this->variable_name;
	output += "[] = {\n";
	return output;
}

std::string HeaderFile::generateFileContent() const
{
	std::string output;
	auto row_size = this->content->rowSize();
	if (row_size == -1)
		row_size = this->bytes_per_row;

	unsigned int byte_counter = 0;

	for (int j = this->content->getHeight()-1; j>=0;--j)
	{
		for (int i = 0; i < row_size; ++i)
		{
			output += "0x";
			char hex_string[4];
			auto byte = this->content->getByte(j*row_size + i);
			sprintf_s(hex_string, "%02X",byte);
			output += hex_string;
			output += ", ";
			byte_counter++;
		}
		output.pop_back();
		output.push_back('\n');
	}
	output.pop_back();
	output.pop_back();
	output += "\n}\n";
	output += "#endif";
	return output;
}

std::string HeaderFile::pathToVariableName(const std::string path)
{
	auto dot_pos = path.rfind('.');
	auto slash_pos = path.rfind('/');

	if (dot_pos == std::string::npos)
		throw std::runtime_error("Provided path is not correct. It has to have .h extension");


	return path.substr(slash_pos + 1, dot_pos - slash_pos -1);
}

ImageContent* HeaderFile::loadForContent(const std::string& filename)
{
	this->name = filename;
	auto letter_index = this->getLetterIndexFromFName(this->name);
	auto lines = HeaderFile::fileToLines(this->name);
	std::string content_type, width, height;

	int counter = 0;

	while (counter < lines.size())
	{
		auto line = lines.at(counter);
		Utils::findMatch(line, this->image_content_type, content_type);
		Utils::findMatch(line, this->image_content_width, width);
		Utils::findMatch(line, this->image_content_height, height);

		if (line.find("static const uint8_t") != std::string::npos)
			break;
		counter++;
	}
	const unsigned int wdth = std::atoi(width.c_str());
	const unsigned int hght = std::atoi(height.c_str());

	ImageContent* content = Image::type_map[content_type];
	content->resize(wdth, hght);


	auto start_index = counter + hght * letter_index + hght;
	int bytes_write_index = 0;

	for (int i = 0; i < hght; ++i)
	{
		auto line = lines.at(start_index - i);
		auto words = Utils::splitString(line, ',');
		for (auto w : words)
		{
			if (w.find("//") == std::string::npos)
			{
				uint8_t hex_byte = std::stoi(w, nullptr, 16);
				content->putByte(hex_byte, bytes_write_index);
				bytes_write_index++;
			}
		}
	}
	return content;
}

void HeaderFile::save(ImageContent* content, const std::string& path)
{
	auto row_size = content->rowSize();
	this->variable_name = this->pathToVariableName(path);
	this->content = content;
	auto file = this->generateFileInfo();
	file += this->generateFileContent();
	std::cout << file;
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

int HeaderFile::getLetterIndexFromFName(std::string& name)
{
	auto found = name.rfind('_');
	if (found != std::string::npos)
	{
		char to_ret = name[found + 1];
		name = name.substr(0, found);
		if (to_ret >= 'a')
			return to_ret - 'a' + 10 + 'Z' - 'A';

		if (to_ret >= 'A')
			return to_ret - 'A' + 10;

		return to_ret - '0';
	}
	return 0;
}
