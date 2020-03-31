#include "converter.h"



void Converter::saveImage(const std::string& path) const
{
	this->newImage->save(path);
}

void Converter::proccessImage(int angle)
{
    Rotation.angle = angle;
    for(const auto pair:Rotation.map)
    {
        auto old_x = pair.first.first;
        auto old_y = pair.first.second;
        auto new_x = pair.second.first;
        auto new_y = pair.second.second;
 
        unsigned char pixels[3];

        this->oldImage->getPixel(old_x, old_y, pixels);
        this->newImage->putPixel(new_x, new_y, pixels);
    }
}