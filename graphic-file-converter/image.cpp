#include "image.h"
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
#include "utils.h"
#include <sys/stat.h>

#include "bpp1.h"

void Image::getPixel(int x, int y, unsigned char output[], PixelMode mode) const
{
	if (mode == PixelMode::rgb)
	{
		for (int i = 0; i < 3; ++i)
		{
			const auto index = this->calculatePixelIndex(x, y, i);
			output[i] = this->content[index];
		}
	}
	else if (mode == PixelMode::bgr)
	{
		for (int i = 0; i < 3; ++i)
		{
			const auto index = this->calculatePixelIndex(x, y, i);
			output[2 - i] = this->content[index];
		}
	}
	else if (mode == PixelMode::mono_bw)
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


void Image::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	this->buffer_size = Image::bufferSize(this->BYTES_PER_PIXEL, this->width, this->height);
	this->content = new unsigned char[this->buffer_size];
	this->row_size = Image::rowSize(this->width, this->depth);
}

size_t Image::bufferSize(const unsigned bytes_per_pixel, const unsigned width, const unsigned height)
{
	return bytes_per_pixel * width * height;
}

unsigned Image::rowSize(const unsigned width, const ColorDepth& depth)
{
	if (depth == ColorDepth::bpp24)
		return (width * 3 + 3) & ~3;
	if (depth == ColorDepth::bpp1)
	{
		const auto new_width = width % 8 == 0 ? width >> 3 : (width >> 3) + 1;
		return (new_width + 3) & ~3;
	}
	return 0;
}

unsigned Image::rowPadding(const unsigned width, const ColorDepth& depth)
{
	const auto row_size = Image::rowSize(width, depth);
	if (depth == ColorDepth::bpp24)
		return row_size - width * 3;
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

void Image::save(const std::string& path) const
{
	std::ofstream fout;
	fout.open(path, std::ios::binary | std::ios::out);
	auto content = this->generateContentToSave();
	fout.write(content.data(), content.size());
	fout.close();
}

std::string Image::toStr() const
{
	std::string output;
	if (this->depth == ColorDepth::bpp24)
	{
		for (int i = height - 1; i > 0; --i)
		{
			for (int j = 0; j < width; j++)
			{
				unsigned char arr[3];
				getPixel(j, i, arr, PixelMode::rgb);
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
	}
	else if (this->depth == ColorDepth::bpp1)
	{
		for (int k = 0 + this->start_index; k < this->height + this->start_index; ++k)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 7; j >= 0; j--)
				{
					if (Utils::isBitSet(this->content[i + k * this->row_size], j))
					{
						output.push_back('*');
					}
					else
					{
						output.push_back(' ');
					}
				}
			}
			output.push_back('\n');
		}
	}
	return output;
}

std::vector<char> Image::generateContentToSave() const
{
	std::vector<char> output;
	switch (this->depth)
	{
	case ColorDepth::bpp24:
		{
			char buf[54];
			this->generateHeader(buf);

			output.reserve(this->HEADER_SIZE + this->row_size * this->height);
			output.insert(output.end(), buf, buf + this->HEADER_SIZE);
			for (int j = 0; j < this->height; ++j)
			{
				for (int i = 0; i < this->width; ++i)
				{
					unsigned char px[3];
					this->getPixel(i, j, px, PixelMode::bgr);

					for (auto c : px)
					{
						output.emplace_back(c);
					}
				}
				for (int i = 0; i < (Image::rowPadding(this->width, this->depth)); ++i)
				{
					output.push_back(0);
				}
			}
			break;
		}
	case ColorDepth::bpp1:
		{
			auto* buf = new unsigned char[this->HEADER_SIZE + 8];

			char color_table[8] = {0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00};
			this->generateHeader(reinterpret_cast<char*>(buf), 1, color_table, 8);

			output.reserve(this->file_size);
			output.insert(output.end(), buf, buf + this->HEADER_SIZE + 8);

			delete[] buf;
			for (int k = this->height - 1 + this->start_index; k >= 0 + this->start_index; --k)
			{
				for (int i = 0; i < 4; i++)
				{
					output.emplace_back(static_cast<char>(this->content[k * this->row_size + i]));
				}
			}
			break;
		}
	default:
		break;
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

void Image::loadFromMemory(unsigned char* input, unsigned int width, unsigned height, unsigned start_index,
                           ColorDepth cd)
{
	this->width = width;
	this->height = height;
	this->content = (input);
	switch (cd)
	{
	case ColorDepth::bpp1:
		this->row_size = this->rowSize(width, ColorDepth::bpp1);
		this->file_size = this->HEADER_SIZE + 8 + this->row_size * height;
		this->pixel_array_offset = this->HEADER_SIZE + 8;
		break;

	default:
		break;
	}
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
	this->row_size = Image::rowSize(this->width, this->depth);
	this->buffer_size = Image::bufferSize(this->BYTES_PER_PIXEL, this->width, this->height);
}

void Image::generateHeader(char* input, uint8_t bpp, char* color_table, size_t color_table_size) const
{
	input[0] = 'B';
	input[1] = 'M';
	Utils::writeIntToCharBufffer(input, this->file_size, 2);
	Utils::writeIntToCharBufffer(input, 0, 6); //not used space
	Utils::writeIntToCharBufffer(input, this->pixel_array_offset, 10);
	Utils::writeIntToCharBufffer(input, 40, 14); //header size
	Utils::writeIntToCharBufffer(input, this->width, 18);
	Utils::writeIntToCharBufffer(input, this->height, 22);
	Utils::writeIntToCharBufffer(input, 1, 26); //planes
	Utils::writeIntToCharBufffer(input, bpp, 28); //bpp
	Utils::writeIntToCharBufffer(input, 0, 30); //compression - not important and not used
	Utils::writeIntToCharBufffer(input, 0, 34); //real size for compression - same as above
	Utils::writeIntToCharBufffer(input, this->horizontal_resolution, 38);
	Utils::writeIntToCharBufffer(input, this->vertical_resolution, 42);
	Utils::writeIntToCharBufffer(input, 0, 46); //color pallette
	Utils::writeIntToCharBufffer(input, 0, 50); //important colors
	if (color_table != nullptr)
		memcpy(input + 54, color_table, color_table_size);
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


Image::Image(unsigned char* content, const unsigned width, const unsigned height, const unsigned start_index)
{
	this->depth = ColorDepth::bpp1;
	this->start_index = start_index;
	this->loadFromMemory(content, width, height, start_index, ColorDepth::bpp1);
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
	this->horizontal_resolution = other.horizontal_resolution;
	this->vertical_resolution = other.vertical_resolution;
	this->file_size = other.file_size;
	this->depth = other.depth;
	this->content = new unsigned char[other.buffer_size];
	memcpy(this->content, other.content, other.buffer_size);
}

Image::~Image()
{
	if (this->depth != ColorDepth::bpp1)
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

std::map<std::string, ImageContent*> Image::type_map = { {"Bpp1", new Bpp1()} };
