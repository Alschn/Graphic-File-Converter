#include "bmp_file.h"
#include <iostream>
#include "bpp1.h"
#include "image.h"
#include "utils.h"

std::vector<uint8_t> BmpFile::generateHeader(ImageContent* content) const
{
	const auto color_table_size = content->colorPaletteSize();
	const auto content_size = content->getHeight() * (content->bmpRowSize() + content->bmpPadding());
	const auto buffer_size = this->HEADER_SIZE + color_table_size;
	const auto color_table = content->colorPalette();

	
	std::vector<uint8_t> header;
	header.resize(this->HEADER_SIZE);
	header[0]='B';
	header[1]='M';

	Utils::writeIntToCharBufffer(header, this->HEADER_SIZE + color_table_size + content_size, 2);
	Utils::writeIntToCharBufffer(header, 0, 6); //not used space
	Utils::writeIntToCharBufffer(header, this->HEADER_SIZE + color_table_size, 10);//pixel content offset
	Utils::writeIntToCharBufffer(header, this->WINDOWS_HEADER_SIZE, 14); //header size
	Utils::writeIntToCharBufffer(header, content->getWidth(), 18); // image's height
	Utils::writeIntToCharBufffer(header, content->getHeight(), 22); // image's width
	Utils::writeIntToCharBufffer(header, 1, 26); //planes - has to be exactly one
	Utils::writeIntToCharBufffer(header, static_cast<int>(content->getContentType()), 28); //bpp
	Utils::writeIntToCharBufffer(header, 0, 30); //compression - not important and not used
	Utils::writeIntToCharBufffer(header, 0, 34); //real size for compression - same as above
	Utils::writeIntToCharBufffer(header, this->H_RES, 38); //horizontal res (pixel per inch) - not really important
	Utils::writeIntToCharBufffer(header, this->V_RES, 42); // vertical res (pixel per inch)
	Utils::writeIntToCharBufffer(header, 0, 46); //color palette
	Utils::writeIntToCharBufffer(header, 0, 50); //important colors

	 if (color_table_size != 0)
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
	const std::string bpp_type = "Bpp" + std::to_string(bpp);

	this->content = Image::type_map[bpp_type];
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
	std::vector<char> input;
	input.resize(54);
	memcpy(input.data(), header_buffer, 54);
	this->readHeader(header_buffer);
	delete[] header_buffer;

	char* pixel_array_buffer = new char[this->file_size - this->HEADER_SIZE];
	pixel_array_buffer = BmpFile::readBytesFromFile(filename, pixel_array_buffer, this->file_size - this->HEADER_SIZE,
	                                                this->pixel_array_offset);
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

BmpFile::~BmpFile()
{
	delete this->content;
}
