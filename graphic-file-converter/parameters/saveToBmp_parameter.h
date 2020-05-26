//Created by Wojciech Nowicki 
#pragma once
#include "parameter.h"

class SaveToBmpParameter : public Parameter
{
	/*
		Displays image in cmd.
	 //*/
public:
	using Parameter::Parameter;
	void executeParam(Converter* conversion, std::string& output_path) override;
};