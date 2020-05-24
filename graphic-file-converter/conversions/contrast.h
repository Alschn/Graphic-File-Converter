//Created by Adam Lisichin
#pragma once
#include "converter.h"

class Contrast : public Converter
{
	using Converter::Converter;
	/**
	 * \brief Adjusts contrast using formula
	 * \param args Integer in range [0, 255]
	 */
	void processImage(Arguments* args) override;
};
