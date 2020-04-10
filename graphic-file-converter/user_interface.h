#pragma once

#include <map>
#include <regex>
#include "converter.h"
#include "parameter.h"

class UserInterface
{
public:
	static std::map<const std::string, Converter*> conversions_map;
	static std::map<const std::string, const std::string> help_map;
	static std::map<const std::string, std::regex> regex_map;
	static std::map<const std::string, int> number_of_command_arguments_map;
	static std::map<const std::string, Parameter*> parameters_map;

	void registerAction(const std::string& command_name, const std::string& command_explanation, Converter* conversion,
	                    std::regex command_regex, int number_of_arguments);
	void display();
	Image executeAction(const std::string& command, const std::string& path, const std::string& out_path, int argument);
	void showHelp();
	void registerHelp(const std::string& command_name, const std::string& explanation);
	void displayImage(Image image);
	void registerParameter(const std::string name, Parameter* action);
};
