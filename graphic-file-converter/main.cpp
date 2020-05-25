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
#include "conversions/rescaler.h"
#include "arguments/scale_arguments.h"
#include "conversions/brightness.h"
#include "conversions/color_intensity.h"
#include "conversions/negative.h"
#include "conversions/contrast.h"
#include "arguments/brightness_arguments.h"
#include "arguments/contrast_arguments.h"
#include "arguments/color_intesity_arguments.h"

using namespace std;

int main(int argc, char* argv[])
{
	UserInterface Desktop;
	Rotation rotation;
	Reflection reflection;
	Rescaler rescaler;
	Brightness brightness;
	Intensity intensity;
	Negative negative;
	Contrast contrast;
	ReflectionArguments ref_args;
	RotationArguments rot_args;
	ScaleArguments scale_args;
	DisplayParameter display;
	BrightnessArguments bright_args;
	ContrastArguments contr_args;
	ColorIntensityArguments intens_args;
	Arguments neg_args;
	// "fake" arguments to satisfy registerAction - negative does not use arguments so it does not have special class for them

	Image::registerImageContent<Bpp1>(1);
	Image::registerImageContent<Bpp24>(24);
	// Image::registerFileType<BmpFile>(".bmp");
	// Image::registerFileType<HeaderFile>(".gh");


	Desktop.registerParameter("-d", &display);
	Desktop.registerAction("rotate", "rotates picture by n degrees", &rotation,
	                       regex(
		                       R"###(^rotate +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &rot_args,1);
	Desktop.registerAction("reflect", "reflects picture over selected axis", &reflection,
	                       regex(
		                       R"###(^reflect +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &ref_args,1);
	Desktop.registerAction("scale", "scales picture to selected values", &rescaler,
	                       regex(
		                       R"###(^scale +(\d+|\d+.\d+) +(\d+|\d+.\d+) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &scale_args,2);
	Desktop.registerAction("negate", "changes picture colors to their oppostie value", &negative, regex(
		                       R"###(^negate +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"), &neg_args,0);
	Desktop.registerAction("brighten", "adjust brightness level of picture", &brightness,
	                       regex(
		                       R"###(^brighten +(-?[0-9]\d*(\.\d+)?) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &bright_args,1);
	Desktop.registerAction("contrast", "adjust contrast of picture", &contrast,
	                       regex(
		                       R"###(^contrast +(-?[0-9]\d*(\.\d+)?) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &contr_args,1);
	Desktop.registerAction("intensify", "adjust R G B values of picture", &intensity,
	                       regex(
		                       R"###(^intensify +(-?[0-9]\d*(\.\d+)?) +(-?[0-9]\d*(\.\d+)?) +(-?[0-9]\d*(\.\d+)?) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &intens_args,3);

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
