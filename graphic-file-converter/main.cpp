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

	Image::registerImageContent(1, []() -> ImageContent* { return new Bpp1(); });
	Image::registerImageContent(24, []() -> ImageContent* { return new Bpp24(); });


	Desktop.registerParameter("-d", &display);
	Desktop.registerAction("rotate", "rotates picture by n degrees", &rotation,
	                       regex(
		                       R"###(^rotate +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &rot_args);
	Desktop.registerAction("reflect", "reflects picture over selected axis", &reflection,
	                       regex(
		                       R"###(^reflect +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &ref_args);
	Desktop.registerAction("scale", "scales picture to selected values", &rescaler,
	                       regex(
		                       R"###(^scale +(\d+|\d+.\d+) +(\d+|\d+.\d+) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &scale_args);
	Desktop.registerAction("negate", "changes picture colors to their oppostie value", &negative, regex(
		                       R"###(^negate +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"), &neg_args);
	Desktop.registerAction("brighten", "adjust brightness level of picture", &brightness,
	                       regex(
		                       R"###(^brighten +(-?[0-9]\d*(\.\d+)?) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &bright_args);
	Desktop.registerAction("contrast", "adjust contrast of picture", &contrast,
	                       regex(
		                       R"###(^contrast +(-?[0-9]\d*(\.\d+)?) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &contr_args);
	Desktop.registerAction("intensify", "adjust R G B values of picture", &intensity,
	                       regex(
		                       R"###(^intensify +(-?[0-9]\d*(\.\d+)?) +(-?[0-9]\d*(\.\d+)?) +(-?[0-9]\d*(\.\d+)?) +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
	                       &intens_args);

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
