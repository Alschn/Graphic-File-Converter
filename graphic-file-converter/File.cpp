#include "file.h"

bool File::fileExists(const std::string& path)
{
	struct stat buffer {};
	return stat(path.c_str(), &buffer) == 0;
}
