#include "image.h"
#include <array>

#include "conversions/converter.h"
#include "font.h"

#pragma once
class ImageScanner: Converter
{

	Font *font;

	void generateNewImages(const std::vector<std::pair<int, int >>& coordinates);
	
public:
	void loadImage(Image* im);

	void processImage(Arguments* args) override;

	void saveImage(std::string &path);

	void saveToBmp(std::string& path) const;

	ImageScanner() = default;
	~ImageScanner() override;
};

