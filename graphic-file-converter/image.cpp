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
	output.insert(output.end(), this->header, this->header + this->HEADER_SIZE);
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
	pixel_array_buffer = Image::readBytesFromFile(this->path, pixel_array_buffer, sizeof(pixel_array_buffer), this->pixel_array_offset);
	this->readPixelArray(pixel_array_buffer);
	delete[] pixel_array_buffer;
}

void Image::readHeader(const char* buffer)
{
	const auto sig_0 = buffer[0];
	const auto sig_1 = buffer[1];

	char buf[54];

	memcpy(buf, buffer, 54);
	
	if (sig_0 != 'B' || sig_1 != 'M')
		throw std::runtime_error("BMP signature is not valid!");

	this->file_size = Utils::fourCharsToInt(buffer, this->FILE_SIZE_OFFSET);
	this->width = Utils::fourCharsToInt(buffer, this->WIDTH_OFFSET);
	this->height = Utils::fourCharsToInt(buffer, this->HEIGHT_OFFSET);

	this->pixel_array_offset = Utils::fourCharsToInt(buffer, PIXEL_ARRAY_OFFSET_INDEX);
	this->row_size = Image::rowSize(this->width, this->BYTES_PER_PIXEL);
	this->buffer_size = Image::bufferSize(this->BYTES_PER_PIXEL, this->width, this->height);
}


void Image::generateHeader(char *input2)
{
	char input[54];
	input[0] = 'B';
	input[1] = 'M';
	Utils::writeIntToCharBufffer(input, this->file_size, 2);
	Utils::writeIntToCharBufffer(input, 0, 6);
	Utils::writeIntToCharBufffer(input, this->pixel_array_offset, 10);
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
			this->content[this->calculatePixelIndex(i, j, 0)] = buffer[offset + 2];  // save R
			this->content[this->calculatePixelIndex(i, j, 1)] = buffer[offset + 1];  // save G
			this->content[this->calculatePixelIndex(i, j, 2)] = buffer[offset];		  // save B
		}
	}
}

Image::Image(const std::string& path, const bool expect_saving, const ImageMode& m,
             const ColorDepth& depth) : path(path), mode(m), depth(depth), save_header(expect_saving)
{
	if (!Image::fileExists(path))
	{
		throw std::exception("Image with specified input path does not exist!");
	}

	if (this->save_header)
	{
		this->header = new unsigned char[this->HEADER_SIZE];
	}

	this->loadFromFile();
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

	this->save_header = other.save_header;
	this->file_size = other.file_size;
	this->header = new unsigned char[other.HEADER_SIZE];
	memcpy(this->header, other.header, this->HEADER_SIZE * 1);
	this->content = new unsigned char[other.buffer_size];
}

Image::~Image()
{
	delete[] this->header;
	delete[] this->content;
}

std::ostream& operator<<(std::ostream& os, const Image& im)
{
	os << im.toStr();
	return os;
}
