#include "converter.h"



void Converter::saveImage(const std::string& path) const
{
	this->newImage->save(path);
}

