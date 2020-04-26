#pragma once
#include "converter.h"

class Rescaler : public Converter
{
private:
	static double lerp(double s, double e, double t);
	static double blerp(double c00, double c10, double c01, double c11, double tx, double ty);

	using Converter::Converter;
};
