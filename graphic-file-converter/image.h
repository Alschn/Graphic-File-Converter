#pragma once
#include <string>
#include "Pixel.h"


class Image
{
private:
	const std::string path;
	std::string name;
	Pixel** pixels;


public:
	int channels;
	int bits_per_channel;
	int width;
	int height;

	void replacePixel(int x, int y, const Pixel& pixel);
	void replaceAllPixels(const Pixel** pixels);
	Pixel getPixel(int x, int y);
	Pixel** getAllPixels();

	void save(const std::string& path, const std::string& name);
	void load(const std::string& path, const std::string& name = "");

	Image(std::string& path, std::string& name) : path(path), name(name) {  };
	Image(const Image &other){};
};
