#pragma once
#include <string>
#include <fstream>
#include <map>
#include "header_file.h"
#include "image_content.h"
#include <functional>


enum class ImageMode
{
	read_from_bmp,
	read_from_header_file,
};

enum class ColorDepth
{
	bpp24,
	bpp16,
	bpp8,
	bpp1,
};

enum class PixelMode
{
	rgb,
	bgr,
	mono_bw
};


class Image
{
private:
	std::string path; //path to the input .bmp
	ImageContent* content = nullptr;

public:
	unsigned int width{}; // width in pixels
	unsigned int height{}; // height in pixels
	ContentTypes content_type1;
	unsigned int channels = 0;
	
	/**
	 * \brief Gets pixel on specified index given by coordinates (x, y). Default orientation is: (0, 0) at the bottom left corner. Empty char array has to be supplied for the return value.
	 * For 24bit color spaces array has have 3 elements.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param output empty char array for output
	 * \param mode for color space if the color space has more than one color.
	 */
	void getPixel(int x, int y, unsigned char output[]) const;
	/**
	 * \brief Puts pixel into memory by given coordinates. This function is meant to be used for 24bit color space.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param input char array of RGB or BGR depending on specified mode
	 */
	void putPixel(int x, int y, unsigned char input[]);
	/**
	 * \brief Puts pixel into memory by given coordinates. This function is meant to be used for 1bpp color space.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param input bool for B/W pixel where True is White, False is Black
	 */

	/**
	 * \brief Resizes image and memory for new dimensions.
	 * \param width width in pixels
	 * \param height height in pixels
	 */
	void resize(int width, int height);

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
	static std::string getExtension(const std::string& path);

	Image() = default;

	Image(const std::string & path);
	
	Image(const std::string& path, const bool expect_saving, const ImageMode& m,
	      const ColorDepth& depth = ColorDepth::bpp24);

	static std::map<ContentTypes, std::function<ImageContent* ()>> content_type_map;
	static std::map<std::string, std::function<File* ()>> file_type_map;

	Image(const Image& other);

	~Image();

	friend std::ostream& operator<<(std::ostream& os, const Image& im);
};
