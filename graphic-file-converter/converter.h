#pragma once
#include <iostream>
#include "image.h"

#ifndef CONVERTER_CLASS
#define CONVERTER_CLASS

class Converter
{
public:
	const Image* oldImage{};
	Image* newImage{};

public:
	virtual void processImage(int angle);
	virtual void scaleImage(double scale_x, double scale_y);
	void saveImage(const std::string& path) const;
	void loadImage(const Image* image);
	virtual void scaleBinImage(double scale_x, double scale_y);


	Converter() = default;

	Converter(const Image* base_image);;

	~Converter();
};
#endif
