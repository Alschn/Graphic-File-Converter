//Created by Adam Lisichin
#include "contrast.h"
#include "../arguments/contrast_arguments.h"

void Contrast::processImage(Arguments* args)
{
	ContrastArguments* contr_args = dynamic_cast<ContrastArguments*>(args);
	contr_args->contrast_value = static_cast<int>(contr_args->contrast_value);
	if (contr_args->contrast_value > 255 || contr_args->contrast_value < -255)
	{
		throw std::exception("Contrast has to be in range [-255, 255]");
	}
	const double factor = 259 * (contr_args->contrast_value + 255) / (255 * (259 - contr_args->contrast_value));
	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);
			const auto red = static_cast<unsigned char>(checkColorRange(factor * (pixels[0] - 128) + 128));
			const auto green = static_cast<unsigned char>(checkColorRange(factor * (pixels[1] - 128) + 128));
			const auto blue = static_cast<unsigned char>(checkColorRange(factor * (pixels[2] - 128) + 128));

			unsigned char rgb[3] = { red, green, blue };
			this->newImage->putPixel(x, y, rgb);
		}
	}
}
