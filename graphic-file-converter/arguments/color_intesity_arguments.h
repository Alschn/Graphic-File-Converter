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
	std::vector<std::string>arg_label{ "R component (from -255 to 255)","G component (from -255 to 255)","B component (from -255 to 255)" };
	std::vector<std::string> get_labels() override;
};