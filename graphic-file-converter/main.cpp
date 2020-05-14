#include <iostream>
#include "image_content/image_content.h"
#include "image_content/bpp1.h"
#include "image_content/bpp24.h"
#include "utils.h"
#include "conversions/rotation.h"
#include "conversions/rescaler.h"
#include "conversions/reflection.h"
#include "parameters/display_parameter.h"
#include "user_interface/user_interface.h"
#include "arguments/reflection_arguments.h"
#include "arguments/rotation_arguments.h"
#include "conversions/enhancer.h"
#include "conversions/rescaler.h"
#include "arguments/scale_arguments.h"

using namespace std;

int main(int argc, char* argv[])
{

	
	UserInterface Desktop;
	Rotation conversion;
	DisplayParameter display;
	Reflection conversion2;
	ReflectionArguments ref_args;
	RotationArguments rot_args;
	Rescaler conversion3;
	ScaleArguments scale_args;

	Image::registerImageContent(1, []() -> ImageContent* { return new Bpp1(); });
	Image::registerImageContent(24, []() -> ImageContent* { return new Bpp24(); });

	
	Desktop.registerParameter("-d", &display);
	Desktop.registerAction("rotate", "rotates picture by n degrees", &conversion,
	                       regex(
		                       R"###(^rotate +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &rot_args);
	Desktop.registerAction("reflect", "reflects picture over selected axis", &conversion2,
	                       regex(
		                       R"###(^reflect +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &ref_args);
	Desktop.registerAction("scale", "scales picture to selected values", &conversion3,
	                       regex(
		                       R"###(^scale +(\d+|\d+.\d+) +(\d+|\d+.\d+) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &scale_args);
	if (argc > 1)
	{
		Desktop.display(argv_to_string(argv, argc));
	}
	else
	{
		std::cout << "No command typed! Try again!" << std::endl;
		Desktop.showHelp();
	}
	// auto im = Image("../sample_bmps/arialDig32x24.h_8");
// // std::cout << *im;
// // im->save("../sample_bmps/10x11xxx2.bmp");
//
// Converter* conv = new Rescaler(&im);
// auto args = new ScaleArguments();
// args->set_arguments({ 1, 1 });
// conv->processImage(args);
// std::cout << conv->oldImage->toStr()<<std::endl;
// std::cout << conv->newImage->toStr();
//
// // conv->newImage->save("../sample_bmps/test_blue+100.bmp");


}
