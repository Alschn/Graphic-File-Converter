//Created by Wojciech Nowicki
#pragma once
#include "arguments.h"

class BrightnessArguments : public Arguments
{
public:
	const int number_of_arguments = 1;
	int brightness_level;
	using Arguments::Arguments;
	int get_number_of_arguments() override;
	void set_arguments(std::vector<double> args) override;
};