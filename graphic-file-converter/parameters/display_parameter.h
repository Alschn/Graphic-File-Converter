//Created by Wojciech Nowicki 
#pragma once
#include "parameter.h"

class DisplayParameter : public Parameter
{
	/*
		Displays image in cmd.
	 */
public:
	using Parameter::Parameter;
	void executeParam(Converter* conversion, std::string& output_path) override;
};
