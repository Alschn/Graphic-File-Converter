#pragma once
#include "converter.h"
#include <map>

class Rotation: public Converter
{
public:
    static std::map <std::pair<int, int>, std::pair<int, int>> create_map(int height, int width, int angle);

    using Converter::Converter;
	void processImage(int angle) override;
    int angle;
};
