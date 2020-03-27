#include <iostream>
#include "user_interface.h"
#include "image.h"
#include "user_interface.cpp"

using namespace std;

int main()
{

	Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);
	std::cout << im.to_str();
	UserInterface Desktop;
	Desktop.display();

}
