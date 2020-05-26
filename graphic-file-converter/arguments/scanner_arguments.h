//Created by Wojciech Nowicki
#pragma once
#include "arguments.h"

class ScannerArguments : public Arguments
{
public:
	const int number_of_arguments = 2;
	int padding;
	int treshold;
	using Arguments::Arguments;
	int get_number_of_arguments() override;
	void set_arguments(std::vector<double> args) override;
};