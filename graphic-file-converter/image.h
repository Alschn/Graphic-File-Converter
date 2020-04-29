#pragma once
#include <string>
#include <vector>

#include "image_content.h"

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
	// unsigned char* content; //pixel array
	size_t buffer_size{}; //internal buffer size in bytes
	unsigned int pixel_array_offset{}; //pixel array offset in BMP file
	unsigned int start_index = 0; //start index for read from memory mode
	ImageContent* content1;

public:
	unsigned int width{}; // width in pixels
	unsigned int height{}; // height in pixels
	unsigned int row_size{}; // row size in bytes 
	unsigned int horizontal_resolution = 3200; //experimental constants
	unsigned int vertical_resolution = 2300;

	size_t file_size{}; //bmp file size

	/*Specified modes*/
	ImageMode mode = ImageMode::read_from_bmp; // set, but not implemented yet
	ColorDepth depth = ColorDepth::bpp24;

	/*
	 * Offsets for BMP HEADER (windows header type)
	 */
	const size_t HEADER_SIZE = 54; // can be changed in future versions
	const int FILE_SIZE_OFFSET = 2;
	const int WIDTH_OFFSET = 18;
	const int HEIGHT_OFFSET = 22;
	const int HORIZONTAL_RESOLUTION_OFFSET = 38;
	const int VERTICAL_RESOLUTION_OFFSET = 42;
	const int PIXEL_ARRAY_OFFSET_INDEX = 10;

	const int BYTES_PER_PIXEL = 3; //for image from .bmp file mode

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
	void putPixel(int x, int y, unsigned char input[], PixelMode mode = PixelMode::rgb);
	/**
	 * \brief Puts pixel into memory by given coordinates. This function is meant to be used for 1bpp color space.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param input bool for B/W pixel where True is White, False is Black
	 */
	void putPixel(int x, int y, bool output);

	/**
	 * \brief Resizes image and memory for new dimensions. Clears content buffer.
	 * \param width width in pixels
	 * \param height height in pixels
	 */
	void resize(int width, int height);
	/**
	 * \brief Calculates internal buffersize for specified bytes per pixel, width [px] and height [px]
	 * \param bytes_per_pixel 
	 * \param width width in pixels
	 * \param height height in pixels
	 * \return buffer size for pixel array of given image represented as size_t.
	 */
	static size_t bufferSize(const unsigned int bytes_per_pixel, const unsigned int width, const unsigned int height);

	/**
	 * \brief Calculates row size for specified width and bytes per pixel
	 * \param width width in pixels
	 * \param depth	depth mode: 24bpp, 16bpp, 8bpp, or 1bpp
	 * \return row size as an integer
	 */
	static unsigned int rowSize(const unsigned int width, const ColorDepth& depth);

	/**
	 * \brief  Calculates padding for given width in pixels and bytes per pixel
	 * \param width width in pixels
	  * \param depth	depth mode: 24bpp, 16bpp, 8bpp, or 1bpp
	 * \return padding as an integer
	 */
	static unsigned int rowPadding(const unsigned int width, const ColorDepth& depth);

	/**
	 * \brief Used for RGB mode
	 * \param x x coordinate of a pixel
	 * \param y y coordinate of a pixel
	 * \param color 0 - red | 1 - green | 2 - blue
	 * \return correct index of a byte for pixel with corresponding color specified in color parameter
	 */
	int calculatePixelIndex(int x, int y, int color = 0) const;

	/**
	 * \brief Saves bmp into .bmp file from memory
	 * \param path Filepath where to save new image
	 */
	void save(const std::string& path) const;
	/**
	 * \brief Converts image to ASCII characters representing pixels.
	 * \return image as string
	 */
	std::string toStr() const;


	/**
	* \brief Check if file exists and is accessible
	* \param path file path
	* \return True or False
	*/
	static bool fileExists(const std::string& path);


	/**
	 * \brief Reads information from .bmp header in windows format (54 bytes) and saves it into class' memory (not all but certain parameters)
	 * \param header header as byte buffer from .bmp file
	 */
	void readHeader(const char* buffer);

	/**
	 * \brief Generates .bmp header in windows standard (54 bytes) from variables present in class scope
	 * \param input Input byte array for header
	 * \param bpp bits per pixel (default = 24)
	 * \param color_table char array of color table (little endian)
	 * \param color_table_size size of color table (minimal size is 8 for 1bpp)
	 */
	void generateHeader(char* input, uint8_t bpp = 24, char (*color_table) = nullptr,
	                    size_t color_table_size = 0) const;

	/**
	 * \brief Reads specified number of bytes from file. The number of bytes is implicitly defined as a input buffer size
	 * \param file_path Path to file
	 * \param buffer Input buffer for which bytes will be written to
	 * \param size Size to read in bytes
	 * \param offset starting index
	 * \return pointer to the input buffer
	 */
	static char* readBytesFromFile(const std::string& file_path, char* buffer, size_t size,
	                               const unsigned int offset = 0);

	/**
	 * \brief Reads pixel array into memory
	 * \param buffer bytes to read 
	 */
	void readPixelArray(const char* buffer);

private:
	/**
	 * \brief Generates byte content to by saved to .bmp file (uses header and content generator)
	* \return vector of chars to be written to file
	*/
	std::vector<char> generateContentToSave() const;

	/**
	* \brief Helper method that loads image from .bmp file into memory
	*/
	void loadFromFile();

	/**
	 * \brief Loads data from .header file
	 * \param input input buffer
	 * \param width width in pixels
	 * \param height height in pixels
	 * \param start_index starting index for buffer
	 * \param cd Color depth - default 1bpp
	 */
	void loadFromMemory(unsigned char* input, const unsigned int width, const unsigned int height,
	                    unsigned int start_index = 0, ColorDepth cd = ColorDepth::bpp1);

public:
	Image() = default;

	Image(const std::string & path);
	
	Image(unsigned char* content, const unsigned int width, const unsigned height, const unsigned int start_index = 0);

	Image(const std::string& path, const bool expect_saving, const ImageMode& m,
	      const ColorDepth& depth = ColorDepth::bpp24);

	static std::map<std::string, ImageContent*> type_map;


	Image(const Image& other);

	~Image();

	friend std::ostream& operator<<(std::ostream& os, const Image& im);
	friend std::istream& operator>>(std::istream& is, Image& im);
};
