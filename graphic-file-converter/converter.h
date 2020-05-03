#pragma once
#include <iostream>
#include "image.h"
#include "arguments.h"

#ifndef CONVERTER_CLASS
#define CONVERTER_CLASS

class Converter
{
public:
	const Image* oldImage{};
	Image* newImage{};

public:
	virtual void processImage(Arguments* args);
	void saveImage(const std::string& path) const;
	void loadImage(const Image* image);

	Converter() = default;

	Converter(const Image* base_image);;

	~Converter();
};
#endif
