//Created by Gustaw Daczkowski
#include "image_content.h"
#include <stdexcept>
#include "../utils.h"

void ImageContent::resize(const unsigned new_width, const unsigned new_height)
{
	delete[] this->buffer;
	this->width = new_width;
	this->height = new_height;
	this->buffer_size = this->calculateBufferSize();
	this->buffer = new uint8_t[this->buffer_size];
}

void ImageContent::putByte(uint8_t input, unsigned index)
{
	if (index >= this->buffer_size)
		throw std::runtime_error("Index too high");
	this->buffer[index] = input;
}

uint8_t ImageContent::getByte(unsigned index)
{
	return this->buffer[index];
}

unsigned ImageContent::getWidth()
{
	return this->width;
}

unsigned ImageContent::getHeight()
{
	return this->height;
}

size_t ImageContent::getBufferSize() const
{
	return this->buffer_size;
}

unsigned ImageContent::bmpPadding()
{
	auto row_size = this->memRowSize();
	return Utils::closestFourMultiple(row_size) - row_size;
}

unsigned ImageContent::bmpRowSize()
{
	return Utils::closestFourMultiple(this->memRowSize());
}

std::vector<uint8_t> ImageContent::colorPalette()
{
	return std::vector<uint8_t>();
}

unsigned ImageContent::getChannels()
{
	return this->channels;
}

unsigned ImageContent::getType()
{
	return this->type;
}

unsigned ImageContent::getPixelByteSize()
{
	return this->onePixelByteSize;
}

size_t ImageContent::getBufferSize()
{
	return this->buffer_size;
}

ImageContent::ImageContent(const ImageContent& other): distinct_colors(other.distinct_colors),
                                                       onePixelByteSize(other.onePixelByteSize),
                                                       channels(other.channels), type(other.type), width(other.width),
                                                       height(other.height), buffer_size(other.buffer_size)
{
	this->buffer = new uint8_t[this->buffer_size];
	memcpy(this->buffer, other.buffer, this->buffer_size);
}

ImageContent::ImageContent()
	: width(0), height(0), buffer_size(0), type(0), onePixelByteSize(0), distinct_colors(0)
{
}

void ImageContent::verifyAccess(const unsigned x, const unsigned y)
{
	if (x > this->width - 1 || y > this->height - 1)
	{
		throw std::runtime_error("Requested pixel coordinates are out of range!");
	}
}
