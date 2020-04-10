#pragma once
#include "converter.h"
#include <map>

class Rotation : public Converter
{
public:
	/**
	 * \brief Creates map which stores old and new coordinates calculated using rotation matrix and proper translation
	 * \param height Old Image's height
	 * \param width Old Image's width
	 * \param angle Angle to rotate the image by (90/180/270/360 and multiples of those angles)
	 * \return Map with converted coordinates; used later on in processImage
	 */
	static std::map <std::pair<int, int>, std::pair<int, int>> createMap(int height, int width, int angle);

	using Converter::Converter;
	/**
	 * \brief Resizes Image if angle is k*90 or k*270. Using converted map puts old pixels onto new Image in correct spots.
	 * \param angle Angle to rotate the image by (90/180/270/360 and multiples of those angles)
	 */
	void processImage(int angle) override;
	int angle;
};
