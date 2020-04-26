#include "rescaler.h"

double Lerp(double s, double e, double t)
{
	return s + (e - s) * t;
}

double Blerp(double c00, double c10, double c01, double c11, double tx, double ty)
{
	return Lerp(Lerp(c00, c10, tx), Lerp(c01, c11, tx), ty)
}