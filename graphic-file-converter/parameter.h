//Created by Wojciech Nowicki
#pragma once
#include "image.h"

class Parameter
{
/*
	Mother class for all parameters. Each subclass has different executeParam function.
 //*/
public:
	virtual void executeParam(Image* image);
};
