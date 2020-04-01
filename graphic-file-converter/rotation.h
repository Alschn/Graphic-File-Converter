#pragma once
#include "converter.h"
#include <map>

class Rotation: public Converter
{
    private:
    std::map <std::pair<int, int>, std::pair<int, int>> map;
    void createMap();

    public:
    void processImage(int angle) override;
    int angle;
};
