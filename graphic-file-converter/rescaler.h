#pragma once
#include "converter.h"

class Rescaler : public Converter
{
	/**
	 * \brief Linear interpolation implementation
	 * \param s First input
	 * \param e Second input
	 * \param t Parameter in the closed unit interval [0, 1]
	 * \return Interpolated value of two input values
	 */
	static double linearInterpolation(double s, double e, double t);

	/**
	 * \brief Takes 4 points and uses the linear interpolation on them for more accurate calculations (2D interpolation)
	 * \param c00 color of the first pixel
	 * \param c10 color of the second pixel
	 * \param c01 color of the third pixel
	 * \param c11 color of the fourth pixel
	 * \param tx Difference between gx and gx cast to int
	 * \param ty Difference between gy and gy cast to int
	 * \return Value after bilinear interpolation
	 */
	static double bilinearInterpolation(double c00, double c10, double c01, double c11, double tx, double ty);

	using Converter::Converter;

	/**
	 * \brief Scaling function implementation
	 * \param args New width, height are equal to old ones multiplied by this constant
	 */
	void processImage(Arguments* args) override;

};
