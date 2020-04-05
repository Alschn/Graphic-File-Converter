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

	void getPixel(int x, int y, unsigned char (&output)[3], PixelMode mode = PixelMode::RGB) const;
	void putPixel(int x, int y, unsigned char (&input)[3]);

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
	
	Image();

	friend std::ostream& operator<<(std::ostream& os, const Image& im);

	~Image();
};
