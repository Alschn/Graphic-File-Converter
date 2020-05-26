//Created by Adam Lisichin
#pragma once
#include <iostream>
#include "../image.h"
#include "../arguments/arguments.h"

#ifndef CONVERTER_CLASS
#define CONVERTER_CLASS

class Converter
{
public:
	const Image* oldImage{};
	Image* newImage{};

public:
	virtual void processImage(Arguments* args);
	virtual void saveImage(const std::string& path);
	virtual void loadImage(const Image* image);
	

	Converter() = default;

	Converter(const Image* base_image);;

	virtual ~Converter();

	static double checkColorRange(double value);
};
#endif
