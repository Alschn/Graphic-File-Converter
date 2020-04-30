#pragma once
#include <string>
#include <utility>

#include "image_content.h"

class File
{
protected:
	std::string name;
public:
	virtual ~File() = default;
	virtual ImageContent* loadForContent(const std::string& filename) = 0;

	File() = default;;
};
