//Created by Gustaw Daczkowski
#include "image.h"
#include <iostream>
#include <map>
#include "image_content/bpp1.h"
#include "image_file_types/bmp_file.h"

std::map<unsigned int, std::function<ImageContent*()>> Image::content_type_map = {};
std::map<std::string, std::function<File*()>> Image::file_type_map = {};

void Image::getPixel(unsigned int x, unsigned int y, unsigned char output[]) const
{
	this->content->getPixel(x, y, output);
}

bool Image::getPixel(unsigned x, unsigned y) const
{
	uint8_t out;
	this->content->getPixel(x, y, &out);
	return out != 0;
}

void Image::putPixel(unsigned int x, unsigned int y, unsigned char input[])
{
	this->content->putPixel(x, y, input);
}

void Image::putPixel(unsigned x, unsigned y, bool value)
{
	if (typeid(*this->content) == typeid(Bpp1))
	{
		uint8_t in = value ? 0x01 : 0x00;
		this->content->putPixel(x, y, &in);
	}
	else
		throw std::runtime_error("This function call is allowed only for 1Bpp content type!");
}


void Image::resize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	this->content->resize(width, height);
}

void Image::save(const std::string& path) const
{
	const auto extension = Image::getExtension(path);
	auto file = Image::file_type_map[extension]();
	file->save(this->content, path);
}

std::string Image::toStr() const
{
	return this->content->toString();
}

void Image::loadFromPath(const std::string& path)
{
	this->path = path;
	const auto extension = Image::getExtension(this->path);

	auto file = Image::file_type_map[extension]();
	this->content = file->loadForContent(this->path);
	this->type = this->content->getType();
	this->width = this->content->getWidth();
	this->height = this->content->getHeight();
	this->channels = this->content->getChannels();
}

std::string Image::getExtension(const std::string& path)
{
	const auto dot_pos = path.rfind('.');
	const auto slash_pos = path.rfind('/');

	if(slash_pos == std::string::npos)
	{
		if (dot_pos == std::string::npos)
			throw std::runtime_error("Provided path is invalid!");
	}

	if (dot_pos < slash_pos)
	{
		throw std::runtime_error("Provided path is invalid!");
	}
	
	const auto end_of_extension = path.rfind('_');
	if (end_of_extension != std::string::npos)
	{
		return path.substr(dot_pos, end_of_extension - dot_pos);
	}
	return path.substr(dot_pos);
}

unsigned Image::onePixelByteSize() const
{
	return this->content->getPixelByteSize();
}

ImageContent* Image::getContent() const
{
	return this->content;
}

Image::Image(unsigned int content_type, unsigned int width, unsigned int height): width(width), height(height)
{
	if (Image::content_type_map.count(content_type))
	{
		delete this->content;
		this->content = Image::content_type_map[content_type]();
		this->content->resize(width, height);
		this->type = content_type;
	}
	else
		throw std::runtime_error(
			"Content you used: " + std::to_string(content_type) + "is not valid content type for Image!");
}

Image::Image(const std::string& path)
{
	this->loadFromPath(path);
}

Image::Image(const Image& other)
{
#ifdef _DEBUG
	std::cout << "Inside copy constructor of class Image" << std::endl;
#endif
	this->width = other.width;
	this->height = other.height;
	this->content = other.content->clone();
	this->channels = other.channels;
}

Image::~Image()
{
	delete[] this->content;
}

std::ostream& operator<<(std::ostream& os, const Image& im)
{
	os << im.toStr();
	return os;
}
