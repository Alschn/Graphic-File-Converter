#pragma once
#include <vector>
#include "image_content.h"

class Bpp24 : public ImageContent
{
public:
	const unsigned int bytes_per_pixel = 3;
	 unsigned int channels = 3;
	
	void getPixel(unsigned x, unsigned y, uint8_t* output) override;
	void putPixel(unsigned x, unsigned y, uint8_t* input) override;
	size_t calculateBufferSize() override;
	std::string toString() override;
	ImageContent* clone() override;
	std::string getType() override;
	int rowSize() override;
	unsigned bmpRowSize() override;
	void readFromBmpMemory(uint8_t* buffer) override;
	ContentTypes getContentType() override;
	std::vector<uint8_t> bmpContent() override;
	
	using ImageContent::ImageContent;
	Bpp24();
	Bpp24(const Bpp24& other);
	~Bpp24();
};
