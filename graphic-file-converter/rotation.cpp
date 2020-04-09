#include "rotation.h"
#include <cmath>

std::map <std::pair<int, int>, std::pair<int, int>> Rotation::create_map(int angle, int height, int width)
{
	std::map <std::pair<int, int>, std::pair<int, int>> map;
	if (angle % 90 != 0)
	{
		throw std::exception("Angle has to be a multiple of 90 degrees");
	}

	const auto pi = std::acos(-1);
	double deg = angle * pi / 180;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// rotation matrix
			auto x_n = j * std::cos(-deg) - i * std::sin(-deg);
			auto y_n = j * std::sin(-deg) + i * std::cos(-deg);
			// translation vector
			switch (angle)
			{
			case 90:
				y_n += double(width) - 1;
				break;
			case 180:
				x_n += double(width) - 1;
				y_n += double(height) - 1;
				break;
			case 270:
				x_n += double(height) - 1;
				break;
			default:
				break;
			}
			map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(int(round(x_n)), int(round(y_n)))));
		}
	}
	return map;
};

void Rotation::processImage(int angle)
{
	int multiple = angle / 360;
	angle = angle - multiple * 360;
	if (!(angle == 360 || angle == 0))
	{
		if (angle != 180)
		{
			this->newImage->resize(this->oldImage->height, this->oldImage->width);
		}

		auto map = this->create_map(angle, this->oldImage->height, this->oldImage->width);

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