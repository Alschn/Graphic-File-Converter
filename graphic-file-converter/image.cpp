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
	struct stat buffer;
	return stat(path.c_str(), &buffer) == 0;
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
	this->row_size = Image::rowSize(this->width, this->BYTES_PER_PIXEL);
	this->buffer_size = Image::bufferSize(this->BYTES_PER_PIXEL, this->width, this->height);

	this->content = new unsigned char[this->buffer_size];

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			const unsigned int bmp_real_offset = i * 3 + offset + j * this->row_size;
			this->content[this->calculatePixelIndex(i, j, 0)] = buffer.at(bmp_real_offset + 2); // save R
			this->content[this->calculatePixelIndex(i, j, 1)] = buffer.at(bmp_real_offset + 1); // save G
			this->content[this->calculatePixelIndex(i, j, 2)] = buffer.at(bmp_real_offset); // save B
		}
	}
}


void Image::generateHeader(const uint8_t(& input)[])
{
	// to be implemented
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

	this->load();
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

Image::Image()
{

}