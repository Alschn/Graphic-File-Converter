#include "bpp24.h"
#include <vector>

void Bpp24::getPixel(unsigned x, unsigned y, uint8_t* output)
{
	this->verifyAccess(x, y);
	for (int i = 0; i < this->bytes_per_pixel; ++i)
	{
		const auto index = this->width * this->bytes_per_pixel * y + x * this->bytes_per_pixel + i;
		output[i] = this->buffer[index];
	}
}

void Bpp24::putPixel(unsigned x, unsigned y, uint8_t* input)
{
	this->verifyAccess(x, y);
	for (int i = 0; i < this->bytes_per_pixel; ++i)
	{
		const auto index = this->width * this->bytes_per_pixel * y + x * this->bytes_per_pixel + i;
		this->buffer[index] = input[i];
	}
}

size_t Bpp24::calculateBufferSize()
{
	return this->width * this->height * 3;
}

std::string Bpp24::toString()
{
	std::string output;
	for (int i = this->height - 1; i >= 0; --i)
	{
		for (int j = 0; j < this->width; j++)
		{
			unsigned char arr[3];
			this->getPixel(j, i, arr);
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

ImageContent* Bpp24::clone()
{
	return new Bpp24(*this);
}

ContentTypes Bpp24::getType()
{
	return ContentTypes::Bpp24;
}

int Bpp24::rowSize()
{
	return this->width * 3;
}

unsigned Bpp24::bmpRowSize()
{
	return this->rowSize();
}

void Bpp24::readFromBmpMemory(uint8_t* buffer)
{
	unsigned int source_index = 0;
	unsigned int dest_index = 0;
	auto padding = this->bmpPadding();

	for (int j = 0; j < this->height; ++j)
	{
		for (int i = 0; i < this->width; ++i)
		{
			for (int k = 0; k < 3; ++k)
			{
				this->buffer[dest_index + k] = buffer[source_index + 2 - k];
			}
			dest_index += 3;
			source_index += 3;
		}
		source_index += padding;
	}
}

std::vector<uint8_t> Bpp24::bmpContent()
{
	std::vector<uint8_t> output;
	const auto padding = this->bmpPadding();
	output.reserve(this->height * (this->width * 3 + padding));

	unsigned source_index = 0;

	for (int j = 0; j < this->height; ++j)
	{
		for (int i = 0; i < this->width; ++i)
		{
			for (int k = 0; k < 3; ++k)
			{
				output.emplace_back(this->buffer[source_index + 2 - k]);
			}
			source_index += 3;
		}
		for (unsigned x = 0; x < padding; ++x)
		{
			output.emplace_back(0);
		}
	}
	return output;
}

Bpp24::Bpp24()
{
	this->width = 0;
	this->height = 0;
	this->buffer_size = 0;
}

Bpp24::Bpp24(const Bpp24& other)
{
	this->width = other.width;
	this->height = other.height;
	this->buffer_size = other.buffer_size;
	this->buffer = new uint8_t[this->buffer_size];
	memcpy(this->buffer, other.buffer, this->buffer_size);
}

Bpp24::~Bpp24()
{
	delete[] this->buffer;
}
