//Created by Adam Lisichin
#pragma once
#include "converter.h"
#include <map>
#include "reflection_arguments.h"

class Reflection : public Converter
{
public:
	/**
	 * \brief Creates map which stores old and new coordinates calculated using self-written algorithm
	 * \param height Old Image's height
	 * \param width Old Image's width
	 * \param num Reflection type: 0 - vertical, 1 - horizontal, 2 - diagonal y=x, 3 - diagonal y=height-x
	 * \return Map with converted coordinates
	 */
	static std::map <std::pair<int, int>, std::pair<int, int>> createMap(int height, int width, int num);

	using Converter::Converter;

	/**
	 * \brief Using converted map, puts old pixels onto new Image in correct spots. Forbids using diagonal reflection on non-squares
	 * \param reflect_num Reflection type: 0 - vertical, 1 - horizontal, 2 - diagonal y=x, 3 - diagonal y=height-x
	 */
	void processImage(Arguments* args) override;

};
