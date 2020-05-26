//Created by Wojciech Nowicki
#pragma once
#include "arguments.h"

class ScaleArguments: public Arguments
{
public:
	const int number_of_arguments = 2;
	double x;
	double y;
	using Arguments::Arguments;
	int get_number_of_arguments() override;
	void set_arguments(std::vector<double> args) override;
};
