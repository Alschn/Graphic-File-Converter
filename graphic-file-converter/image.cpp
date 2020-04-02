#include "image.h"
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

void Image::replacePixel(int x, int y, const char pixel[3])
{
}

void Image::getPixel(int x, int y, unsigned char (&output)[3], PixelMode mode) const
{
	if (mode == PixelMode::RGB)
	{
		for (int i = 0; i < 3; ++i)
		{
			auto index = this->calculatePixelIndex(x, y, i);
			output[i] = this->content[index];
		}
	}
	else if (mode == PixelMode::BGR)
	{
		for (int i = 0; i < 3; ++i)
		{
			auto index = this->calculatePixelIndex(x, y, i);
			output[2 - i] = this->content[index];
		}
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

void Image::save(const std::string& path)
{
	if (!this->save_header)
		throw std::runtime_error("Cannot save image without preserved header");


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

			for (auto c:px)
			{
				output.push_back(c);
			}
		}
		for(int i = 0; i< (this->row_size-this->width*this->BYTES_PER_PIXEL); ++i)
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

void Image::load()
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

	if (this->save_header)
	{
		std::copy(buffer.begin(), buffer.begin() + this->HEADER_SIZE, this->header);
	}

	const auto offset = Utils::fourCharsToInt(buffer, PIXEL_ARRAY_OFFSET);
	this->calculateRowSize();
	this->setBufferSize();
	

	this->content = new unsigned char[this->buffer_size];

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			const unsigned int bmp_real_offset = i * 3 + offset + j * this->row_size;
			this->content[this->calculatePixelIndex(i, j, 0)] = buffer.at(bmp_real_offset + 2); // save R
			this->content[this->calculatePixelIndex(i, j, 1)] = buffer.at(bmp_real_offset + 1); // save G
			this->content[this->calculatePixelIndex(i, j, 2)] = buffer.at(bmp_real_offset);				  // save B
		}
	}
}

Image::Image(const std::string& path, const bool expect_saving, const ImageMode& m,
             const ColorDepth& depth): path(path), mode(m), depth(depth), save_header(expect_saving)
{
	if (this->save_header)
	{
		this->header = new unsigned char[this->HEADER_SIZE];
	}


	this->load();
}

Image::Image(const Image& other): mode(other.mode), depth(other.depth)
{
	this->width = other.width;
	this->height = other.height;
	this->buffer_size = other.buffer_size;
	this->row_size = other.row_size;

	
	this->save_header = other.save_header;
	this->file_size = other.file_size;
	this->header = new unsigned char[other.HEADER_SIZE];
	memcpy(this->header, other.header, this->HEADER_SIZE);
	this->content = new unsigned char[other.buffer_size];

}

std::ostream& operator<<(std::ostream& os, const Image& im)
{
	os << im.toStr();
	return os;
}
