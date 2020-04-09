#pragma once
#include <string>
#include <vector>

enum class ImageMode
{
	ReadFromBMP,
	ReadFromHeaderFile,
};

enum class ColorDepth
{
	bpp24,
	bpp8,
	bpp1,
};

enum class PixelMode
{
	RGB,
	BGR,
	MONOBW
};


class Image
{
private:
	std::string path;
	unsigned char* content;
	size_t buffer_size{};
	unsigned int pixel_array_offset{};
	

public:
	unsigned int width{};
	unsigned int height{};
	unsigned int row_size{};
	unsigned int horizontal_resolution{};
	unsigned int vertical_resolution{};
	
	size_t file_size{};


	/*Specified modes*/
	ImageMode mode = ImageMode::ReadFromBMP;
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
	const int BYTES_PER_PIXEL = 3;

	/**
	 * \brief Gets pixel on specified index given by coordinates (x, y). Default orientation is: (0, 0) at the bottom left corner. Empty char array has to be supplied for the return value.
	 * For 24bit color spaces array has have 3 elements.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param output empty char array for output
	 * \param mode for color space if the color space has more than one color.
	 */
	void getPixel(int x, int y, unsigned char output[], PixelMode mode = PixelMode::RGB) const;
	/**
	 * \brief Puts pixel into memory by given coordinates. This function is meant to be used for 24bit color space.
	 * \param x x coordinate
	 * \param y y coordinate
	 * \param input char array of RGB or BGR depending on specified mode
	 */
	void putPixel(int x, int y, unsigned char input[], PixelMode mode = PixelMode::RGB);
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
	 * \param bytes_per_pixel bytes per one pixel
	 * \return row size as an integer
	 */
	static unsigned int rowSize(const unsigned int width, const unsigned int bytes_per_pixel);

	/**
	 * \brief  Calculates padding for given width in pixels and bytes per pixel
	 * \param width width in pixels
	 * \param bytes_per_pixel bytes per one pixel
	 * \return padding as an integer
	 */
	static unsigned int rowPadding(const unsigned int width, const unsigned int bytes_per_pixel);

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
	void save(const std::string& path);
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

private:
	/**
	 * \brief Helper method that loads image from .bmp file into memory
	 */
	void loadFromFile();

	/**
	 * \brief Reads information from .bmp header in windows format (54 bytes) and saves it into class' memory (not all but certain parameters)
	 * \param header header as byte buffer from .bmp file
	 */
	void readHeader(const char* buffer);

	/**
	 * \brief Generates .bmp header in windows standard (54 bytes) from variables present in class scope
	 * \param input Input byte array for header
	 * \return 
	 */
	void generateHeader( char *input) const;

	/**
	 * \brief Reads specified number of bytes from file. The number of bytes is implicitly defined as a input buffer size
	 * \param file_path Path to file
	 * \param buffer Input buffer for which bytes will be written to
	 * \param size Size to read in bytes
	 * \param offset starting index
	 * \return pointer to the input buffer
	 */
	static char* readBytesFromFile(const std::string& file_path, char * buffer, size_t size, const unsigned int offset = 0);

	/**
	 * \brief Reads pixel array into memory
	 * \param buffer bytes to read 
	 */
	void readPixelArray(const char* buffer);
	
public:
	Image() = default;
	
	Image(const std::string& path, const bool expect_saving, const ImageMode& m,
	      const ColorDepth& depth = ColorDepth::bpp24);


	Image(const Image& other);

	~Image();

	friend std::ostream& operator<<(std::ostream& os, const Image& im);
	friend std::istream& operator>> (std::istream& is, Image& im);


};

