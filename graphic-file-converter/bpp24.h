#pragma once
#include "image_content.h"
class Bpp24 :public ImageContent
{
public:
	const unsigned int distinct_colors = 3;

	void getPixel(unsigned x, unsigned y, uint8_t* output) override;
	void putPixel(unsigned x, unsigned y, uint8_t* input) override;
	size_t calculateBufferSize() override;

	Bpp24(unsigned int width, unsigned int height);
	~Bpp24();
};

