#pragma once
#include <string>
#include <utility>
#include "utils.h"


enum class ImageMode
{

	ReadFromBMP,
	ReadFromHeader,
};
enum class ColorDepth
{
	bpp24,
	bpp8,
	bpp1,
};



class Image
{
private:
	std::string path;
	unsigned char* content;


public:
	unsigned int width;
	unsigned int height;
	unsigned char* header;
	size_t file_size;
	

	ImageMode mode;
	ColorDepth depth;

	unsigned int buffer_size;

	const size_t HEADER_SIZE = 52;
	const int FILE_SIZE_OFFSET = 2;
	const int WIDTH_OFFSET = 18;
	const int HEIGHT_OFFSET = 22;
	const int PIXEL_ARRAY_OFFSET = 10;
	
	void replacePixel(int x, int y, const char pixel[3]);
	void replaceAllPixels(const char** pixels, size_t rows, size_t col);
	void getPixel(int x, int y, unsigned char(&output)[3]);
	void putPixel(int x, int y, unsigned char(&input)[3]);
	char** getAllPixels();

	// x coord, y coord, color: 0 - red, 1 - green, 2 - blue
	int calculatePixelIndex(int x, int y, int color=0) const;

	void save(const std::string& path);
	std::string to_str();

private:
	void load(bool expect_saving);
public:

	
	Image(std::string path, bool expect_saving, const ImageMode &m, const ColorDepth &depth = ColorDepth::bpp24) : path(std::move(path)), mode(m), depth(depth)
	{
		if (expect_saving)
		{
			this->header = new unsigned char[this->HEADER_SIZE];
		}
		

		this->load(expect_saving);
	};
	Image(const Image &other)
	{
		this->content = new unsigned char[other.buffer_size];
		memcpy(this->content, other.content, other.buffer_size);
	};

	~Image()
	{
		delete[] this->content;
	}
};
