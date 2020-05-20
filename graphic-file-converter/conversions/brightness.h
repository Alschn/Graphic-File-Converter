//Created by Adam Lisichin
#pragma once
#include "converter.h"

class Brightness : public Converter
{
public:
	using Converter::Converter;
	/**
	 * \brief Changes R, G, B values at once by a given integer
	 * \param args Integer in range [-255, 255]
	 */
	void processImage(Arguments* args) override;
};