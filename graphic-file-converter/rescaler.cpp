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
			const auto gx = static_cast<double>(x) / newImage->width * (oldImage->width - 1);
			const auto gy = static_cast<double>(y) / newImage->height * (oldImage->height - 1);
			auto gxi = static_cast<int>(gx);
			auto gyi = static_cast<int>(gy);

			// space for operation on pixels and their colors
			// to be implemented
			//
		}
	}
}
