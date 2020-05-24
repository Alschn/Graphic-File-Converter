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


// int main(int argc, char* argv[])
int main()
{
	// UserInterface Desktop;
	// Rotation conversion;
	// DisplayParameter display;
	// Reflection conversion2;
	// ReflectionArguments ref_args;
	// RotationArguments rot_args;
	// Rescaler conversion3;
	// ScaleArguments scale_args;

	//register content types

	// bool found = false;
	// int found_letter_index = 0;
	// bool looking_for_black = true;
	// bool black_pixel_found = false;
	// for (int i = 0; i < im.width; ++i)
	// {
	// 	black_pixel_found = false;
	// 	for (int j = 0; j < im.height; ++j)
	// 	{
	// 		uint8_t colors[3] = {0, 0, 0};
	// 		im.getPixel(i, j, colors);
	// 		for (auto c : colors)
	// 		{
	// 			if (c < 30)
	// 			{
	// 				black_pixel_found = true;
	// 				if (looking_for_black) {
	// 					std::cout << "Letter with index: " << found_letter_index << " found at X: " << i << " Y: " << j << std::endl;
	// 					looking_for_black = false;
	// 					found_letter_index++;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	if (black_pixel_found)
	// 	{
	// 		std::cout << "Inside Letter"<<std::endl;
	// 	}
	// 	else
	// 	{
	// 		std::cout << "Looking for letter... " << std::endl;
	// 		looking_for_black = true;
	// 	}
	// }


	std::cout << " Get";
	// bool rest = im.getPixel<Bpp1>(1, 2);
	// im.getPixel<Bpp24>(1, 2);
	// im.getPixel<Bpp1>(1, 2);

	// Desktop.registerParameter("-d", &display);
	// Desktop.registerAction("rotate", "rotates picture by n degrees", &conversion,
	//                        std::regex(
	// 	                       R"###(^rotate +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	//                        &rot_args);
	// Desktop.registerAction("reflect", "reflects picture over selected axis", &conversion2,
	//                        std::regex(
	// 	                       R"###(^reflect +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	//                        &ref_args);
	// Desktop.registerAction("scale", "scales picture to selected values", &conversion3,
	//                        std::regex(
	// 	                       R"###(^scale +(\d+|\d+.\d+) +(\d+|\d+.\d+) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	//                        &scale_args);
	// if (argc > 1)
	// {
	// 	Desktop.display(argv_to_string(argv, argc));
	// }
	// else
	// {
	// 	std::cout << "No command typed! Try again!" << std::endl;
	// 	Desktop.showHelp();
	// }


	// std::cout << *im;
	// im->save("../sample_bmps/10x11xxx2.bmp");
	Image::registerImageContent<Bpp1>(1);
	Image::registerImageContent<Bpp24>(24);

	//auto im = Image("../sample_bmps/10x10.bmp");
	//im.save("../sample_bmps/abc.bmp");

	//Converter* conv = new Rescaler(&im);
	//auto args = new ScaleArguments();
	//args->set_arguments({ 2, 2 });
	//conv->processImage(args);
	//std::cout << conv->oldImage->toStr()<<std::endl;
	//std::cout << conv->newImage->toStr();
	//
	//conv->newImage->save("../sample_bmps/test_blue+100.bmp");
}
