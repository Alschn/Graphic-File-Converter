#include "bpp1.h"
#include "utils.h"

void Bpp1::getPixel(unsigned x, unsigned y, uint8_t* output)
{
	this->verifyAccess(x, y);
	unsigned int byte_n = 0;
	unsigned int bit_n = 0;
	this->calculatePixelIndex(x, y, byte_n, bit_n);
	output[0] = (this->buffer[byte_n] >> (7 - bit_n)) & 1;
}

void Bpp1::putPixel(unsigned x, unsigned y, uint8_t* input)
{
	this->verifyAccess(x, y);
	unsigned int byte_n = 0;
	unsigned int bit_n = 0;
	this->calculatePixelIndex(x, y, byte_n, bit_n);
	this->buffer[byte_n] = (this->buffer[byte_n] & ~(1UL << 7 - bit_n)) | (input[0] << 7 - bit_n);
}

size_t Bpp1::calculateBufferSize()
{
	const size_t size = this->width * this->height;
	return Bpp1::eightDivisor(size);
}

std::string Bpp1::toString()
{
	std::string output;
	output.reserve(this->width * this->height + this->height);
	for (int j = this->height - 1; j >= 0; j--)
	{
		for (auto i = 0; i < this->width; ++i)
		{
			uint8_t data = 4;
			this->getPixel(i, j, &data);
			output.push_back(this->symbols[data]);
		}
		output.push_back('\n');
	}
	return output;
}

ImageContent* Bpp1::clone()
{
	return new Bpp1(*this);
}

std::string Bpp1::getType()
{
	return "Bpp1";
}

int Bpp1::rowSize()
{
	if (this->width % 8 == 0)
		return this->width / 8;
	return -1;
}

unsigned Bpp1::bmpRowSize()
{
	return Bpp1::eightDivisor(this->width);
}

void Bpp1::readFromBmpMemory(uint8_t* buffer)
{
	const auto internal_row_size = this->rowSize();
	unsigned int source_counter = 0;
	unsigned int dest_counter = 0;
	const auto padding = this->bmpPadding();

	if (internal_row_size > -1)
	{
		for (int j = 0; j < this->height; ++j)
		{
			for (int i = 0; i < internal_row_size; ++i)
			{
				this->buffer[dest_counter] = buffer[source_counter];
				source_counter++;
				dest_counter++;
			}
			source_counter += padding;
		}
	}
	else
	{
		for (int j = 0; j < this->height; ++j)
		{
			for (int i = 0; i < this->width; ++i)
			{
				uint8_t pixel =  0;
				pixel= (buffer[j*(this->width/8+1 + this->bmpPadding()) + i/8] >> (7-i%8)) & 1;
				this->putPixel(i, j, &pixel);
			}
		}
	}
}

ContentTypes Bpp1::getContentType()
{
	return ContentTypes::Bpp1;
}

std::vector<uint8_t> Bpp1::colorPalette()
{
	auto to_ret = std::vector<uint8_t>{0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00};
	return to_ret;
}

unsigned Bpp1::colorPaletteSize()
{
	return 8;
}

std::vector<uint8_t> Bpp1::bmpContent()
{
	std::vector<uint8_t> output;
	const auto internal_row_size = this->rowSize();
	unsigned int source_counter = 0;
	const auto padding = this->bmpPadding();

	if (internal_row_size > -1)
	{
		output.reserve((internal_row_size + padding) * this->height);
		for (int j = 0; j < this->height; ++j)
		{
			for (int i = 0; i < internal_row_size; ++i)
			{
				output.push_back(this->buffer[source_counter]);
				source_counter++;
			}
			for (auto p = 0; p < padding; ++p)
			{
				output.push_back(0);
			}
		}
	}
	else
	{
		const auto bytes_in_row = this->width / 8 + 1;
		output.reserve((bytes_in_row + padding) * this->height);
		for (int j = 0; j < this->height; ++j)
		{
			uint8_t* bytes_to_write = new uint8_t[bytes_in_row];
			for (int i = 0; i < this->width; ++i)
			{
				uint8_t pixel[1] = {0};
				this->getPixel(i, j, pixel);
				bytes_to_write[i / 8] = (bytes_to_write[i / 8] & ~(1UL << 7 - i % 8)) | (pixel[0] << 7 - i % 8);
			}
			for (int b =  0; b< bytes_in_row;++b)
			{
				output.push_back(bytes_to_write[b]);
			}
			for (auto p = 0; p < padding; ++p)
			{
				output.push_back(0);
			}
		}
	}
	return output;
}

unsigned Bpp1::eightDivisor(const unsigned input)
{
	if (input % 8 != 0)
	{
		return input / 8 + 1;
	}
	return input / 8;
}

void Bpp1::calculatePixelIndex(unsigned int x, unsigned int y, unsigned int& byte_n, unsigned int& bit_n) const
{
	unsigned index = this->width * y + x;
	byte_n = index / 8;
	bit_n = index % 8;
}

Bpp1::Bpp1(const Bpp1& other)
{
	this->width = other.width;
	this->height = other.height;
	this->buffer_size = other.buffer_size;
	this->buffer = new uint8_t[this->buffer_size];
	memcpy(this->buffer, other.buffer, this->buffer_size);
}

Bpp1::Bpp1()
{
	this->width = 0;
	this->height = 0;
	this->buffer_size = 0;
	this->channels = 1;
}


Bpp1::~Bpp1()
{
	delete[] this->buffer;
}
