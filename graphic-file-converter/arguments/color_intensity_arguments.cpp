//Created by Wojciech Nowicki
#include "color_intesity_arguments.h"

int ColorIntensityArguments::get_number_of_arguments()
{
	return number_of_arguments;
}

void ColorIntensityArguments::set_arguments(std::vector<double> args)
{
	this->r = args[0];
	this->g = args[1];
	this->b = args[2];
}

std::vector<std::string> ColorIntensityArguments::get_labels()
{
	return arg_label;
}
