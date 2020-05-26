//Created by Gustaw Daczkowski
#include "file.h"
#include <fstream>

bool File::fileExists(const std::string& path)
{
	struct stat buffer{};
	return stat(path.c_str(), &buffer) == 0;
}

bool File::directoryExists(std::string& path)
{
	struct stat info{};
	if (stat(path.c_str(), &info) != 0)
		throw std::runtime_error("Directory: " + path + " is not accessible!;");
	if (info.st_mode & S_IFDIR)
		return true;
	throw std::runtime_error("Path: " + path + " is not a directory!;");
}

bool File::directoryExistsFromFile(const std::string& path_with_filename)
{
	const auto pos = path_with_filename.rfind('/');
	std::string path;
	if (pos == std::string::npos)
	{
		path = "./";
	}
	else
	{
		path = path_with_filename.substr(0, pos);
	}

	struct stat info{};
	if (stat(path.c_str(), &info) != 0)
		throw std::runtime_error("Directory: " + path + " is not accessible!;");
	if (info.st_mode & S_IFDIR)
		return true;
	throw std::runtime_error("Path: " + path + " is not a directory!;");
}

char* File::readBytesFromFile(const std::string& file_path, char* buffer, size_t size, const unsigned offset)
{
	if (!File::fileExists(file_path))
	{
		throw std::runtime_error("Provided file path does not exist");
	}
	std::ifstream file(file_path, std::ios_base::binary);
	file.seekg(offset);
	file.read(buffer, size);
	file.close();
	return buffer;
}
