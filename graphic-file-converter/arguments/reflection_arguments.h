//Created by Wojciech Nowicki
#pragma once
#include "arguments.h"

class ReflectionArguments: public Arguments
{
public:
	using Arguments::Arguments;
	int get_number_of_arguments() override;
	void set_arguments(std::vector<double> args) override;
	const int number_of_arguments = 1;
	int reflection_number;
	std::vector<std::string>arg_label{ "reflection number (0 - vertical, 1 - horizontal, 2 - y=x, 3 - y=h-x" };
	std::vector<std::string> get_labels() override;
};
