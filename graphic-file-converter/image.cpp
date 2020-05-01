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

std::vector<char> Image::generateContentToSave() const
{
	std::vector<char> output;
	// switch (this->depth)
	// {
	// case ColorDepth::bpp24:
	// 	{
	// 		char buf[54];
	// 		this->generateHeader(buf);
	//
	// 		output.reserve(this->HEADER_SIZE + this->row_size * this->height);
	// 		output.insert(output.end(), buf, buf + this->HEADER_SIZE);
	// 		for (int j = 0; j < this->height; ++j)
	// 		{
	// 			for (int i = 0; i < this->width; ++i)
	// 			{
	// 				unsigned char px[3];
	// 				this->getPixel(i, j, px, PixelMode::bgr);
	//
	// 				for (auto c : px)
	// 				{
	// 					output.emplace_back(c);
	// 				}
	// 			}
	// 			for (int i = 0; i < (Image::rowPadding(this->width, this->depth)); ++i)
	// 			{
	// 				output.push_back(0);
	// 			}
	// 		}
	// 		break;
	// 	}
	// case ColorDepth::bpp1:
	// 	{
	// 		auto* buf = new unsigned char[this->HEADER_SIZE + 8];
	//
	// 		char color_table[8] = {0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00};
	// 		this->generateHeader(reinterpret_cast<char*>(buf), 1, color_table, 8);
	//
	// 		output.reserve(this->file_size);
	// 		output.insert(output.end(), buf, buf + this->HEADER_SIZE + 8);
	//
	// 		delete[] buf;
	// 		for (int k = this->height - 1 + this->start_index; k >= 0 + this->start_index; --k)
	// 		{
	// 			for (int i = 0; i < 4; i++)
	// 			{
	// 				output.emplace_back(static_cast<char>(this->content[k * this->row_size + i]));
	// 			}
	// 		}
	// 		break;
	// 	}
	// default:
	// 	break;
	// }
	// return output;

	return output;
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


char* Image::readBytesFromFile(const std::string& file_path, char* buffer, size_t size, const unsigned int offset)
{
	std::ifstream file(file_path, std::ios_base::binary);
	file.seekg(offset);
	file.read(buffer, size);
	file.close();
	return buffer;
}

Image::Image(const std::string& path)
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

// Image::Image(unsigned char* content, const unsigned width, const unsigned height, const unsigned start_index)
// {
// 	this->depth = ColorDepth::bpp1;
// 	this->start_index = start_index;
// 	this->loadFromMemory(content, width, height, start_index, ColorDepth::bpp1);
// }


Image::Image(const std::string& path, const bool expect_saving, const ImageMode& m,
             const ColorDepth& depth) : path(path), mode(m), depth(depth)
{
	// if (!Image::fileExists(path))
	// {
	// 	throw std::exception("Image with specified input path does not exist!");
	// }

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
