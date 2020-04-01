#include "image.h"
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

void Image::replacePixel(int x, int y, const char pixel[3])
{
}

void Image::getPixel(int x, int y, unsigned char (&output)[3])
{
	for (int i = 0; i < 3; ++i)
	{
		auto index = this->calculatePixelIndex(x, y, i);
		output[i] = this->content[index];
	}
}

void Image::putPixel(int x, int y, unsigned char (& input)[3])
{
	for (int i = 0; i < 3; ++i)
	{
		auto index = this->calculatePixelIndex(x, y, i);
		this->content[index] = input[i];
	}
}

void Image::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	this->setBufferSize();
	this->content = new unsigned char[this->buffer_size];
	this->calculateRowSize();
}

void Image::setBufferSize()
{
	this->buffer_size = this->BYTES_PER_PIXEL * this->width * this->height;
}



unsigned Image::calculateRowSize()
{
	const int bytes_per_pixel = 3;
	this->row_size = (this->width * bytes_per_pixel + 3) & ~3;
	return this->row_size;
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

std::string Image::to_str()
{
	std::string output;

	for (int i = height - 1; i > 0; --i)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned char arr[3];
			getPixel(j, i, arr);
			if (arr[0] > 0)
			{
				output.append("R");
			}
			else if (arr[1] > 0)
			{
				output.append("B");
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

void Image::load(bool expect_saving)
{
	std::ifstream infile(this->path, std::ios_base::binary);

	std::vector<unsigned char> buffer{
		std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>()
	};

	//check if signature is valid
	const auto sig_0 = buffer.at(0);
	const auto sig_1 = buffer.at(1);

	if (sig_0 != 'B' || sig_1 != 'M')
		throw std::runtime_error("BMP signature is not valid!");

	//initialize necessary values
	this->file_size = Utils::fourCharsToInt(buffer, FILE_SIZE_OFFSET);
	this->width = Utils::fourCharsToInt(buffer, WIDTH_OFFSET);
	this->height = Utils::fourCharsToInt(buffer, HEIGHT_OFFSET);

	if (expect_saving)
	{
		std::copy(buffer.begin(), buffer.begin() + this->HEADER_SIZE, this->header);
	}

	const auto offset = Utils::fourCharsToInt(buffer, PIXEL_ARRAY_OFFSET);
	const auto row_size = (width * 3 + 3) & ~3;
	if (this->depth == ColorDepth::bpp24)
	{
		this->buffer_size = this->height * this->width * 3;
	}

	this->content = new unsigned char[this->buffer_size];

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			const unsigned int bmp_real_offset = i * 3 + offset + j * row_size;
			this->content[this->calculatePixelIndex(j, i, 0)] = buffer.at(bmp_real_offset + 2); // save R
			this->content[this->calculatePixelIndex(j, i, 1)] = buffer.at(bmp_real_offset + 1); // save G
			this->content[this->calculatePixelIndex(j, i, 2)] = buffer.at(bmp_real_offset);				 // save B
		}
	}
}
