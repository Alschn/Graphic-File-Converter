//Created by Adam Lisichin
#include "color_intensity.h"
#include "../arguments/color_intesity_arguments.h"

void Intensity::processImage(Arguments* args)
{
	if (oldImage->channels == 1)
	{
		throw std::exception("Color intensity is not available for 1bpp");
	}
	ColorIntensityArguments* col_args = dynamic_cast<ColorIntensityArguments*>(args);
	col_args->r = static_cast<int>(col_args->r);
	col_args->g = static_cast<int>(col_args->g);
	col_args->b = static_cast<int>(col_args->b);
	
	if ((col_args->r > 255 || col_args->r < -255) || (col_args->g > 255 || col_args->g < -255) || (col_args->b > 255 || col_args->b < -255))
	{
		throw std::invalid_argument("Color adjustment has to be in range [-255, 255]");
	}

	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);

			pixels[0] = this->checkColorRange(pixels[0] + col_args->r);
			pixels[1] = this->checkColorRange(pixels[1] + col_args->g);
			pixels[2] = this->checkColorRange(pixels[2] + col_args->b);

			this->newImage->putPixel(x, y, pixels);
		}
	}
}
