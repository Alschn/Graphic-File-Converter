//Created by Wojciech Nowicki
#pragma once
#include "../conversions/converter.h"

class Parameter
{
/*
	Mother class for all parameters. Each subclass has different executeParam function.
 */
public:
	virtual void executeParam(Converter* conversion, std::string& output_path);
};
