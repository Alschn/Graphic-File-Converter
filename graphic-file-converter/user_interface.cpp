#include <iostream>
#include "user_interface.h"
#include <map>
#include <string>

std::map<std::string, Converter*> UserInterface::conversions_map;
std::map <std::string, std::string> UserInterface::help_map;

void UserInterface::registerAction(const std::string command_name, Converter *conversion)
{
    conversions_map.emplace(command_name, conversion);
}


void UserInterface::display()
{
    std::cout << "Welcome to file converter!" << std::endl;
    std::cout << "Type command or --help to get commands examples" << std::endl;
    std::string command;
    for (;;)
    {
        std::cin >> command;

        if (conversions_map.find(command) != conversions_map.end())
        {
            executeAction(command);
        }
        else if (command == "--help")
        {
            showHelp();
        }
        else
        {
            std::cout << "There is no such function!" << std::endl;
            showHelp();
        }
    }
}

void UserInterface::executeAction(const std::string& command)
{
   
}

void UserInterface::showHelp()
{
    std:: cout << "Possible commands: " << std::endl;
    for (auto explanation : help_map)
    {
        std::cout << explanation.first << "    " << explanation.second << std::endl;
    }
}

void UserInterface::registerHelp(std::string command, std::string command_explanation)
{
    help_map.emplace(command, command_explanation);
}
