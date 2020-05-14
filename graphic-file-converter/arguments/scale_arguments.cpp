//Created by Wojciech Nowicki
#include "scale_arguments.h"

int ScaleArguments::get_number_of_arguments()
{
	return number_of_arguments;
}

void ScaleArguments::set_arguments(std::vector<double> args)
{
	this->x = args[0];
	this->y = args[1];
}
