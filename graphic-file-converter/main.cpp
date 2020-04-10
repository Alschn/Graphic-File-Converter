#include <iostream>
#include "utils.h"
#include "rotation.h"
#include "reflection.h"
#include "arialDig32x24.h"
#include <fstream>

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
	// const int number = 9;
	// const Image im(const_cast<unsigned char*>(ArialDig32x24), 32, 23, 23 * number);
	// std::cout << std::endl << im << std::endl;
	// im.save(R"(..\sample_bmps\from_arial.bmp)");
	/*
	 * End of example
	 */
}
