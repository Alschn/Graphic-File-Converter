#include <iostream>
#include <fstream>
#include "rotation.h"
#include "reflection.h"
#include "arialDig32x24.h"
#include "display_parameter.h"
#include "user_interface.h"
#include "rescaler.h"

using namespace std;

int main()
{
//#ifdef _DEBUG
//	std::cout << "In DEBUG mode." << std::endl;
//#endif

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
	Image im(R"(..\sample_bmps\8x48.bmp)", true, ImageMode::read_from_bmp);
	Converter* conv = new Rescaler(&im);
	conv->scaleImage(0.5, 0.5);
	conv->saveImage(R"(..\sample_bmps\output_rect2.bmp)");

	/*
	 * Initialize all variables and objects needed to use user interface.
	 */
	UserInterface Desktop;
	Rotation conversion;
	DisplayParameter display;
	Reflection conversion2;
	Desktop.registerParameter("-d", &display);
	Desktop.registerAction("rotation", "rotates picture by n degrees", &conversion,
	                       regex(
		                       R"###(^converter +rotation +\d+ +(('|")[^'][^"]\S+[^'][^"]('|")) *(('|")[^'][^"]\S+[^'][^"]('|"))? *(-\w)? *$)###"),
	                       1);
	Desktop.registerAction("reflection", "reflects picture over selected axis", &conversion2,
	                       regex(
		                       R"###(^converter +reflection +\d +(('|")[^'][^"]\S+[^'][^"]('|")) *(('|")[^'][^"]\S+[^'][^"]('|"))? *(-\w)? *$)###"),
	                       1);
	Desktop.display();
}
