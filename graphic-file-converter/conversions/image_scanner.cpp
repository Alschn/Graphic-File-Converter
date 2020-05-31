//Created by Gustaw Daczkowski

#include "image_scanner.h"
#include "../image_file_types/header_file.h"
#include "../font.h"
#include "../image_file_types/bmp_file.h"
#include "../arguments/scanner_arguments.h"

void ImageScanner::generateNewImages(const std::vector<std::pair<int, int>>& coordinates)
{
	const auto color_arr_size = this->oldImage->onePixelByteSize();
	std::unique_ptr<unsigned char[]> colors = std::make_unique<unsigned char[]>(color_arr_size);

	for (const auto pair : coordinates)
	{
		auto im = new Image(1, pair.second + 2 * padding, this->oldImage->height);
		for (unsigned int j = 0; j < this->oldImage->height; ++j)
		{
			for (unsigned int i = 0; i < pair.second + 2 * padding; ++i)
			{
				this->oldImage->getPixel(i + pair.first - padding, j, colors.get());
				for (unsigned int k = 0; k < color_arr_size; ++k)
				{
					if (colors[k] < threshold)
					{
						im->putPixel(i, j, true);
						break;
					}
					im->putPixel(i, j, false);
				}
			}
		}
		letters.push_back(im);
	}
}

void ImageScanner::loadImage(Image* im)
{
	this->oldImage = im;
}

void ImageScanner::processImage(Arguments* args)
{
	ScannerArguments* scan_args = dynamic_cast<ScannerArguments*>(args);
	padding = scan_args->padding;
	threshold = this->oldImage->type >= 8 ? scan_args->treshold : 1;

	bool black_pixel_found = false;
	int letter_start_index = -1;
	int letter_width = -1;

	const unsigned int threshold = this->oldImage->type >= 8 ? 80 : 1;

	std::vector<std::pair<int, int>> found_images;

	const auto color_arr_size = this->oldImage->onePixelByteSize();
	std::unique_ptr<unsigned char[]> colors = std::make_unique<unsigned char[]>(color_arr_size);


	for (unsigned int i = 0; i < this->oldImage->width; ++i)
	{
		unsigned int j = 0;
		black_pixel_found = false;
		// std::fill(colors, colors + color_arr_size, 0); //fill color array with zeros to ensure correct loading

		while (j < this->oldImage->height && !black_pixel_found)
			//we scan each column and stop when we reach top or when black pixel occurs
		{
			this->oldImage->getPixel(i, j, colors.get());

			for (unsigned int k = 0; k < color_arr_size; ++k)
			{
				if (colors[k] < threshold)
				{
					black_pixel_found = true;
					if (letter_start_index == 0)
					{
						letter_start_index = i;
						letter_width = 0;
					}
					break; //if black pixel is found exit the loop and don't bother for other pixels
				}
			}
			++j;
		}
		if (black_pixel_found)
		{
			++letter_width;
		}
		else if (letter_start_index + letter_width == i)
		{
			found_images.emplace_back(std::make_pair(letter_start_index, letter_width));
			letter_start_index = 0;
			letter_width = 0;
		}
		else
		{
			letter_start_index = 0;
		}
	}
	generateNewImages(found_images);
}

void ImageScanner::saveImage(const std::string& path)
{
	const auto file = HeaderFile();
	auto n_p = path;
	n_p += ".h";
	file.saveFont(this->letters, n_p);
}

void ImageScanner::saveToBmp(std::string& path) const
{
	auto file = BmpFile();
	file.saveFont(this->letters, path);
}

ImageScanner::~ImageScanner()
{
	for (auto l : this->letters)
	{
		delete l;
	}
}
