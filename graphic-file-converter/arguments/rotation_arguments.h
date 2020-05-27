//Created by Wojciech Nowicki
#pragma once
#include "arguments.h"

class RotationArguments : public Arguments
{
public:
	using Arguments::Arguments;
	int get_number_of_arguments() override;
	void set_arguments(std::vector<double> args) override;
	const int number_of_arguments = 1;
	int degrees;
	std::vector<std::string>arg_label{ "degrees (multiple of 90)" };
	std::vector<std::string> get_labels() override;
};
