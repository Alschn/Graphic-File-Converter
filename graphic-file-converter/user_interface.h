#pragma once
#include "converter.h"
#include <map>


class UserInterface
{

public:
	static std::map <std::string, Converter*> conversions_map;

	void registerAction(const std::string command_name, Converter *conversion);
	void display();
	void executeAction(const std::string& command);
	void showHelp();
};

	