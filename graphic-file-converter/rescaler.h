#pragma once
#include "converter.h"

class Rescaler : public Converter
{
	/**
	 * \brief 
	 * \param s 
	 * \param e 
	 * \param t 
	 * \return Interpolated value
	 */
	static double linearInterpolation(double s, double e, double t);

	/**
	 * \brief Takes 4 points and uses the linear interpolation on them for more accurate calculations
	 * \param c00 color of the first pixel
	 * \param c10 color of the second pixel
	 * \param c01 color of the third pixel
	 * \param c11 color of the fourth pixel
	 * \param tx Difference between gx and gx cast to int
	 * \param ty Difference between gy and gy cast to int
	 * \return Value after bilinear interpolation
	 */
	static double bilinearInterpolation(double c00, double c10, double c01, double c11, double tx, double ty);

	/**
	 * \brief Scaling function implementation
	 * \param scale_x New width is equal to old width multiplied by this constant
	 * \param scale_y New height is equal to old width multiplied by this constant
	 */
	void scaleImage(double scale_x, double scale_y);

	using Converter::Converter;
};
