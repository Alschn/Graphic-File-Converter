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
	this->buffer[byte_n] |= input[0] << bit_n;
}

size_t Bpp1::calculateBufferSize()
{
	const size_t size = this->width * this->height;
	if (size%8 != 0)
	{
		return size / 8 + 1;
	}
	return size / 8;
}

void Bpp1::calculatePixelIndex(unsigned int x, unsigned int y, unsigned int& byte_n, unsigned int& bit_n) const
{
	unsigned index = this->width * y + x;
	byte_n = index / 8;
	bit_n = index % 8;
}

Bpp1::Bpp1(unsigned width, unsigned height)
{
	this->ImageContent::resize(width, height);
}

Bpp1::~Bpp1()
{
	delete[] this->buffer;
}
