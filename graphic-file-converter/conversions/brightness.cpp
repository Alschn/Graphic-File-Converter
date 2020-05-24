//#include "brightness.h"
////Created by Adam Lisichin
//#include "brightness.h"
//
//void Brightness::processImage(Arguments* args)
//{
//	if (args[0] > 255 || args[0] < -255)
//	{
//		throw std::exception("Brightness has to be in range [-255, 255]");
//	}
//	for (int x = 0; x < newImage->width; x++) {
//		for (int y = 0; y < newImage->height; y++)
//		{
//			unsigned char pixels[3];
//			this->oldImage->getPixel(x, y, pixels);
//
//			const auto red = static_cast<unsigned char>(this->checkColorRange(pixels[0] + args[0]));
//			const auto green = static_cast<unsigned char>(this->checkColorRange(pixels[1] + args[0]));
//			const auto blue = static_cast<unsigned char>(this->checkColorRange(pixels[2] + args[0]));
//
//			unsigned char rgb[3] = { red, green, blue };
//			this->newImage->putPixel(x, y, rgb);
//		}
//	}
//}