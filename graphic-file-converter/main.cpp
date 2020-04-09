#include <iostream>

#include "rotation.h"
#include "user_interface.h"
// #include "image.h"


using namespace std;

int main()
{
//#ifdef _DEBUG
	//std::cout << "In DEBUG mode." << std::endl;
//#endif

	// std::cout << im;
	//std::cout << endl;


	//std::map<std::string, Converter*> conversions;
	// Converter* conv = new Rotation(&im);

	//conversions.try_emplace("rotate", new Rotation());


	//Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);


	// conv->processImage(90);
	// conv->saveImage(R"(..\sample_bmps\10x1110_rotated.bmp)");


	UserInterface Desktop;
	Rotation conversion;
	Desktop.registerAction("rotation", "rotates picture by n degrees", &conversion, regex(R"###(^converter +rotation +\d\d +(('|")[^']\S+[^']('|")) *('\S+[^']')? *$)###"), 1);
	Desktop.display();

	//im.save(R"(..\sample_bmps\10x1011121.bmp)");
}



