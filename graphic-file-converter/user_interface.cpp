#include <iostream>
#include "user_interface.h"
#include <map>
#include <string>
#include <regex>
#include <sstream>
#include <vector>
#include "image.h"
#include "converter.h"
#include <algorithm>

std::map <const std::string, Converter*> UserInterface::conversions_map;
std::map <const std::string, const std::string> UserInterface::help_map;
std::map <const std::string, std::regex> UserInterface::regex_map;
std::map <const std::string, int> UserInterface::number_of_command_arguments_map;

void UserInterface::registerAction(const std::string& command_name, const std::string& command_explanation, Converter* conversion, std::regex command_regex, int number_of_arguments)
{
	conversions_map.emplace(command_name, conversion);
	help_map.emplace(command_name, command_explanation);
	regex_map.emplace(command_name, command_regex);
	number_of_command_arguments_map.emplace(command_name, number_of_arguments);
}


void UserInterface::display()
{
    std::cout << "Welcome to Graphic File Converter" << std::endl;
    std::cout << "Please enter your command:" << std::endl;
    for (;;)
    {
        std::string command;
        std::getline(std::cin, command);
        std::regex choose_route_regex(R"###(^converter +load +('[^']\S+[^']') ?$)###");
        std::regex help_regex(R"(^converter +help *$)");
        std::smatch help_regex_matches;
        std::smatch choose_route_regex_matches;
        std::regex_search(command, help_regex_matches, help_regex);
        std::regex_search(command, choose_route_regex_matches, choose_route_regex);
        if (!choose_route_regex_matches.empty())
        {
            Converter* conversion;
            std::stringstream command_ss(command);
            std::vector<std::string> splitted;
            std::string buf_string;
            while (command_ss >> buf_string)
            {
                splitted.push_back(buf_string);
            }
            splitted[2].erase(splitted[2].begin());
            splitted[2].erase(splitted[2].end());
        	std::string input_path = splitted[2];
            Image image(input_path, 1, ImageMode::ReadFromBMP);
        ASK_LOOP:
            std::cout << "What do you want to do? (type one name of following functions)" << std::endl;
            for (auto a : help_map)
            {
                std::cout << a.first << std::endl;
            }
            std::string choose_command;
            std::cin >> choose_command;
            for (auto a : help_map)
            {
                if (a.first == choose_command)
                {
                ARGUMENT_LOOP:
                    int argument;
                    std::cout << "Enter argument:  ";
                    std::cin >> argument;
                    if (!argument)
                    {
                        std::cout << "Your argument is invalid, try again!" << std::endl;
                        goto ARGUMENT_LOOP;
                    }
                    conversion = conversions_map[choose_command];
                    conversion = new Converter(&image);
                    conversion->processImage(argument);
                    conversion->saveImage("CONVERTED" + input_path);
                }
                else
                {
                    std::cout << "You wrote command incorrectly, try again!" << std::endl;
                    goto ASK_LOOP;
                }
            }
        }
        else if (!help_regex_matches.empty())
        {
            std::cout << std::endl;
            showHelp();
        }
        else
        {
            for (auto command_name : regex_map)
            {
                std::smatch command_match;
                std::regex_search(command, command_match, command_name.second);
                if (!command_match.empty())
                {
                    std::stringstream command_ss(command);
                    std::vector<std::string> splitted;
                    std::string buf_string;
                    while (command_ss >> buf_string)
                    {
                        splitted.push_back(buf_string);
                    }
                    int argument;
                    for (auto m : splitted)
                    {
                        try
                        {
                            argument = std::stoi(m);
                        }
                        catch (...)
                        {
                            ;
                        }
                    }
                    splitted[3].erase(splitted[3].begin());
                    splitted[3].erase(splitted[3].end());
                    std::string input_path = splitted[3];
                    std::string output_path;
                    if (splitted.size() == 5)
                    {
                        splitted[4].erase(splitted[4].begin());
                        splitted[4].erase(splitted[4].end());
                        output_path = splitted[4];
                    }
                    else
                    {
                        output_path = "CONVERTED" + input_path;
                    }
                    executeAction(command_name.first, input_path, output_path, argument);
                    std::cout << "Action executed!" << std::endl;
                }
                else
                {
                    std::cout << std::endl;
                    std::cout << "There is no such command! Try again or type \"converter help\"" << std::endl;
                }
            }
        }
    }
}
void UserInterface::executeAction(const std::string& command, const std::string& path, const std::string& out_path, int argument)
{
    Image image(path, 1, ImageMode::ReadFromBMP, ColorDepth::bpp24);
    Converter* conversion = conversions_map[command];
    conversion = new Converter(&image);
    conversion->loadImage(&image);
    conversion->processImage(argument);
	conversion->saveImage(out_path);
}

void UserInterface::registerHelp(const std::string& command_name, const std::string& explanation)
{
    help_map.emplace(command_name, explanation);
}

void UserInterface::showHelp()
{
    std::cout << "Command structure:" << std::endl;
    std::cout << "converter [command_name] [argument] '[in_path]' {'[out_path]'}" << std::endl;
    std::cout << "( {} - possible, not needed, notice that not all functions need arguments )" << std::endl;
	for (int i = 0; i<90; i++)
	{
        std::cout << "=";
	}
    std::cout<<std::endl;
	std:: cout << "Possible commands: " << std::endl;
    for (auto explanation : help_map)
    {
        std::cout << explanation.first <<"   |   "<< explanation.second << std::endl;
    }
    std::cout << std::endl;
}