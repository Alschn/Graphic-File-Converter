#include <iostream>

#include "rotation.h"
// #include "user_interface.h"
// #include "image.h"


using namespace std;


enum class abc
{
	a=1
};

int main()
{
#ifdef _DEBUG
	std::cout << "In DEBUG mode." << std::endl;
#endif

	// std::cout << im;
	std::cout << endl;


	std::map<std::string, Converter*> conversions;
	// Converter* conv = new Rotation(&im);

	conversions.try_emplace("rotate", new Rotation());


	Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);


	// conv->processImage(90);
	// conv->saveImage(R"(..\sample_bmps\10x1110_rotated.bmp)");


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
