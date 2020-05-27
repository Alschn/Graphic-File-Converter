//Created by Wojciech Nowicki
#include "contrast_arguments.h"

int ContrastArguments::get_number_of_arguments()
{
	return number_of_arguments;
}

void ContrastArguments::set_arguments(std::vector<double> args)
{
	this->contrast_value = args[0];
}


std::vector<std::string> ContrastArguments::get_labels()
{
	return arg_label;
}