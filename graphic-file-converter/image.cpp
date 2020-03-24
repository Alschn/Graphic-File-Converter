#include "image.h"
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::setw(2) << std::setfill('0')<< std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
	return HexCharStruct(_c);
}

void Image::load(bool expect_saving)
{
    std::ifstream infile(this->path, std::ios_base::binary);
	
	std::vector<unsigned char> buffer{ std::istreambuf_iterator<char>(infile),
						   std::istreambuf_iterator<char>() };
	
	//check if signature is valid
	auto sig_0	 = buffer.at(0);
	auto sig_1 = buffer.at(1);
	
	if (sig_0 != 'B' || sig_1 != 'M')
		throw std::runtime_error("BMP signature is not valid!");
	
	//initialize necessary values
	this->file_size = Utils::fourCharsToInt(buffer, FILE_SIZE_OFFSET);
	this->width = Utils::fourCharsToInt(buffer, WIDTH_OFFSET);
	this->height = Utils::fourCharsToInt(buffer, HEIGHT_OFFSET);
	
	
	if(expect_saving)
	{
		std::copy(buffer.begin(), buffer.begin() + this->HEADER_SIZE, this->header);
	}
	char contents[8*3][48];
	auto dataSize = ((width * 3 + 3) & (~3));
	int offset = buffer.at(10);

	int f = 0;
	for(int j = 0; j < height; ++j)
	{
		for (int i=0 + offset + j * dataSize; i < width*3 + offset + j * dataSize; i += 3)
		{
			std::cout << "Pixel at: (" <<std::dec<< (i - offset - j * dataSize)/3<< ", " << j << ")   ";
			std::cout << "R: " << hex(buffer.at(i + 2 )) <<
				" G: "<< hex(buffer.at(i + 1 ))
			<< " B: "<< hex(buffer.at(i )) << std::endl;
		}
		std::cout << "============================================" << std::endl;
	}
	
	

	// auto dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);
	// std::vector<char> img(376);
	// infile.read(img.data(), img.size());
	//
	// auto dataSize = ((width * 3 + 3) & (~3)) * height;
	// img.resize(dataSize);
	// infile.read(img.data(), img.size());
	//
	// char temp = 0;
	//
	// for (auto i = dataSize - 4; i >= 0; i -= 3)
	// {
	// 	temp = img[i];
	// 	img[i] = img[i + 2];
	// 	img[i + 2] = temp;
	//
	// 	std::cout << "R: " << int(img[i] & 0xff) << " G: " << int(img[i + 1] & 0xff) << " B: " << int(img[i + 2] & 0xff) << std::endl;
	// }
	//
	
}
