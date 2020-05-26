#pragma once
#include <memory>
#include <vector>

#include "image.h"

class Font
{
public:
	static const int char_count = 36;
	const int letter_count = 26;
	const int digit_count = 10;
	static unsigned char alphabet[char_count];

	std::vector<std::unique_ptr<Image>> char_images;
	Font(std::vector<std::unique_ptr<Image>> letters);
	void saveLetters(std::string& path);

public:
	static void generateAlphabet();
	static std::string extractFontName(std::string& path);
};
