#pragma once
#include <vector>

#ifndef UTILS_CLASS
#define UTILS_CLASS


class Utils
{
public:
	static unsigned int fourCharsToInt(const std::vector<unsigned char>& input, const int offset);
	static unsigned int fourCharsToInt(const char *input, const int offset);
	static void writeIntToCharBufffer(char* input, const unsigned int value, const unsigned int offset);
};

#endif

