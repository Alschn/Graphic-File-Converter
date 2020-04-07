#pragma once
#include <string>
#include <utility>


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
	unsigned char* header{};
	unsigned char* content;
	bool save_header{};


public:
	unsigned int width{};
	unsigned int height{};
	unsigned int row_size{};
	size_t file_size{};


	/*Specified modes*/
	ImageMode mode;
	ColorDepth depth;

	unsigned int buffer_size{};

	/*
	 * Offsets for BMP HEADER (windows header type)
	 */
	const size_t HEADER_SIZE = 54;
	const int FILE_SIZE_OFFSET = 2;
	const int WIDTH_OFFSET = 18;
	const int HEIGHT_OFFSET = 22;
	const int PIXEL_ARRAY_OFFSET = 10;
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
	void putPixel(int x, int y, unsigned char input[]);
	void putPixel(int x, int y, bool output);

	void resize(int width, int height);
	void setBufferSize();
	unsigned int calculatePadding();
	unsigned int calculateRowSize(); 

	/**
	 * \brief 
	 * \param width 
	 * \param bytes_per_pixel 
	 * \return 
	 */
	static unsigned int rowSize(const unsigned int width, const unsigned int bytes_per_pixel);
	static unsigned int rowPadding(const unsigned int width, const unsigned int bytes_per_pixel);


	// x coord, y coord, color: 0 - red, 1 - green, 2 - blue
	int calculatePixelIndex(int x, int y, int color = 0) const;

	void save(const std::string& path);
	std::string toStr() const;

private:
	void load();
public:
	Image(const std::string& path, const bool expect_saving, const ImageMode& m,
	      const ColorDepth& depth = ColorDepth::bpp24);

	Image(const Image& other);

	friend std::ostream& operator<<(std::ostream& os, const Image& im);

	~Image();
};
