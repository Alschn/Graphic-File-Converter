//Created by Adam Lisichin
#pragma once
#include "converter.h"

class Intensity : public Converter
{
public:
	using Converter::Converter;
    /**
	* \brief Allows adjusting all of the colors individually
	* \param red Integer in range [-255, 255] - modifies R
	* \param green Integer in range [-255, 255] - modifies G
	* \param blue Integer in range [-255, 255] - modifies B
	*/
	void processImage(Arguments* args) override;

	
};