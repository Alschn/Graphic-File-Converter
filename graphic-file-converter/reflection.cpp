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
                if (this->reflect_type == "vertical")
                {
                    // code for vertical mirror reflection
                }
                else if (this->reflect_type == "horizontal")
                {
                    // code for horizontal mirror reflection
                }
                else if (this->reflect_type == "diagonal")
                {
                    // code for diagonal mirror reflection
                }

            }

                unsigned char colors[3] = { 0xAA, 0xBB, 0xAA };
                // this->newImage->putPixel(j, i, colors);
                // map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(int(round((x_n))), int(round(y_n)))));
        }
};


void Reflection::reflectImage(std::string reflect_type)
{
    this->reflect_type = reflect_type;
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
}