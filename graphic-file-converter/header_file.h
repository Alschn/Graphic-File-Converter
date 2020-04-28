#pragma once
#include <vector>
#include <regex>
#include "file.h"
#include "utils.h"
#include "image.h"

class HeaderFile :public File
{
private:
	const std::regex image_content_type = std::regex(R"(RES:\s*(\w{3}\d{1,2}))");
	const std::regex image_content_width = std::regex(R"(WIDTH:\s*(\d*))");
	const std::regex image_content_height = std::regex(R"(HEIGHT:\s*(\d*))");
	
public:
	int letter = 0;
	ImageContent * loadForContent(const std::string& filename) override;
	static std::vector<std::string> fileToLines(const std::string& filename);
	static int getLetterIndexFromFName(std::string &name);
};
