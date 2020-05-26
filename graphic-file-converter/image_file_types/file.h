//Created by Gustaw Daczkowski
#pragma once
#include <string>
#include <utility>
#include "../image_content/image_content.h"

class File
{
protected:
	std::string name;
public:
	virtual ~File() = default;
	virtual ImageContent* loadForContent(const std::string& filename) = 0;
	virtual void save( ImageContent* content, const std::string &path) = 0;
	static char* readBytesFromFile(const std::string& file_path, char* buffer, size_t size, const unsigned int offset = 0);
	static bool fileExists(const std::string& path);
	static bool directoryExists(std::string& path);
	static bool directoryExistsFromFile(const std::string& path_with_filename);
	
	File() = default;;
};
