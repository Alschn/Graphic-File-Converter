#include <iostream>

#include "rotation.h"
#include "reflection.h"
// #include "user_interface.h"
// #include "image.h"


using namespace std;




int main()
{
#ifdef _DEBUG
	std::cout << "In DEBUG mode." << std::endl;
#endif

	// std::cout << im;
	std::cout << endl;


	// std::map<std::string, Converter*> conversions;


	// conversions.try_emplace("rotate", new Rotation());


	Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);
	Converter* conv = new Reflection(&im);

	conv->processImage(0);
	conv->saveImage(R"(..\sample_bmps\101x1110_rotated.bmp)");


	// UserInterface Desktop;
	// Desktop.registerHelp("--rotation", "rotates picture by n degrees");
	// Desktop.registerHelp("--contrast", "changes colours intensification");
	// Desktop.display();

	im.save(R"(..\sample_bmps\10x1011121.bmp)");
}


void proccesscommand(std::string command)
{

	//Converter conversion= map[command]

	// Image *im = new Image(path);

	// conversion.loadimage(im);
	// conversion.proccessImage();
	
}
