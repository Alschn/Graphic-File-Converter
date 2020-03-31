#include "rotation.h"
#include <cmath>

void Rotation::createMap()
{   
    if (angle % 90 != 0)
    {
        // raise exception
    }
    if (angle > 360)
    {
        int multiple = angle / 360;
        angle = angle - multiple*360;
    }
    if (angle != 360 or angle != 0)
    {
    const double pi = std::acos(-1);
    double deg = angle * pi / 180;

    for (int i = 0; i < this->oldImage->height; i++)
    {
        for (int j = 0; j < this->oldImage->width; j++)
        {
            // rotation matrix
            int x_n = j * std::cos(-deg) -  i * std::sin(-deg);
            int y_n = j * std::sin(-deg) + i * std::cos(-deg);
            // translation vector
            switch (angle)
            {
            case 90:
                y_n += this->oldImage->width;
                break;
            case 180:
                y_n += this->oldImage->width;
                y_n += this->oldImage->height;
                break;
            case 270:
                x_n += this->oldImage->height;
                break;
            }
           
            map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(x_n, y_n)));
           
        }
    }
    }
};


// to jest źle
void Rotation::proccessImage(int angle)
{
    this->angle = angle;
    for(const auto pair:map)
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