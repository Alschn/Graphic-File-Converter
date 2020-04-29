#pragma once
#include "arguments.h"

class ScaleArguments: public Arguments
{
public:
	const int number_of_arguments = 2;
	int x;
	int y;
	using Arguments::Arguments;
	int get_number_of_arguments() override;
	void set_arguments(std::vector<double> args) override;
	ScaleArguments(const int x, const int y);

};