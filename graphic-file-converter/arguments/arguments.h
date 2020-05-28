//Created by Wojciech Nowicki
#pragma once
#include <vector>
#include <string>

class Arguments
{
	/*
	 Mother class for all types of arguments.
	 Each subclass contains arguments as attributes
	 needed to perform conversion.
	 //*/
public:
	const int number_of_arguments = 0;
	virtual int get_number_of_arguments();
	virtual void set_arguments(std::vector <double> args);
	Arguments() = default;
	std::vector<std::string>args;
	virtual std::vector<std::string> get_labels();
};
