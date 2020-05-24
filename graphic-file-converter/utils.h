//Created by Gustaw Daczkowski
#pragma once
#include <vector>
#include <regex>

#ifndef UTILS_CLASS
#define UTILS_CLASS


class Utils
{
public:
	static unsigned int fourCharsToInt(const std::vector<unsigned char>& input, const int offset);
	static unsigned int fourCharsToInt(const char* input, const int offset);
	static void writeIntToCharBuffer(char* input, const unsigned int value, const unsigned int offset);
	static void writeIntToCharBuffer(uint8_t* input, const unsigned int value, const unsigned int offset);
	static void writeIntToCharBuffer(std::vector<uint8_t>& input, const unsigned int value, const unsigned int offset);
	static bool isBitSet(const char input, unsigned int position);
	static bool findMatch(const std::string& str, const std::regex r, std::string& output);
	static std::vector<std::string> splitString(const std::string& str, char delimiter);
	static unsigned int closestFourMultiple(const unsigned int input);
	static bool directoryExists(std::string& path);
};

#endif
