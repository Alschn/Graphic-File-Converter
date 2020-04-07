#include <iostream>

#include "rotation.h"
#include "reflection.h"
// #include "user_interface.h"
// #include "image.h"


using namespace std;

int main()
{

	Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);
	std::cout << im;
	std::cout << endl;


	//Image im2(im);
	//im2.resize(im.height, im.width);

	Converter  *conv = new Reflection(&im);
	conv->processImage(0);
	conv->saveImage(R"(..\sample_bmps\output.bmp)");

	// UserInterface Desktop;

	
	// Desktop.registerHelp("--rotation", "rotates picture by n degrees");
	// Desktop.registerHelp("--contrast", "changes colours intensification");
	// Desktop.display();

	// im.save(R"(..\sample_bmps\10x1011121.bmp)");
	
}
