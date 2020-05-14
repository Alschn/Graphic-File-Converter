//Created by Wojciech Nowicki
#pragma once

#include <map>
#include <regex>
#include "converter.h"
#include "parameter.h"
#include "arguments.h"

class UserInterface
{
public:
	static std::map<const std::string, Converter*> conversions_map;
	static std::map<const std::string, const std::string> help_map;
	static std::map<const std::string, std::regex> regex_map;
	static std::map<const std::string, Arguments*> arguments_map;
	static std::map<const std::string, Parameter*> parameters_map;

	static void registerAction(const std::string& command_name, const std::string& command_explanation,
		Converter* conversion, const std::regex& command_regex, Arguments* arguments);
	void display(const std::string& command);
	static Image* executeAction(const std::string& command, const std::string& path, const std::string& out_path, Arguments* args);
	void showHelp();
	void registerHelp(const std::string& command_name, const std::string& explanation);
	void registerParameter(const std::string name, Parameter* action);
};

std::string argv_to_string(char *arg[], int number_of_arg);
bool check_regex_if_empty(std::regex reg, const std::string& command);
