#include <iostream>
#include "utils.h"
#include "rotation.h"
#include "rescaler.h"
#include "reflection.h"
#include "display_parameter.h"
#include "user_interface.h"
#include "reflection_arguments.h"
#include "rotation_arguments.h"
#include "enhancer.h"
#include "rescaler.h"
#include "scale_arguments.h"

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
	 Desktop.registerParameter("-d", &display);
	 Desktop.registerAction("rotate", "rotates picture by n degrees", &conversion,
	 	regex(
	 		R"###(^rotate +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	 	&rot_args);
	 Desktop.registerAction("reflect", "reflects picture over selected axis", &conversion2,
	 	regex(
	 		R"###(^reflect +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	 	&ref_args);
	 Desktop.registerAction("scale", "scales picture to selected values", &conversion3, regex(R"###(^scale +(\d+|\d+.\d+) +(\d+|\d+.\d+) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"), &scale_args);
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
	//auto im = new Image("../sample_bmps/test.bmp");
	// std::cout << *im;

	/*Enhancer* conv = new Enhancer(im);
	conv->adjustIntensity(0, 0, 0);
	conv->newImage->save("../sample_bmps/test_blue+100.bmp");*/

}
