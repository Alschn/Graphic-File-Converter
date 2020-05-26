//Created by Gustaw Daczkowski
#pragma once
#include <vector>
#include <regex>
#include "file.h"
#include "../utils.h"
#include "../font.h"


#ifndef  CLASS_HEADER_FILE
#define CLASS_HEADER_FILE



class HeaderFile :public File
{
private:
	const std::regex image_content_type = std::regex(R"(Bpp:\s*?(\d{1,2}))");
	const std::regex image_content_width = std::regex(R"(WIDTH:\s*(\d*))");
	const std::regex image_content_height = std::regex(R"(HEIGHT:\s*(\d*))");
	const std::regex letter_information = std::regex(R"****(\/\/\sChar:\s([A-Za-z0-9])\s\|\sW:\s(\d+)\s\|\sH:\s(\d+))****");
	std::string variable_name;
	std::string generateFileInfo();
	std::string generateFileInfo( std::string& font_name, int content_type, unsigned int width, unsigned int height,  std::string& variable_name, std::string& type) const;
	std::string generateFileContent(ImageContent *content, unsigned char letter = 0) const;
	static std::string pathToVariableName(const std::string& path);
	ImageContent* content = nullptr;
	const int bytes_per_row = 12;
	const std::string epilogue = "}\n#endif";
	static void saveStringToFile(const std::string& content, const std::string& path);
	
public:
	int letter = 0;
	ImageContent* loadForContent(const std::string& filename) override;
	virtual void save(ImageContent* content, const  std::string& path) override;
	void saveFont(std::vector<Image*> font, std::string& path) const;
	static std::vector<std::string> fileToLines(const std::string& filename);
	static unsigned char getLetterIndexFromFName(std::string& name);
	bool extractLetterInformation(std::string &line, unsigned char desired_letter, unsigned int &width, unsigned int &height) const;
	static std::string resolvePath(const std::string& path);

	~HeaderFile();

};



#endif
