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
	std::vector<std::string>arg_label{ "X (positive float)","Y (positive float)" };
	std::vector<std::string> get_labels() override;
};
