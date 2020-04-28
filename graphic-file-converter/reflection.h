#pragma once
#include "converter.h"
#include <map>

class Reflection : public Converter
{
public:
	static std::map<std::pair<int, int>, std::pair<int, int>> create_map(int num, int height, int width);

	using Converter::Converter;
	void processImage(int reflect_num) override;
};
