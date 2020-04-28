#pragma once
#include "image_content.h"
#ifndef _BPP1_
#define _BPP1_

class Bpp1 :
	public ImageContent
{
public:
	const unsigned int distinct_colors = 2;

	void getPixel(unsigned x, unsigned y, uint8_t* output) override;
	void putPixel(unsigned x, unsigned y, uint8_t* input) override;
	size_t calculateBufferSize() override;

private:
	void calculatePixelIndex(unsigned int x, unsigned int y, unsigned int& byte_n, unsigned int& bit_n) const;
public:
	Bpp1();
	Bpp1(unsigned int width, unsigned int height);
	~Bpp1();
};
#endif
