#include "header_file.h"
#include <fstream>
#include "image.h"
#include "bpp1.h"

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

	for (int i = 0; i<hght; ++i)
	{
		auto line = lines.at(start_index - i);
		auto words = Utils::splitString(line, ',');
		for (auto w:words)
		{
			if(w.find("//")==std::string::npos)
			{
				uint8_t hex_byte = std::stoi(w, nullptr, 16);
				content->putByte(hex_byte, bytes_write_index);
				bytes_write_index++;
			}
		}
	}
	
	return content; 
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
			if (line!="  ")
			{
				output.push_back(line);
			}
		}
		file.close();
	}
	return output;
}

int HeaderFile::getLetterIndexFromFName(std::string &name)
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

