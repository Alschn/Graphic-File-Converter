#include <iostream>

#include "image.h"

int main()
{

	Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);
	std::cout << im.to_str();
	return 0;
}
