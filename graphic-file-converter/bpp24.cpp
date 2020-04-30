#include "bpp24.h"

void Bpp24::getPixel(unsigned x, unsigned y, uint8_t* output)
{
	this->verifyAccess(x, y);
	for (int i = 0; i < this->distinct_colors; ++i)
	{
		const auto index = this->width * this->distinct_colors * y + x * this->distinct_colors + i;
		output[i] = this->buffer[index];
	}
}

void Bpp24::putPixel(unsigned x, unsigned y, uint8_t* input)
{
	this->verifyAccess(x, y);
	for (int i = 0; i < this->distinct_colors; ++i)
	{
		const auto index = this->width * this->distinct_colors * y + x * this->distinct_colors + i;
		this->buffer[index] = input[i];
	}
}

size_t Bpp24::calculateBufferSize()
{
	return this->width * this->height * 3;
}

Bpp24::Bpp24(const unsigned width, const unsigned height)
{
	this->ImageContent::resize(width, height);
}

Bpp24::~Bpp24()
{
	delete[] this->buffer;
}
