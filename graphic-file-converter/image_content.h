#pragma once
#include <cstdint>
#include <map>
#include <string>


#ifndef  ImageContentClass
#define ImageContentClass

class ImageContent
{
protected:
	unsigned int width = 0;
	unsigned int height = 0;
	size_t buffer_size = 0;
	uint8_t* buffer = nullptr;
	const unsigned int distinct_colors = 0;

public:
	virtual void getPixel(unsigned int x, unsigned int y, uint8_t* output) = 0;
	virtual void putPixel(unsigned int x, unsigned int y, uint8_t* input) = 0;
	virtual void resize(unsigned int new_width, unsigned int new_height);
	virtual void putByte(uint8_t input, unsigned int index);
	virtual uint8_t getByte(unsigned int index);
	virtual int rowSize() = 0;
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual std::string getType() = 0;
	size_t bufferSize() const;
	ImageContent(const ImageContent& other);
	ImageContent();
	virtual ImageContent* clone() = 0;
	virtual std::string toString()=0;
	virtual ~ImageContent(){};

	
protected:
	virtual size_t calculateBufferSize() = 0;
	virtual void verifyAccess(unsigned int x, unsigned int y);
};

#endif
