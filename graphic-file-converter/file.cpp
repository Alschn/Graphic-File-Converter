#include "file.h"
#include <fstream>

bool File::fileExists(const std::string& path)
{
	struct stat buffer {};
	return stat(path.c_str(), &buffer) == 0;
}
char* File::readBytesFromFile(const std::string& file_path, char* buffer, size_t size, const unsigned offset)
{
	if(!File::fileExists(file_path))
	{
		throw std::runtime_error("Provided file path does not exist");
	}
	std::ifstream file(file_path, std::ios_base::binary);
	file.seekg(offset);
	file.read(buffer, size);
	file.close();
	return buffer;
}
