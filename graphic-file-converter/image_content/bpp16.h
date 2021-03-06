//Created by Gustaw Daczkowski
#pragma once
#include "./image_content.h"

class Bpp16 :
	public ImageContent
{
public:
	const unsigned int distinct_colors = 3;
	 unsigned int channels = 3;

	void getPixel(unsigned x, unsigned y, uint8_t* output) override;
	void putPixel(unsigned x, unsigned y, uint8_t* input) override;
	size_t calculateBufferSize() override;

	using ImageContent::ImageContent;
	~Bpp16();
};
