#include "image.h"
#include <array>

#include "conversions/converter.h"
#include "font.h"

#pragma once
class ImageScanner: public Converter
{

	std::vector<Image* > letters;
	unsigned int padding;
	unsigned int threshold;
	
	void generateNewImages(const std::vector<std::pair<int, int >>& coordinates);
	
public:
	void loadImage(Image* im);

	void processImage(Arguments* args) override;

	void saveImage(std::string &path) const;

	void saveToBmp(std::string& path) const;

	ImageScanner() = default;
	~ImageScanner() override;
};

