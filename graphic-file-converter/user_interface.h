#pragma once

#include <map>

#include "converter.h"


class UserInterface
{
public:
	static std::map<std::string, Converter*> conversions_map;
	static std::map<std::string, std::string> help_map;

	void registerAction(const std::string command_name, Converter* conversion);
	void display();
	void executeAction(const std::string& command);
	void showHelp();
	void registerHelp(std::string command, std::string command_explanation);
};
