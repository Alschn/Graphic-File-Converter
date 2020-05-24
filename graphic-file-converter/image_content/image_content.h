//Created by Gustaw Daczkowski
#pragma once
#include <cstdint>
#include <string>
#include<vector>

#ifndef  ImageContentClass
#define ImageContentClass


class ImageContent
{
protected:
	unsigned int width;
	unsigned int height;
	size_t buffer_size;
	uint8_t* buffer = nullptr;
	const unsigned int distinct_colors = 0;
	unsigned int onePixelByteSize;
	unsigned int channels;
	unsigned int type;

public:
	virtual void getPixel(unsigned int x, unsigned int y, uint8_t* output) = 0;
	virtual void putPixel(unsigned int x, unsigned int y, uint8_t* input) = 0;
	virtual void resize(unsigned int new_width, unsigned int new_height);
	virtual void putByte(uint8_t input, unsigned int index);
	virtual uint8_t getByte(unsigned int index);
	virtual int memRowSize() = 0;
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual ImageContent* clone() = 0;
	virtual std::string toString() =0;
	virtual unsigned int bmpPadding();
	virtual unsigned int bmpRowSize();
	virtual void readFromBmpMemory(uint8_t* buffer) = 0;
	virtual std::vector<uint8_t> colorPalette();
	virtual std::vector<uint8_t> bmpContent() = 0;
	virtual unsigned int getChannels();
	virtual unsigned int getType();
	virtual unsigned int getPixelByteSize();
	
	ImageContent(const ImageContent& other);
	ImageContent();
	virtual ~ImageContent() = default;;
	size_t getBufferSize() const;

protected:
	virtual size_t calculateBufferSize() = 0;
	virtual void verifyAccess(unsigned int x, unsigned int y);
};

#endif
