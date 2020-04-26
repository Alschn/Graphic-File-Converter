#pragma once

class Rescaler : public Converter
{
private:
	static double Lerp(double s, double e, double t);
	static double Blerp(double c00, double c10, double c01, double c11, double tx, double ty);

	using Converter::Converter;
};
