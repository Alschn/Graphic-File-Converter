#include "converter.h"

#include <iostream>


void Converter::processImage(int angle)
{
	std::cout << "Inside converter";
}

void Converter::saveImage(const std::string& path) const
{
	this->newImage->save(path);
}

void Converter::loadImage(const Image* image)
{
	this->oldImage = image;
	this->newImage = new Image(*image);
}

Converter::Converter(const Image* base_image) : oldImage(base_image)
{
	newImage = new Image(*base_image);
}

Converter::~Converter()
{
	delete this->oldImage;
	delete this->newImage;
}

void Converter::scaleImage(double scale_x, double scale_y)
{
	std::cout << "Inside converter";
}