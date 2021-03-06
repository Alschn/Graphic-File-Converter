//Created by Gustaw Daczkowski

#include "../image.h"
#include <array>
#include "converter.h"
#include "../font.h"

#pragma once
class ImageScanner : public Converter
{
	std::vector<Image*> letters;
	unsigned int padding;
	unsigned int threshold;

	void generateNewImages(const std::vector<std::pair<int, int>>& coordinates);

public:
	void loadImage(Image* im);

	void processImage(Arguments* args) override;

	void saveImage(const std::string& path) override;

	void saveToBmp(std::string& path) const;

	ImageScanner() = default;
	~ImageScanner() override;
};
