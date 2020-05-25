//Created by Wojciech Nowicki
#include "brightness_arguments.h"

int BrightnessArguments::get_number_of_arguments()
{
	return number_of_arguments;
}

void BrightnessArguments::set_arguments(std::vector<double> args)
{
	this->brightness_level = args[0];
}