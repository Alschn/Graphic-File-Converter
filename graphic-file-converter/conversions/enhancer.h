//Created by Adam Lisichin
#pragma once
#include "converter.h"

class Enhancer : public Converter
{
public:
	/**
     * \brief Checks if value fits within color 0 and 255 
     * \param value Number to be checked whether it fits in range [0, 255]
     * \return Value in range
     */
    static double checkColorRange(double value);
	
	/**
     * \brief Creates a negative of an image
     */
    void negativeOfImage();
	
	/**
     * \brief Changes R, G, B values at once by a given integer
     * \param brightness Integer in range [-255, 255]
     */
    void adjustBrightness(int brightness);
	
	/**
     * \brief Adjusts contrast using formula
     * \param contrast Integer in range [-255, 255]
     */
    void adjustContrast(int contrast);
	
	/**
     * \brief Allows adjusting all of the colors individually
     * \param red Integer in range [-255, 255] - modifies R
     * \param green Integer in range [-255, 255] - modifies G
     * \param blue Integer in range [-255, 255] - modifies B
     */
    void adjustIntensity(int red, int green, int blue);

    using Converter::Converter;
};
