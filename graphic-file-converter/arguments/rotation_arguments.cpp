//Created by Wojciech Nowicki
#include "rotation_arguments.h"

int RotationArguments::get_number_of_arguments()
{
	return number_of_arguments;
}

void RotationArguments::set_arguments(std::vector<double> args)
{
	this->degrees = args[0];
}

std::vector<std::string> RotationArguments::get_labels()
{
	return arg_label;
}