//Created by Gustaw Daczkowski
#pragma once
#include <string>
#include <map>

#include "image_file_types/file.h"
#include "image_content/image_content.h"
#include "image_content/bpp1.h"
#include "image_content/bpp24.h"
#include <functional>
#include <iostream>
#ifndef  CLASS_IMAGE
#define CLASS_IMAGE


class Image
{
private:
	std::string path; //path to the input .bmp
	ImageContent* content = nullptr;

public:
	unsigned int width = 0; // width in pixels
	unsigned int height = 0; // height in pixels
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

	bool getPixel(unsigned int x, unsigned int y) const;

	// ****getPixel variant with templates*****
	// template <class T>
	// struct item_return
	// {
	// 	typedef T type;
	// };
	//
	// template <class T>
	// typename item_return<T>::type getPixel1(unsigned int x, unsigned int y, uint8_t* output = nullptr);
	//
	// template <>
	// struct item_return<Bpp1>
	// {
	// 	typedef bool type;
	// };
	//
	// template <>
	// bool getPixel1<Bpp1>(unsigned int x, unsigned int y, uint8_t* output)
	// {
	// 	if (dynamic_cast<Bpp1*>(this->content))
	// 	{
	// 		uint8_t out;
	// 		this->content->getPixel(x, y, &out);
	// 		return out != 0;
	// 	}
	// 	throw std::runtime_error("This function call is allowed only for 1Bpp content type!");
	// }

	/**
	 * \brief Puts pixel into memory by given coordinates. This function is meant to be used for 24bit color space.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param input char array of RGB or BGR depending on specified mode
	 */
	void putPixel(unsigned int x, unsigned int y, unsigned char input[]);

	/*
	 * Variant for 1bpp with boolean
	 */
	void putPixel(unsigned int x, unsigned int y, bool value);

	/**
	 * \brief Resizes image and memory for new dimensions.
	 * \param width width in pixels
	 * \param height height in pixels
	 */
	void resize(unsigned int width, unsigned int height);

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
	void loadFromPath(const std::string& path);

public:
	//allow only image content
	template <typename T, typename = std::enable_if<std::is_base_of<ImageContent, T>::value>>
	static void registerImageContent(unsigned bpp)
	{
		Image::content_type_map[bpp] = []() -> ImageContent* { return new T(); };
	}

	template <typename T, typename = std::enable_if<std::is_base_of<File, T>::value>>
	static void registerFileType(std::string extension)
	{
		Image::file_type_map[extension] = []() -> File* { return new T(); };
	}

	static std::map<unsigned int, std::function<ImageContent*()>> content_type_map;
	static std::map<std::string, std::function<File*()>> file_type_map;

	static std::string getExtension(const std::string& path);

	unsigned int onePixelByteSize() const;

	ImageContent* getContent() const;
	
	Image() = default;

	Image(unsigned int content_type, unsigned int width, unsigned int height);

	Image(const std::string& path);

	Image(const Image& other);

	~Image();

	friend std::ostream& operator<<(std::ostream& os, const Image& im);
};
#endif
