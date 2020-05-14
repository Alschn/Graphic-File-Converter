//Created by Wojciech Nowicki
#include "reflection_arguments.h"

int ReflectionArguments::get_number_of_arguments()
{
	return number_of_arguments;
}

void ReflectionArguments::set_arguments(std::vector<double> args)
{
	this->reflection_number = args[0];
}
