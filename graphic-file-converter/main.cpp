#include <iostream>
#include "utils.h"
#include "rotation.h"
#include "reflection.h"
#include "arialDig32x24.h"
#include <fstream>
// #include "user_interface.h"
// #include "image.h"
#include "reflection.h"
#include "display_parameter.h"

using namespace std;

int main()
{
#ifdef _DEBUG
	std::cout << "In DEBUG mode." << std::endl;
#endif

	// std::cout << im;
	//std::cout << endl;


	//std::map<std::string, Converter*> conversions;
	// Converter* conv = new Rotation(&im);

	//conversions.try_emplace("rotate", new Rotation());


	//Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);


	//Image im2(im);
	//im2.resize(im.height, im.width);

	Converter  *conv = new Reflection(&im);
	conv->processImage(2);
	conv->saveImage(R"(..\sample_bmps\output.bmp)");

	UserInterface Desktop;
	Rotation conversion;
	DisplayParameter display;
	Reflection conversion2;
	Desktop.registerParameter("-d", &display);
	Desktop.registerAction("rotation", "rotates picture by n degrees", &conversion,regex(R"###(^converter +rotation +\d\d +(('|")[^'][^"]\S+[^'][^"]('|")) *(('|")[^'][^"]\S+[^'][^"]('|"))? *(-\w)? *$)###"), 1);
	Desktop.registerAction("reflection", "reflects picture over selected axis", &conversion2, regex(R"###(^converter +reflection +\d +(('|")[^'][^"]\S+[^'][^"]('|")) *(('|")[^'][^"]\S+[^'][^"]('|"))? *(-\w)? *$)###"), 1);

	Desktop.display();

	// im.save(R"(..\sample_bmps\10x1011121.bmp)");
	
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
