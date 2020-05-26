//Created by Adam Lisichin
#include "negative.h"


void Negative::processImage(Arguments* args)
{
	if (oldImage->channels == 1)
	{
		throw std::exception("Negative is not available for 1bpp");
	}
	for (unsigned x = 0; x < newImage->width; x++) {
		for (unsigned y = 0; y < newImage->height; y++)
		{

			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);

			const auto red = 255 - pixels[0];
			const auto green = 255 - pixels[1];
			const auto blue = 255 - pixels[2];

			unsigned char rgb[3] = { red, green, blue };
			this->newImage->putPixel(x, y, rgb);
		}
	}
}