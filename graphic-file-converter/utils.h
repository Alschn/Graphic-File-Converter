#pragma once
#include <vector>

class Utils
{
public:
	static unsigned int fourCharsToInt(const std::vector<unsigned char>& input,const int offset)
	{
		unsigned int out=0; 
		for(int i = 0; i<4; ++i)
		{
			out |= (input.at(offset + i)) << 8 * i;
		}
		return out;
	}
	
	
};

