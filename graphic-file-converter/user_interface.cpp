#include <iostream>
#include "user_interface.h"
#include <map>
#include <string>
#include <regex>

std::map<std::string, Converter*> UserInterface::conversions_map;
std::map <std::string, std::string> UserInterface::help_map;

void UserInterface::registerAction(const std::string& command_name, const std::string& command_explanation, Converter *conversion)
{
    conversions_map.emplace(command_name, conversion);
    help_map.emplace(command_name, command_explanation);
}


void UserInterface::display()
{
    Image image;
    std::cout << "Welcome to file converter!" << std::endl;
    std::cout << "Type command or --help to get commands examples" << std::endl;
    std::string command;
    std::getline(std::cin, command);
	std::regex reg(R"(^load \S+$)");
	std::smatch match;
    std::regex_search(command, match, reg);
    for(auto x: match)
    {
        std::cout << x << std::endl;
    }
}

void UserInterface::executeAction(const std::string& command)
{
   
}

void UserInterface::registerHelp(const std::string& command_name, const std::string& explanation)
{
    help_map.emplace(command_name, explanation);
}

void UserInterface::showHelp()
{
    std:: cout << "Possible commands: " << std::endl;
    for (auto explanation : help_map)
    {
        std::cout << explanation.first << "    " << explanation.second << std::endl;
    }
}