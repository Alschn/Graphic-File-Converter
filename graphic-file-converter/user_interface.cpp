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
    BEGIN:std::string command;
    std::cin >> command;
    std::smatch match;
    std::regex reg("^load [\S]+$");
    std::regex_search(command, match, reg);
    if (match.size()>0)
    {
        std::smatch match_path;
        std::regex reg_path("(?!load\b)\b\S+");
        std::regex_search(match, match_path, reg_path);
        Image image(match_path.str(), true, ImageMode::ReadFromBMP);
    }
    else if (command == "--help")
    {
        showHelp();
    }
    else
    {
        std::cout << "You need to load file first!" << std::endl;
        showHelp();
    }
    for (;;)
    {
        std::string next_command;
        std::cin >> next_command;
        std::smatch match_command;
        std::regex reg_command("(^load[\S]+$|^save[\S]+$|^display$|^--help$)");
        std::regex_search(next_command, match_command, reg_command);
        std::string command_match = match_command.str();
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