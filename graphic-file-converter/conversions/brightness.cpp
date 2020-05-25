
//Created by Adam Lisichin
#include "brightness.h"
#include "../arguments/brightness_arguments.h"

void Brightness::processImage(Arguments* args)
{
	BrightnessArguments* bright_args = dynamic_cast<BrightnessArguments*>(args);
	bright_args->brightness_level = static_cast<int>(bright_args->brightness_level);
	if (bright_args->brightness_level > 255 || bright_args->brightness_level < -255)
	{
		throw std::exception("Brightness has to be in range [-255, 255]");
	}
	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);

			const auto red = static_cast<unsigned char>(this->checkColorRange(pixels[0] + bright_args->brightness_level));
			const auto green = static_cast<unsigned char>(this->checkColorRange(pixels[1] + bright_args->brightness_level));
			const auto blue = static_cast<unsigned char>(this->checkColorRange(pixels[2] + bright_args->brightness_level));

			unsigned char rgb[3] = { red, green, blue };
			this->newImage->putPixel(x, y, rgb);
		}
	}
}