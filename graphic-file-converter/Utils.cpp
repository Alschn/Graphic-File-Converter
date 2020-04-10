#include "utils.h"

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

void Utils::writeIntToCharBufffer(char* input, unsigned int value, const unsigned int offset)
{
	memcpy(input + offset, &value, sizeof(value));
}

bool Utils::isBitSet(const char input, unsigned position)
{
	return (input & (1 << position));
}
