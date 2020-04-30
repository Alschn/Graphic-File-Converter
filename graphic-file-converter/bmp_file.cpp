#include "bmp_file.h"
#include <fstream>

#include "bpp1.h"
#include "utils.h"

char* BmpFile::readBytesFromFile(const std::string& file_path, char* buffer, size_t size, const unsigned offset)
{
	std::ifstream file(file_path, std::ios_base::binary);
	file.seekg(offset);
	file.read(buffer, size);
	file.close();
	return buffer;
}

ImageContent* BmpFile::loadForContent(const std::string& filename)
{
	// char* header_buffer = new char[this->HEADER_SIZE];
	// header_buffer = BmpFile::readBytesFromFile(filename, header_buffer, this->HEADER_SIZE);
	// this->readHeader(header_buffer);
	// delete[] header_buffer;
	//
	// char* pixel_array_buffer = new char[this->file_size - this->HEADER_SIZE];
	// pixel_array_buffer = BmpFile::readBytesFromFile(this->path, pixel_array_buffer, this->file_size - this->HEADER_SIZE,
	// 	this->pixel_array_offset);
	// this->readPixelArray(pixel_array_buffer);
	// delete[] pixel_array_buffer;
	//
	// const auto sig_0 = buffer[0];
	// const auto sig_1 = buffer[1];
	//
	// if (sig_0 != 'B' || sig_1 != 'M')
	// 	throw std::runtime_error("BMP signature is not valid!");
	//
	// this->file_size = Utils::fourCharsToInt(buffer, this->FILE_SIZE_OFFSET);
	// this->width = Utils::fourCharsToInt(buffer, this->WIDTH_OFFSET);
	// this->height = Utils::fourCharsToInt(buffer, this->HEIGHT_OFFSET);
	//
	// this->pixel_array_offset = Utils::fourCharsToInt(buffer, this->PIXEL_ARRAY_OFFSET_INDEX);
	// this->horizontal_resolution = Utils::fourCharsToInt(buffer, this->HORIZONTAL_RESOLUTION_OFFSET);
	// this->vertical_resolution = Utils::fourCharsToInt(buffer, this->VERTICAL_RESOLUTION_OFFSET);
	// this->row_size = Image::rowSize(this->width, this->depth);
	return new Bpp1();
}
