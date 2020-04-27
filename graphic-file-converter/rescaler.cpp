#include "rescaler.h"

double Rescaler::linearInterpolation(double s, double e, double t)
{
	return s + (e - s) * t;
}

double Rescaler::bilinearInterpolation(double c00, double c10, double c01, double c11, double tx, double ty)
{
	return linearInterpolation(linearInterpolation(c00, c10, tx), linearInterpolation(c01, c11, tx), ty);
}

void Rescaler::scaleImage(double scale_x, double scale_y)
{
	const auto new_width = static_cast<int>(oldImage->width * scale_x);
	const auto new_height = static_cast<int>(oldImage->height * scale_y);
	this->newImage->resize(new_width, new_height);

	for (int x = 0; x < newImage->width; x++) {
		for (int y = 0; y < newImage->height; y++)
		{
			auto gx = static_cast<double>(x) / newImage->width * (oldImage->width - 1);
			auto gy = static_cast<double>(y) / newImage->height * (oldImage->height - 1);
			auto gxi = static_cast<int>(gx);
			auto gyi = static_cast<int>(gy);

			unsigned char c00[3];
			this->oldImage->getPixel(gxi, gyi, c00);

			unsigned char c01[3];
			this->oldImage->getPixel(gxi + 1, gyi, c01);

			unsigned char c10[3];
			this->oldImage->getPixel(gxi, gyi + 1, c10);

			unsigned char c11[3];
			this->oldImage->getPixel(gxi + 1, gyi + 1, c11);

			auto red = static_cast<unsigned char>(bilinearInterpolation(c00[0], c10[0], c01[0], c11[0], gx - gxi, gy - gyi));
			auto green = static_cast<unsigned char>(bilinearInterpolation(c00[1], c10[1], c01[1], c11[1], gx - gxi, gy - gyi));
			auto blue = static_cast<unsigned char>(bilinearInterpolation(c00[2], c10[2], c01[2], c11[2], gx - gxi, gy - gyi));

			unsigned char rgb[3] = { red, green, blue };
			this->newImage->putPixel(x, y, rgb);

			// unsigned char pixels[3];
			// this->oldImage->getPixel(old_x, old_y, pixels);
			// this->newImage->putPixel(new_x, new_y, pixels);
			//
		}
	}
}
