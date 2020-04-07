#include "reflection.h"
#include <cmath>

void Reflection::createMap()
{
    // vertical and horizontal reflection allowed for all bmp files
    // diagonal reflection allowed only for square ones
    for (int i = 0; i < this->oldImage->height; i++)
    {
        for (int j = 0; j < this->oldImage->width; j++)
        {
            switch (this->reflect_num)
            {
            case 0:
                // code for vertical mirror reflection
                break;
            case 1:
                // code for horizontal mirror reflection
                break;
            case 2:
                // code for diagonal mirror reflection #1
                break;
            case 3:
                // code for diagonal mirror reflection #2
                break;
            }

            //map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(int(round((x_n))), int(round(y_n)))));
        }
    }
};


void Reflection::processImage(int reflect_num)
{
    this->reflect_num = reflect_num;
    this->createMap();

    for (const auto& pair : this->map)
    {
        auto old_x = pair.first.first;
        auto old_y = pair.first.second;
        auto new_x = pair.second.first;
        auto new_y = pair.second.second;

        unsigned char pixels[3];

        this->oldImage->getPixel(old_x, old_y, pixels);
        this->newImage->putPixel(new_x, new_y, pixels);
    }
};