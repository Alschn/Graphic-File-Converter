#include "reflection.h"

std::map <std::pair<int, int>, std::pair<int, int>> Reflection::create_map(int num)
{
	// vertical and horizontal reflection allowed for all bmp files
	// diagonal reflection allowed only for square ones
	for (int i = 0; i < this->oldImage->height; i++)
	{
		for (int j = 0; j < this->oldImage->width; j++)
		{
			int x_n = j;
			int y_n = i;
			switch (num)
			{
			case 0:
				// vertical mirror reflection
				x_n = this->oldImage->width - j - 1;
				break;
			case 1:
				// horizontal mirror reflection
				y_n = this->oldImage->height - i - 1;
				break;
			case 2:
				// diagonal mirror reflection y = x ONLY FOR SQUARES
				x_n = i;
				y_n = j;
				break;
			case 3:
				// diagonal mirror reflection y = -x+height ONLY FOR SQUARES
				x_n = this->oldImage->width - i - 1;
				y_n = this->oldImage->height - j - 1;
				break;
			default:
				break;
			}

			map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(x_n, y_n)));
		}
	}
	return this->map;
};


void Reflection::processImage(int reflect_num)
{
	if (this->oldImage->width != this->oldImage->height && (reflect_num == 2 || reflect_num == 3))
	{
		throw std::exception("Diagonal reflection is not allowed for non-square bmp files");
	}
	this->reflect_num = reflect_num;
	this->create_map(this->reflect_num);

	for (const auto& pair : this->map)
	{
		const auto old_x = pair.first.first;
		const auto old_y = pair.first.second;
		const auto new_x = pair.second.first;
		const auto new_y = pair.second.second;

		unsigned char pixels[3];

		this->oldImage->getPixel(old_x, old_y, pixels);
		this->newImage->putPixel(new_x, new_y, pixels);
	}
};