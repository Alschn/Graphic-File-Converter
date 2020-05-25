//Created by Adam Lisichin
#include "rotation.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "../arguments/rotation_arguments.h"

std::map <std::pair<int, int>, std::pair<int, int>> Rotation::createMap(int height, int width, int angle)
{
	std::map <std::pair<int, int>, std::pair<int, int>> map;
	if (angle % 90 != 0)
	{
		throw std::invalid_argument("Angle has to be a multiple of 90 degrees");
	}

	const double deg = angle * M_PI / 180;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// rotation matrix
			auto x_n = static_cast<int>(round(j * std::cos(-deg) - i * std::sin(-deg)));
			auto y_n = static_cast<int>(round(j * std::sin(-deg) + i * std::cos(-deg)));
			// translation vector
			switch (angle)
			{
			case 90:
				y_n += width - 1;
				break;
			case 180:
				x_n += width - 1;
				y_n += height - 1;
				break;
			case 270:
				x_n += height - 1;
				break;
			default:
				break;
			}
			map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(x_n, y_n)));
		}
	}
	return map;
};

void Rotation::processImage(Arguments* args)
{
	RotationArguments* rot_args = dynamic_cast<RotationArguments*>(args);
	rot_args->degrees = static_cast<int>(rot_args->degrees);
	if(rot_args->degrees<0)
	{
		throw std::invalid_argument("Rotation degree has to be a positive number!");
	}
	// keep angle in [0, 360] degree interval
	const int multiple = rot_args->degrees / 360;
	rot_args->degrees = rot_args->degrees - multiple * 360;
	if (!(rot_args->degrees == 360 || rot_args->degrees == 0))	// do not calculate if deg is 0 or 360
	{
		if (rot_args->degrees != 180)	// do not resize for 180 degree rotation
		{
			this->newImage->resize(this->oldImage->height, this->oldImage->width);
		}

		auto map = this->createMap(this->oldImage->height, this->oldImage->width, rot_args->degrees);

		for (const auto& pair : map)
		{
			const auto old_x = pair.first.first;
			const auto old_y = pair.first.second;
			const auto new_x = pair.second.first;
			const auto new_y = pair.second.second;

			unsigned char pixels[3];

			this->oldImage->getPixel(old_x, old_y, pixels);
			this->newImage->putPixel(new_x, new_y, pixels);
		}
	}
}
