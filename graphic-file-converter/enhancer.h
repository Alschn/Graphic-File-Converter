#pragma once
#include "converter.h"

class Enhancer : public Converter
{
public:
    static double truncate(double value);
    void negativeOfImage();
    void adjustBrightness(int brightness);
    void adjustContrast(int contrast);
    void adjustIntensity(int red, int green, int blue);
    using Converter::Converter;
};