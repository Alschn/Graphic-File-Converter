#include "font.h"
#include "utils.h"

Font::Font(std::vector<std::unique_ptr<Image>> letters): char_images(std::move(letters))
{
}

void Font::saveLetters(std::string& path)
{
	const auto font_name = extractFontName(path);
	Utils::directoryExists(path); //throws an exception if path does not exist
	const auto path_to_save = path + font_name + "_";
	generateAlphabet();
	for (unsigned int i = 0; i < char_images.size(); ++i)
	{
		char_images.at(i)->save(path_to_save + std::string(1, alphabet[i]) + ".bmp");
	}
}

void Font::generateAlphabet()
{
	unsigned int counter = 0;
	for (char i = 'A'; i <= 'Z'; ++i)
	{
		this->alphabet[counter] = i;
		counter++;
	}
	for (char i = '0'; i <= '9'; ++i)
	{
		this->alphabet[counter] = i;
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
