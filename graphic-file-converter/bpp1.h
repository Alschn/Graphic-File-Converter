#pragma once
#include "image_content.h"
#ifndef _BPP1_
#define _BPP1_

class Bpp1 :public ImageContent
{
public:
	const unsigned int distinct_colors = 2;
	const char symbols[2] = {' ', '*'};

	void getPixel(unsigned x, unsigned y, uint8_t* output) override;
	void putPixel(unsigned x, unsigned y, uint8_t* input) override;
	size_t calculateBufferSize() override;

	std::string toString() override;
	ContentTypes getType() override;
	ContentTypes getContentType() override;

	int rowSize() override;
	unsigned bmpRowSize() override;
	void readFromBmpMemory(uint8_t* buffer) override;
	std::vector<uint8_t> colorPalette() override;
	unsigned colorPaletteSize() override;
	std::vector<uint8_t> bmpContent() override;

	static unsigned int eightDivisor(const unsigned int input);

private:
	void calculatePixelIndex(unsigned int x, unsigned int y, unsigned int& byte_n, unsigned int& bit_n) const;
public:
	Bpp1(const Bpp1& other);
	ImageContent* clone() override;
	Bpp1();
	~Bpp1();
};
#endif
