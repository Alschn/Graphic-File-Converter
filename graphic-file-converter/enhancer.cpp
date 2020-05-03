#include "enhancer.h"
#include <cmath>

double Enhancer::checkColorRange(double value)
{
	if (value < 0) {
		return 0;
	}
	if (value > 255) {
		return 255;
	}
	return value;
}

void Enhancer::negativeOfImage()
{
	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
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

void Enhancer::adjustBrightness(int brightness)
{
	if (brightness > 255 || brightness < -255)
	{
		throw std::exception("Brightness has to be in range [-255, 255]");
	}
	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);

			const auto red = static_cast<unsigned char>(this->checkColorRange(pixels[0] + brightness));
			const auto green = static_cast<unsigned char>(this->checkColorRange(pixels[1] + brightness));
			const auto blue = static_cast<unsigned char>(this->checkColorRange(pixels[2] + brightness));

			unsigned char rgb[3] = { red, green, blue };
			this->newImage->putPixel(x, y, rgb);
		}
	}
}

void Enhancer::adjustContrast(int contrast)
{
	if (contrast > 255 || contrast < -255)
	{
		throw std::exception("Contrast has to be in range [-255, 255]");
	}
	const double factor = 259 * (contrast + 255) / (255 * (259 - contrast));
	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);
			const auto red = static_cast<unsigned char>(this->checkColorRange(factor * (pixels[0] - 128) + 128));
			const auto green = static_cast<unsigned char>(this->checkColorRange(factor * (pixels[1] - 128) + 128));
			const auto blue = static_cast<unsigned char>(this->checkColorRange(factor * (pixels[2] - 128) + 128));

			unsigned char rgb[3] = { red, green, blue };
			this->newImage->putPixel(x, y, rgb);
		}
	}
}

void Enhancer::adjustIntensity(int red, int green, int blue)
{
	if ((red > 255 || red < -255) || (green > 255 || green < -255) || (blue > 255 || blue < -255))
	{
		throw std::exception("Color adjustment has to be in range [-255, 255]");
	}

	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			unsigned char pixels[3];
			this->oldImage->getPixel(x, y, pixels);

			pixels[0] = this->checkColorRange(pixels[0] + red);
			pixels[1] = this->checkColorRange(pixels[1] + green);
			pixels[2] = this->checkColorRange(pixels[2] + blue);

			this->newImage->putPixel(x, y, pixels);
		}
	}
}