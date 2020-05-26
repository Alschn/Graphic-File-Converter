//Created by Adam Lisichin
#include "reflection.h"

std::map <std::pair<int, int>, std::pair<int, int>> Reflection::createMap(int height, int width, int num)
{
	std::map <std::pair<int, int>, std::pair<int, int>> map;
	// vertical and horizontal reflection allowed for all bmp files
	// diagonal reflection allowed only for square ones
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int x_n = j;
			int y_n = i;
			switch (num)
			{
			case 0:
				// vertical mirror reflection
				x_n = width - j - 1;
				break;
			case 1:
				// horizontal mirror reflection
				y_n = height - i - 1;
				break;
			case 2:
				// diagonal mirror reflection y = x ONLY FOR SQUARES
				x_n = i;
				y_n = j;
				break;
			case 3:
				// diagonal mirror reflection y = -x+height ONLY FOR SQUARES
				x_n = width - i - 1;
				y_n = height - j - 1;
				break;
			default:
				throw std::exception("Such number of reflection not associated!");
			}

			map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(x_n, y_n)));
		}
	}
	return map;
};


void Reflection::processImage(Arguments* args)
{
	ReflectionArguments* ref_args = dynamic_cast<ReflectionArguments*>(args);
	ref_args->reflection_number = static_cast<int>(ref_args->reflection_number);
	if (ref_args->reflection_number < 0)
	{
		throw std::invalid_argument("Rotation argument has to be positive numbers!");
	}
	
	// diagonal reflection allowed only for squares
	if (this->oldImage->width != this->oldImage->height && (ref_args->reflection_number == 2 || ref_args->reflection_number == 3))
	{
		throw std::invalid_argument("Diagonal reflection is not allowed for non-square bmp files");
	}

	auto map = this->createMap(this->oldImage->height, this->oldImage->width, ref_args->reflection_number);

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
};
