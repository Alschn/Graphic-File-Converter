#pragma once
#include "converter.h"
#include <map>

class Reflection: public Converter
{
    private:
    std::map <std::pair<int, int>, std::pair<int, int>> map;
    void createMap();


    public:
    using Converter::Converter;
    void processImage(int reflect_num) override;
    int reflect_num;
};