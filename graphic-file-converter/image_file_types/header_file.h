//Created by Gustaw Daczkowski
#pragma once
#include <vector>
#include <regex>
#include "file.h"
#include "../utils.h"
#include "../image.h"

class HeaderFile :public File
{
private:
	const std::regex image_content_type = std::regex(R"(RES:\s*\w{3}(\d{1,2}))");
	const std::regex image_content_width = std::regex(R"(WIDTH:\s*(\d*))");
	const std::regex image_content_height = std::regex(R"(HEIGHT:\s*(\d*))");
	std::string variable_name;
	std::string generateFileInfo() const;
	std::string generateFileInfo(const std::string& font_name, int content_type, unsigned int width, unsigned int height, const std::string& variable_name) const;
	std::string generateFileContent() const;
	static std::string pathToVariableName(const std::string path);
	ImageContent* content = nullptr;
	const int bytes_per_row = 12;
	
	
public:
	int letter = 0;
	ImageContent * loadForContent(const std::string& filename) override;
	void save( ImageContent* content, const std::string& path) override;
	static std::vector<std::string> fileToLines(const std::string& filename);
	static int getLetterIndexFromFName(std::string &name);

	~HeaderFile();
	
};
