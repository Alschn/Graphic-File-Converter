//Created by Adam Lisichin
#pragma once
#include "converter.h"

class Negative : public Converter
{
	using Converter::Converter;
	/**
	 * \brief Creates a negative of an image
	 */
	void processImage(Arguments* args) override;
	

};