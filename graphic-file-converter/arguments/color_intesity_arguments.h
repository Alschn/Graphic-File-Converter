//Created by Wojciech Nowicki
#pragma once
#include "arguments.h"

class ColorIntensityArguments : public Arguments
{
public:
	const int number_of_arguments = 3;
	int r;
	int g;
	int b;
	using Arguments::Arguments;
	int get_number_of_arguments() override;
	void set_arguments(std::vector<double> args) override;
};