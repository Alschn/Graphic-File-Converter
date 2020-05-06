//Created by Gustaw Daczkowski
#pragma once
#include <vector>
#include "file.h"

class BmpFile :public File
{
private:
	const size_t HEADER_SIZE = 54; // can be changed in future versions
	const int FILE_SIZE_OFFSET = 2;
	const int WIDTH_OFFSET = 18;
	const int HEIGHT_OFFSET = 22;
	const int BPP_OFFSET = 28;
	const int HORIZONTAL_RESOLUTION_OFFSET = 38;
	const int VERTICAL_RESOLUTION_OFFSET = 42;
	const int PIXEL_ARRAY_OFFSET= 10;
	const int WINDOWS_HEADER_SIZE = 40;
	const unsigned int H_RES = 3200; //experimental constants
	const unsigned int V_RES = 3200;
	ImageContent* content = nullptr;
	size_t file_size = 0;
	unsigned int row_size = 0; // row size in bytes 
	unsigned int pixel_array_offset = 0;

	std::vector<uint8_t> generateHeader(ImageContent* content) const;

public:
	void readHeader(char* buffer);
	void readPixelArray(char* pixel_array_buffer) const;
	ImageContent* loadForContent(const std::string& filename) override;
	void save(ImageContent* content, const std::string& path) override;
	~BmpFile();
};

