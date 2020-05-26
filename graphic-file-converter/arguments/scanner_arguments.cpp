//Created by Wojciech Nowicki
#include "scanner_arguments.h"

int ScannerArguments::get_number_of_arguments()
{
	return number_of_arguments;
}

void ScannerArguments::set_arguments(std::vector<double> args)
{
	this->padding = args[0];
	this->treshold = args[1];
}