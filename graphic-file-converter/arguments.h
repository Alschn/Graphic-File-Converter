#pragma once
#include <vector>

class Arguments
{
public:
	const int number_of_arguments = 0;
	virtual int get_number_of_arguments();
	virtual void set_arguments(std::vector <double> args);
	Arguments() = default;
};