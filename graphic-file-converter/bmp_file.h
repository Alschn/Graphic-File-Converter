#pragma once
#include <vector>

#include "file.h"
class BmpFile :public File
{
private:
	static char* readBytesFromFile(const std::string& file_path, char* buffer, size_t size, const unsigned int offset = 0);
	const size_t HEADER_SIZE = 54; // can be changed in future versions

public:
	ImageContent* loadForContent(const std::string& filename) override;
	void save(ImageContent* content, const std::string& path) override;
};

