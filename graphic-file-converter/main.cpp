#include <iostream>
#include "user_interface.h"
// #include "image.h"

using namespace std;

int main()
{

	Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);
	std::cout << im;
	std::cout << endl;

	Image im2(im);

	im2.resize(im.height, im.width);


	UserInterface Desktop;

	
	//Desktop.registerAction("--rotation", "rotates picture by n degrees");
	//Desktop.registerAction("--contrast", "changes colours intensification");
	//Desktop.display();

	im.save(R"(..\sample_bmps\10x101111.bmp)");
	
}
