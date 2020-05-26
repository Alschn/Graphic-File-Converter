//Created by Gustaw Daczkowski
#include "bmp_file.h"
#include <iostream>
#include "../image_content/bpp1.h"
#include "../image.h"
#include "../utils.h"
#include "../font.h"
#include <fstream>


std::vector<uint8_t> BmpFile::generateHeader(ImageContent* content) const
{
	const auto color_table = content->colorPalette();
	const auto color_table_size = color_table.size();
	const auto content_size = content->getHeight() * (content->bmpRowSize() + content->bmpPadding());
	const auto buffer_size = this->HEADER_SIZE + color_table_size;

	std::vector<uint8_t> header;
	header.resize(this->HEADER_SIZE);
	header[0]='B'; //signature
	header[1]='M'; //signature

	Utils::writeIntToCharBuffer(header, this->HEADER_SIZE + color_table_size + content_size, 2);
	Utils::writeIntToCharBuffer(header, 0, 6); //not used space
	Utils::writeIntToCharBuffer(header, this->HEADER_SIZE + color_table_size, 10);//pixel content offset
	Utils::writeIntToCharBuffer(header, this->WINDOWS_HEADER_SIZE, 14); //header size
	Utils::writeIntToCharBuffer(header, content->getWidth(), 18); // image's height
	Utils::writeIntToCharBuffer(header, content->getHeight(), 22); // image's width
	Utils::writeIntToCharBuffer(header, 1, 26); //planes - has to be exactly one
	Utils::writeIntToCharBuffer(header, content->getType(), 28); //bpp
	Utils::writeIntToCharBuffer(header, 0, 30); //compression - not important and not used
	Utils::writeIntToCharBuffer(header, 0, 34); //real size for compression - same as above
	Utils::writeIntToCharBuffer(header, this->H_RES, 38); //horizontal res (pixel per inch) - not really important
	Utils::writeIntToCharBuffer(header, this->V_RES, 42); // vertical res (pixel per inch)
	Utils::writeIntToCharBuffer(header, 0, 46); //color palette
	Utils::writeIntToCharBuffer(header, 0, 50); //important colors

	 if (color_table_size != 0) //color table
		header.insert(header.end(), color_table.data(), color_table.data() + color_table_size);
	return header;
}

void BmpFile::readHeader(char* buffer)
{
	const auto sig_0 = buffer[0];
	const auto sig_1 = buffer[1];

	if (sig_0 != 'B' || sig_1 != 'M')
		throw std::runtime_error("BMP signature is not valid!");

	this->file_size = Utils::fourCharsToInt(buffer, this->FILE_SIZE_OFFSET);
	const auto width = Utils::fourCharsToInt(buffer, this->WIDTH_OFFSET);
	const auto height = Utils::fourCharsToInt(buffer, this->HEIGHT_OFFSET);

	this->pixel_array_offset = Utils::fourCharsToInt(buffer, this->PIXEL_ARRAY_OFFSET);
	const auto bpp = buffer[this->BPP_OFFSET];

	this->content = Image::content_type_map[(bpp)]();
	this->content->resize(width, height);
}

void BmpFile::readPixelArray(char* pixel_array_buffer) const
{
	this->content->readFromBmpMemory(reinterpret_cast<uint8_t*>(pixel_array_buffer));
}

ImageContent* BmpFile::loadForContent(const std::string& filename)
{
	char* header_buffer = new char[this->HEADER_SIZE];
	header_buffer = File::readBytesFromFile(filename, header_buffer, this->HEADER_SIZE);
	this->readHeader(header_buffer);
	delete[] header_buffer;

	char* pixel_array_buffer = new char[this->file_size - this->HEADER_SIZE];
	pixel_array_buffer = File::readBytesFromFile(filename, pixel_array_buffer, this->file_size - this->HEADER_SIZE, this->pixel_array_offset);
	this->readPixelArray(pixel_array_buffer);
	delete[] pixel_array_buffer;

	return this->content;
}

void BmpFile::save(ImageContent* content, const std::string& path)
{
	std::ofstream file_out;
	file_out.open(path, std::ios::binary | std::ios::out);
	auto header = this->generateHeader(content);
	auto byte_content = content->bmpContent();
	file_out.write(reinterpret_cast<char*>(header.data()), header.size());
	file_out.write(reinterpret_cast<char*>(byte_content.data()), byte_content.size());
	file_out.close();
}

void BmpFile::saveFont(std::vector<Image*> char_images, std::string& path)
{
	const auto font_name = Font::extractFontName(path);
	File::directoryExists(path); //throws an exception if path does not exist
	const auto path_to_save = path + font_name + "_";
	Font::generateAlphabet();
	for (unsigned int i = 0; i < char_images.size(); ++i)
	{
		char_images.at(i)->save(path_to_save + std::string(1, Font::alphabet[i]) + ".bmp");
	}
}

BmpFile::~BmpFile()
{
	delete this->content;
}
