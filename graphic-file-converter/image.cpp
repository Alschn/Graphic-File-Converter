//Created by Gustaw Daczkowski
#include "image.h"
#include <iostream>
#include <map>
#include "image_file_types/bmp_file.h"

void Image::getPixel(unsigned int x, unsigned int y, unsigned char output[]) const
{
	this->content->getPixel(x, y, output);
}

void Image::putPixel(unsigned int x, unsigned int y, unsigned char input[])
{
	this->content->putPixel(x, y, input);
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
	const auto pos = path.rfind('.');
	if (pos == std::string::npos)
		throw std::runtime_error("Provided path is invalid!");

	const auto end_of_extension = path.rfind('_');
	if (end_of_extension != std::string::npos)
	{
		return path.substr(pos, end_of_extension - pos);
	}
	return path.substr(pos);
}

Image::Image(unsigned int content_type, unsigned int width, unsigned int height)
{
	delete this->content;
	this->content = Image::content_type_map[content_type]();
	this->content->resize(width, height);
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

std::map<unsigned int, std::function<ImageContent*()>> Image::content_type_map = {};

std::map<std::string, std::function<File*()>> Image::file_type_map = {
	{".h", []() -> File* { return new HeaderFile(); }},
	{".bmp", []() -> File* { return new BmpFile(); }}
};
