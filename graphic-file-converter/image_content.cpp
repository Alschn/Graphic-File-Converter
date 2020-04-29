#include "image_content.h"

#include <stdexcept>

void ImageContent::resize(unsigned new_width, unsigned new_height)
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


unsigned ImageContent::getWidth()
{
	return this->width;
}

unsigned ImageContent::getHeight()
{
	return this->height;
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

void ImageContent::verifyAccess(unsigned x, unsigned y)
{
	if (x > this->width - 1 || y > this->height - 1)
	{
		throw std::runtime_error("Requested pixel coordinates are out of range!");
	}
}

// std::ostream& operator<<(std::ostream& os, const ImageContent& ic) 
// {
// 	os << const_cast<ImageContent&>(ic).toString();
// 	return os;
// }
