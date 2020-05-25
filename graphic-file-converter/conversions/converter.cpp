//Created by Adam Lisichin

#include "converter.h"

#include <iostream>


void Converter::processImage(Arguments* args)
{
	std::cout << "Inside converter";
}

auto Converter::checkColorRange(double value) -> double
{
	if (value < 0) {
		return 0;
	}
	if (value > 255) {
		return 255;
	}
	return value;
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
