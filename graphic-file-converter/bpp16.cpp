#include "bpp16.h"

void Bpp16::getPixel(unsigned x, unsigned y, uint8_t* output)
{
	this->verifyAccess(x, y);
	for (int i = 0; i < this->distinct_colors; ++i)
	{
		const auto index = this->width * 2 * y + x * 2;
		output[i] = this->buffer[index];
	}
}

void Bpp16::putPixel(unsigned x, unsigned y, uint8_t* input)
{
	this->verifyAccess(x, y);
	for (int i = 0; i < this->distinct_colors; ++i)
	{
		const auto index = this->width * 2 * y + x * 2;
		this->buffer[index] = input[i];
	}
}

size_t Bpp16::calculateBufferSize()
{
	return this->width * this->height * 2;
}

Bpp16::~Bpp16()
{
	delete[] this->buffer;
}
