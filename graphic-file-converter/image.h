#pragma once
#include <string>
#include "utils.h"


class Image
{
private:
	std::string path;
	char** pixels;


public:
	unsigned int width;
	unsigned int height;
	char* header;
	size_t file_size;

	const size_t HEADER_SIZE = 52;
	const int FILE_SIZE_OFFSET = 2;
	const int WIDTH_OFFSET = 18;
	const int HEIGHT_OFFSET = 22;
	
	void replacePixel(int x, int y, const char pixel[3]);
	void replaceAllPixels(const char** pixels, size_t rows, size_t col);
	void getPixel(int x, int y, char output[]);
	char** getAllPixels();

	void save(const std::string& path);

private:
	void load(bool expect_saving);
public:
	Image(const std::string& path, bool expect_saving) : path(path)
	{
		if (expect_saving)
		{
			this->header = new char[this->HEADER_SIZE];
		}

		this->load(expect_saving);
	};
	Image(const Image &other)
	{
	
	};
};
