#pragma once
#include "parameter.h"

class DisplayParameter: public Parameter
{
public:
	using Parameter::Parameter;
	void executeParam(Image image) override;
};