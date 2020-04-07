#pragma once
#include "converter.h"
#include <map>

class Rotation: public Converter
{
    private:
    std::map <std::pair<int, int>, std::pair<int, int>> map;
    std::map <std::pair<int, int>, std::pair<int, int>> create_map();

    
    public:
    using Converter::Converter;
	void processImage(int angle) override;
    int angle;
};
