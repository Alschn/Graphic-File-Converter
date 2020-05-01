#include "image.h"
#include <map>
#include "bmp_file.h"
#include "bpp24.h"


void Image::getPixel(int x, int y, unsigned char output[]) const
{
	this->content->getPixel(x, y, output);
}

void Image::putPixel(int x, int y, unsigned char input[])
{
	this->content->putPixel(x, y, input);
}

void Image::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	this->content->resize(width, height);
}

void Image::save(const std::string& path) const
{
	const auto extension = this->getExtension(path);
	auto file = Image::file_type_map[extension];
	file->save(this->content, path);
}

std::string Image::toStr() const
{
	return this->content->toString();
}

void Image::loadFromPath(const std::string &path)
{
	this->path = path;
	const auto extension = this->getExtension(this->path);

	auto file = Image::file_type_map[extension];
	this->content = file->loadForContent(this->path);

	this->content_type = this->content->getType();
	this->width = this->content->getWidth();
	this->height = this->content->getHeight();
	this->channels = this->content->getChannels();
}

std::string Image::getExtension(const std::string& path)
{
	const auto pos = path.rfind('.');
	if (pos == std::string::npos)
		throw std::runtime_error("Provided path is invalid!");

	const auto end_of_extension = path.rfind('_');
	if (end_of_extension != std::string::npos)
	{
		return path.substr(pos, end_of_extension - pos);
	}
	return path.substr(pos);
}


Image::Image(const std::string& path)
{
	this->loadFromPath(path);
}


Image::Image(const std::string& path, const bool expect_saving, const ImageMode& m,
             const ColorDepth& depth) : path(path), mode(m), depth(depth)
{
	this->loadFromPath(path);
}

Image::Image(const Image& other) : mode(other.mode), depth(other.depth)
{
#ifdef _DEBUG
	std::cout << "Inside copy constructor of class Image" << std::endl;
#endif

	this->width = other.width;
	this->height = other.height;
	this->buffer_size = other.buffer_size;
	this->row_size = other.row_size;
	this->pixel_array_offset = other.pixel_array_offset;
	this->horizontal_resolution = other.horizontal_resolution;
	this->vertical_resolution = other.vertical_resolution;
	this->file_size = other.file_size;
	this->depth = other.depth;
	this->content = other.content->clone();
}

Image::~Image()
{
	if (this->depth != ColorDepth::bpp1)
		delete[] this->content;
}

std::ostream& operator<<(std::ostream& os, const Image& im)
{
	os << im.toStr();
	return os;
}

std::istream& operator>>(std::istream& is, Image& im)
{
	// char* header = new char[im.HEADER_SIZE];
	// is.read(header, im.HEADER_SIZE);
	// im.readHeader(header);
	// delete[] header;
	//
	// is.seekg(im.HEADER_SIZE);
	//
	// char* pixel_array_buffer = new char[im.file_size - im.HEADER_SIZE];
	// is.read(pixel_array_buffer, im.file_size - im.HEADER_SIZE);
	// im.readPixelArray(pixel_array_buffer);
	// delete[] pixel_array_buffer;
	//
	return is;
}

std::map<std::string, ImageContent*> Image::type_map = { {"Bpp1", new Bpp1()}, {"Bpp24", new Bpp24()} };
std::map<std::string, File*> Image::file_type_map = {{".h", new HeaderFile()}, {".bmp", new BmpFile()}};
