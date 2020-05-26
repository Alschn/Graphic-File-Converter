#include "font.h"

#include <utility>
#include "utils.h"
unsigned char Font::alphabet[char_count] = {};

Font::Font(std::vector<std::unique_ptr<Image>> letters): char_images(std::move(letters))
{
}


void Font::generateAlphabet()
{
	unsigned int counter = 0;
	for (char i = 'A'; i <= 'Z'; ++i)
	{
		Font::alphabet[counter] = i;
		counter++;
	}
	for (char i = '0'; i <= '9'; ++i)
	{
		Font::alphabet[counter] = i;
		counter++;
	}
}

std::string Font::extractFontName(std::string& path)
{
	auto left_bound = path.rfind('/');
	if (left_bound != std::string::npos)
	{
		auto name = path.substr(++left_bound, path.size() - left_bound);
		path = path.substr(0, left_bound);
		return name;
	}
	auto name = path;
	path = "./";
	return name;
}
