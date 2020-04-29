#include <iostream>
#include "utils.h"
#include "rotation.h"
#include "reflection.h"
#include "arialDig32x24.h"
#include <fstream>
#include "image_content.h"
#include "bpp24.h"
#include "header_file.h"
#include "rescaler.h"

int main()
{
#ifdef _DEBUG
	std::cout << "In DEBUG mode." << std::endl;
#endif

	/*
	 *Here is an example how to use Image class with `from memory` mode.
	 * Simply uncomment lines below and set number constant. The number will be displayed on the console and save to from_arial.bmp file.
	 * Attention: `FromMemory` mode doesn't work with converter. Converter can only convert images from .bmp files.
	 */
	const int number = 9;
	// Image im(const_cast<unsigned char*>(ArialDig32x24), 32, 23, 23 * number);

	// unsigned char a[3] = { 100, 200, 213};
	// im.putPixel(222, 200, a);

	// ImageContent* content = new Bpp24(20, 20);
	// content->resize(30, 30);
	// unsigned char x[] = {1, 2, 3};
	// content->putPixel(500, 500, x);

	auto im = new Image("../sample_bmps/arialDig32x24.h_9");
	Converter *conv = new Rescaler(im);
	conv->scaleBinImage(2, 2);
	std::cout << *conv->newImage;
	
	// std::cout << std::endl << im << std::endl;
	// im.save(R"(..\sample_bmps\from_arial.bmp)");
	/*
	 * End of example
	 */
}
