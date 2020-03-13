#include "TestExample.h"

#include <stdexcept>

int test_example::divide(int a, int b)
{
	if (b == 0)
		throw std::invalid_argument("Divide by zero exception");
	return a / b;
}

int test_example::multiply(int a, int b)
{
	return a * b;
}
