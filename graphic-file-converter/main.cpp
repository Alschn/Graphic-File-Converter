#include <iostream>

#include "rotation.h"
#include "reflection.h"
// #include "user_interface.h"
// #include "image.h"

#include <chrono>
#include <fstream>
using namespace std;




int main()
{
#ifdef _DEBUG
	std::cout << "In DEBUG mode." << std::endl;
#endif




	// std::map<std::string, Converter*> conversions;


	// conversions.try_emplace("rotate", new Rotation());


	// Image im(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);
	Image im=Image();

	std::ifstream file(R"(..\sample_bmps\10x10.bmp)", std::ios_base::binary);

	file >> im;

	im.save(R"(..\sample_bmps\saved_test.bmp)");
	// im.save(R"(..\sample_bmps\test_save.bmp)");
	Converter* conv = new Rotation(&im);
	auto start = chrono::steady_clock::now();
	conv->processImage(90);
	conv->saveImage(R"(..\sample_bmps\11222.bmp)");
	// auto end = chrono::steady_clock::now();
	// cout << "Elapsed time in milliseconds : "
	// 	<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
	// 	<< " ms" << endl;

	// UserInterface Desktop;
	// Desktop.registerHelp("--rotation", "rotates picture by n degrees");
	// Desktop.registerHelp("--contrast", "changes colours intensification");
	// Desktop.display();

	im.save(R"(..\sample_bmps\10x1011121.bmp)");
}
