#include "image.h"
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
#include "utils.h"
#include <sys/stat.h>

void Image::getPixel(int x, int y, unsigned char output[], PixelMode mode) const
{
	if (mode == PixelMode::RGB)
	{
		for (int i = 0; i < 3; ++i)
		{
			const auto index = this->calculatePixelIndex(x, y, i);
			output[i] = this->content[index];
		}
	}
	else if (mode == PixelMode::BGR)
	{
		for (int i = 0; i < 3; ++i)
		{
			const auto index = this->calculatePixelIndex(x, y, i);
			output[2 - i] = this->content[index];
		}
	}
	else if (mode == PixelMode::MONOBW)
	{
		//to be implemented
	}
}

void Image::putPixel(int x, int y, unsigned char input[], PixelMode mode)
{
	for (int i = 0; i < 3; ++i)
	{
		auto index = this->calculatePixelIndex(x, y, i);
		this->content[index] = input[i];
	}
}


/*
 *This method is for 1bpp mode. Cannot be used with another modes. 
 */
void Image::putPixel(int x, int y, bool output)
{
	//to be implemented
}


void Image::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	this->buffer_size = Image::bufferSize(this->BYTES_PER_PIXEL, this->width, this->height);
	this->content = new unsigned char[this->buffer_size];
	this->row_size = Image::rowSize(this->width, this->BYTES_PER_PIXEL);
}

size_t Image::bufferSize(const unsigned bytes_per_pixel, const unsigned width, const unsigned height)
{
	return bytes_per_pixel * width * height;
}

unsigned Image::rowSize(const unsigned width, const unsigned bytes_per_pixel)
{
	return (width * bytes_per_pixel + 3) & ~3;
}

unsigned Image::rowPadding(const unsigned width, const unsigned bytes_per_pixel)
{
	const auto row_size = Image::rowSize(width, bytes_per_pixel);
	return row_size - width * bytes_per_pixel;
}

int Image::calculatePixelIndex(int x, int y, int color) const
{
	switch (this->depth)
	{
	case ColorDepth::bpp24:
		return this->width * 3 * y + x * 3 + color;

	default:
		return this->width * 3 * y + x * 3 + color;
	}
}

void Image::save(const std::string& path)
{
	char buf[54];
	this->generateHeader(buf);


	std::ofstream fout;
	fout.open(path, std::ios::binary | std::ios::out);

	std::vector<char> output;
	output.reserve(this->HEADER_SIZE + this->row_size * this->height);
	output.insert(output.end(), buf, buf + this->HEADER_SIZE);
	for (int j = 0; j < this->height; ++j)
	{
		for (int i = 0; i < this->width; ++i)
		{
			unsigned char px[3];
			this->getPixel(i, j, px, PixelMode::BGR);

			for (auto c : px)
			{
				output.emplace_back(c);
			}
		}
		for (int i = 0; i < (this->row_size - this->width * this->BYTES_PER_PIXEL); ++i)
		{
			output.push_back(0);
		}
	}
	fout.write(output.data(), output.size());
}

std::string Image::toStr() const
{
	std::string output;

	for (int i = height - 1; i > 0; --i)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned char arr[3];
			getPixel(j, i, arr, PixelMode::RGB);
			if (arr[0] > 0)
			{
				output.append("R");
			}
			else if (arr[1] > 0)
			{
				output.append("G");
			}
			if (arr[2] > 0)
			{
				output.append("B");
			}
		}
		output.append("\n");
	}

	return output;
}

bool Image::fileExists(const std::string& path)
{
	struct stat buffer{};
	return stat(path.c_str(), &buffer) == 0;
}

void Image::loadFromFile()
{
	char* header_buffer = new char [this->HEADER_SIZE];
	header_buffer = Image::readBytesFromFile(this->path, header_buffer, this->HEADER_SIZE);
	this->readHeader(header_buffer);
	delete[] header_buffer;

	char* pixel_array_buffer = new char[this->file_size - this->HEADER_SIZE];
	pixel_array_buffer = Image::readBytesFromFile(this->path, pixel_array_buffer, this->file_size - this->HEADER_SIZE,
	                                              this->pixel_array_offset);
	this->readPixelArray(pixel_array_buffer);
	delete[] pixel_array_buffer;
}

void Image::readHeader(const char* buffer)
{
	const auto sig_0 = buffer[0];
	const auto sig_1 = buffer[1];

	if (sig_0 != 'B' || sig_1 != 'M')
		throw std::runtime_error("BMP signature is not valid!");

	this->file_size = Utils::fourCharsToInt(buffer, this->FILE_SIZE_OFFSET);
	this->width = Utils::fourCharsToInt(buffer, this->WIDTH_OFFSET);
	this->height = Utils::fourCharsToInt(buffer, this->HEIGHT_OFFSET);

	this->pixel_array_offset = Utils::fourCharsToInt(buffer, this->PIXEL_ARRAY_OFFSET_INDEX);
	this->horizontal_resolution = Utils::fourCharsToInt(buffer, this->HORIZONTAL_RESOLUTION_OFFSET);
	this->vertical_resolution = Utils::fourCharsToInt(buffer, this->VERTICAL_RESOLUTION_OFFSET);
	this->row_size = Image::rowSize(this->width, this->BYTES_PER_PIXEL);
	this->buffer_size = Image::bufferSize(this->BYTES_PER_PIXEL, this->width, this->height);
}


void Image::generateHeader(char* input) const
{
	input[0] = 'B';
	input[1] = 'M';
	Utils::writeIntToCharBufffer(input, this->file_size, 2);
	Utils::writeIntToCharBufffer(input, 0, 6);
	Utils::writeIntToCharBufffer(input, this->pixel_array_offset, 10);
	Utils::writeIntToCharBufffer(input, 40, 14);
	Utils::writeIntToCharBufffer(input, this->width, 18);
	Utils::writeIntToCharBufffer(input, this->height, 22);
	Utils::writeIntToCharBufffer(input, 1, 26);
	Utils::writeIntToCharBufffer(input, 24, 28);
	Utils::writeIntToCharBufffer(input, 0, 30);
	Utils::writeIntToCharBufffer(input, 0, 34);
	Utils::writeIntToCharBufffer(input, this->horizontal_resolution, 38);
	Utils::writeIntToCharBufffer(input, this->vertical_resolution, 42);
	Utils::writeIntToCharBufffer(input, 0, 46);
	Utils::writeIntToCharBufffer(input, 0, 50);
}

char* Image::readBytesFromFile(const std::string& file_path, char* buffer, size_t size, const unsigned int offset)
{
	std::ifstream file(file_path, std::ios_base::binary);
	file.seekg(offset);
	file.read(buffer, size);
	file.close();
	return buffer;
}

void Image::readPixelArray(const char* buffer)
{
	this->content = new unsigned char[this->buffer_size];
	for (int j = 0; j < this->height; ++j)
	{
		for (int i = 0; i < this->width; ++i)
		{
			const unsigned int offset = i * 3 + j * this->row_size;
			this->content[this->calculatePixelIndex(i, j, 0)] = buffer[offset + 2]; // save R
			this->content[this->calculatePixelIndex(i, j, 1)] = buffer[offset + 1]; // save G
			this->content[this->calculatePixelIndex(i, j, 2)] = buffer[offset]; // save B
		}
	}
}

Image::Image(const std::string& path, const bool expect_saving, const ImageMode& m,
             const ColorDepth& depth) : path(path), mode(m), depth(depth)
{
	if (!Image::fileExists(path))
	{
		throw std::exception("Image with specified input path does not exist!");
	}

	this->loadFromFile(); // to be changed
}

Image::Image(const Image& other) : mode(other.mode), depth(other.depth)
{
#ifdef _DEBUG
	std::cout << "Inside copy constructor of class Image" << std::endl;
#endif


	this->width = other.width;
	this->height = other.height;
	this->buffer_size = other.buffer_size;
	this->row_size = other.row_size;
	this->pixel_array_offset = other.pixel_array_offset;

	this->file_size = other.file_size;
	this->content = new unsigned char[other.buffer_size];
}

Image::~Image()
{
	delete[] this->content;
}

std::ostream& operator<<(std::ostream& os, const Image& im)
{
	os << im.toStr();
	return os;
}

std::istream& operator>>(std::istream& is, Image& im)
{
	char* header = new char[im.HEADER_SIZE];
	is.read(header, im.HEADER_SIZE);
	im.readHeader(header);
	delete[] header;

	is.seekg(im.HEADER_SIZE);

	char* pixel_array_buffer = new char[im.file_size - im.HEADER_SIZE];
	is.read(pixel_array_buffer, im.file_size - im.HEADER_SIZE);
	im.readPixelArray(pixel_array_buffer);
	delete[] pixel_array_buffer;

	return is;
}
