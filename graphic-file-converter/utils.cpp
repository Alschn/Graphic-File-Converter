#include "utils.h"
#include <fstream>
#include <regex>
#include <sstream>

unsigned Utils::fourCharsToInt(const std::vector<unsigned char>& input, const int offset)
{
	unsigned int out = 0;
	for (int i = 0; i < 4; ++i)
	{
		out |= (input.at(offset + i)) << 8 * i;
	}
	return out;
}

unsigned Utils::fourCharsToInt(const char* input, const int offset)
{
	unsigned int out = 0;
	for (int i = 0; i < 4; ++i)
	{
		out |= static_cast<uint8_t>(input[offset + i]) << 8 * i;
	}
	return out;
}

void Utils::writeIntToCharBuffer(char* input, unsigned int value, const unsigned int offset)
{
	memcpy(input + offset, &value, sizeof(value));
}

void Utils::writeIntToCharBuffer(uint8_t* input, const unsigned value, const unsigned offset)
{
	memcpy(input + offset, &value, sizeof(value));
}

void Utils::writeIntToCharBuffer(std::vector<uint8_t> &input, const unsigned value, const unsigned offset)
{
	memcpy(input.data() + offset, &value, sizeof(value));
}

bool Utils::isBitSet(const char input, unsigned position)
{
	return (input & (1 << position));
}

bool Utils::findMatch(const std::string& str, const std::regex r, std::string& output)
{
	std::smatch matches;
	if (std::regex_search(str, matches, r))
	{
		output = matches.str(1);
		return true;
	}
	return false;
}

std::vector<std::string> Utils::splitString(const std::string& str, char delimiter)
{
	std::vector<std::string> output;

	std::stringstream stream(str);
	std::string token;

	while (std::getline(stream, token, delimiter))
		output.push_back(token);

	return output;
}

unsigned Utils::closestFourMultiple(const unsigned input)
{
	return (input + 3) & ~3;
}
