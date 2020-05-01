#include "image_content.h"
#include <stdexcept>
#include "utils.h"
void ImageContent::resize(const unsigned new_width, const unsigned new_height)
{
	this->width = new_width;
	this->height = new_height;
	this->buffer_size = this->calculateBufferSize();
	this->buffer = new uint8_t[this->buffer_size];
}

void ImageContent::putByte(uint8_t input, unsigned index)
{
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

size_t ImageContent::bufferSize() const
{
	return this->buffer_size;
}

unsigned ImageContent::bmpPadding()
{
		auto row_size = this->bmpRowSize();
		return Utils::closestFourMultiple(row_size) - row_size;
}

unsigned ImageContent::colorPaletteSize()
{
	return 0;
}

std::vector<uint8_t> ImageContent::colorPalette()
{
	return std::vector<uint8_t>();
}

unsigned ImageContent::getChannels() 
{
	return this->channels;
}

ImageContent::ImageContent(const ImageContent& other)
{
	this->width = other.width;
	this->height = other.height;
	this->buffer_size = other.buffer_size;
	this->buffer = new uint8_t[this->buffer_size];
	memcpy(this->buffer, other.buffer, this->buffer_size);
}

ImageContent::ImageContent()
{
	this->width = 0;
	this->height = 0;
	this->buffer_size = 0;
}

void ImageContent::verifyAccess(const unsigned x, const unsigned y)
{
	if (x > this->width - 1 || y > this->height - 1)
	{
		throw std::runtime_error("Requested pixel coordinates are out of range!");
	}
}
