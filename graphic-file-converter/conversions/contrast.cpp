////Created by Adam Lisichin
//#include "contrast.h"
//
//void Contrast::processImage(Arguments* args)
//{
//	if (args[0] > 255 || args[0] < 0)
//	{
//		throw std::exception("Contrast has to be in range [0, 255]");
//	}
//	const double factor = 259 * (args[0] + 255) / (255 * (259 - args[0]));
//	for (int x = 0; x < newImage->width; x++) {
//		for (int y = 0; y < newImage->height; y++)
//		{
//			unsigned char pixels[3];
//			this->oldImage->getPixel(x, y, pixels);
//			const auto red = static_cast<unsigned char>(checkColorRange(factor * (pixels[0] - 128) + 128));
//			const auto green = static_cast<unsigned char>(checkColorRange(factor * (pixels[1] - 128) + 128));
//			const auto blue = static_cast<unsigned char>(checkColorRange(factor * (pixels[2] - 128) + 128));
//
//			unsigned char rgb[3] = { red, green, blue };
//			this->newImage->putPixel(x, y, rgb);
//		}
//	}
//}
