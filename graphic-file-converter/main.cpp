#include <iostream>
#include <fstream>
#include "rotation.h"
#include "reflection.h"
#include "arialDig32x24.h"
#include "display_parameter.h"
#include "user_interface.h"
#include "reflection_arguments.h"
#include "rotation_arguments.h"

using namespace std;

int main(int argc, char *argv[])
{
	UserInterface Desktop;
	Rotation conversion;
	DisplayParameter display;
	Reflection conversion2;
	ReflectionArguments ref_args;
	RotationArguments rot_args;
	Desktop.registerParameter("-d", &display);
	Desktop.registerAction("rotate", "rotates picture by n degrees", &conversion,
		regex(
			R"###(^rotate +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
		&rot_args);
	Desktop.registerAction("reflect", "reflects picture over selected axis", &conversion2,
		regex(
			R"###(^reflect +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
		&ref_args);
	if (argc > 1)
	{	
		Desktop.display(argv_to_string(argv, argc));
	}
	else
	{
		std::cout << "No command typed! Try again!" << std::endl;
		Desktop.showHelp();
	}
}
