#include "bpp1.h"

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
	if (size % 8 != 0)
	{
		return size / 8 + 1;
	}
	return size / 8;
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
}

Bpp1::Bpp1(unsigned width, unsigned height)
{
	this->ImageContent::resize(width, height);
}

Bpp1::~Bpp1()
{
	delete[] this->buffer;
}



