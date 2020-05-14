//Created by Gustaw Daczkowski
#pragma once
#include <string>
#include <map>
#include "header_file.h"
#include "image_content.h"
#include <functional>

class Image
{
private:
	std::string path; //path to the input .bmp
	ImageContent* content = nullptr;

public:
	unsigned int width{}; // width in pixels
	unsigned int height{}; // height in pixels
	unsigned int channels = 0;
	unsigned int type = 0;
	/**
	 * \brief Gets pixel on specified index given by coordinates (x, y). Default orientation is: (0, 0) at the bottom left corner. Empty char array has to be supplied for the return value.
	 * For 24bit color spaces array has have 3 elements.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param output empty char array for output
	 * \param mode for color space if the color space has more than one color.
	 */
	void getPixel(unsigned int x, unsigned int y, unsigned char output[]) const;
	/**
	 * \brief Puts pixel into memory by given coordinates. This function is meant to be used for 24bit color space.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param input char array of RGB or BGR depending on specified mode
	 */
	void putPixel(unsigned int x, unsigned int y, unsigned char input[]);

	/**
	 * \brief Resizes image and memory for new dimensions.
	 * \param width width in pixels
	 * \param height height in pixels
	 */
	void resize(unsigned int width,unsigned int height);

	/**
	 * \brief Saves file.
	 * \param path Filepath where to save new image
	 */
	void save(const std::string& path) const;
	/**
	 * \brief Converts image to ASCII characters representing pixels.
	 * \return image as string
	 */
	std::string toStr() const;

private:
	void loadFromPath(const std::string &path);

public:
	static std::map<unsigned int, std::function<ImageContent* ()>> content_type_map;
	static std::map<std::string, std::function<File* ()>> file_type_map;
	static std::string getExtension(const std::string& path);

	static void registerImageContent(unsigned int bpp, std::function<ImageContent* ()> func);
	
	Image() = default;

	Image(const std::string & path);
	
	Image(const Image& other);

	~Image();

	friend std::ostream& operator<<(std::ostream& os, const Image& im);
};
