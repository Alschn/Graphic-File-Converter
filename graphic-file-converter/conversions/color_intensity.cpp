//Created by Adam Lisichin
#include "color_intensity.h"

void Intensity::processImage(Arguments* args)
{
	if ((args[0] > 255 || args[0] < -255) || (args[1] > 255 || args[1] < -255) || (args[2] > 255 || args[2] < -255))
	{
		throw std::exception("Color adjustment has to be in range [-255, 255]");
	}

	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);

			pixels[0] = checkColorRange(pixels[0] + args[0]);
			pixels[1] = checkColorRange(pixels[1] + args[1]);
			pixels[2] = checkColorRange(pixels[2] + args[2]);

			this->newImage->putPixel(x, y, pixels);
		}
	}
}
