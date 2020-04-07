#include <iostream>
#include "user_interface.h"
#include <map>
#include <string>
#include <regex>
#include <sstream>
#include <vector>
#include "image.h"
#include "converter.h"

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
        std::regex choose_route_regex(R"(^converter +load +[\S] +$)");
        std::smatch choose_route_regex_matches;
        std::regex_search(command, choose_route_regex_matches, choose_route_regex);
    	if (choose_route_regex_matches.ready() == true)
    	{
            std::cout << "Sciezka za raczke!" << std::endl;
        }
        else
        {
            std::smatch command_match;
        	for(auto command_name:regex_map)
	        {
                std::regex_search(command, command_match, command_name.second);
        		if(command_match.ready()==true)
        		{
                    std::stringstream command_ss(command);
                    std::vector<std::string> splitted;
                    std::string buf_string;
        			while(command_ss>>buf_string)
        			{
                        splitted.push_back(buf_string);
        			}
                    std::vector<int> arguments;
                    for (auto m : splitted)
                    {
                        try
                        {
                            int argument = std::stoi(m);
                            arguments.push_back(argument);
                        }
                        catch (...)
                        {
                            ;
                        }	
                    }        				


        			
        		}
                else
                {
                    showHelp();
                }
	        }
        }


    }
}

void UserInterface::executeAction(const std::string& command, const std::string& path, const std::string& out_path)
{
    Image image(path, 1, ImageMode::ReadFromBMP, ColorDepth::bpp24);
	Converter* conversion = conversions_map[command];
    conversion->loadImage(&image);
    //conversion.processImage(arguments);
	conversion->saveImage(out_path);
}

void UserInterface::registerHelp(const std::string& command_name, const std::string& explanation)
{
    help_map.emplace(command_name, explanation);
}

void UserInterface::showHelp()
{
    std::cout << "Command structure:" << std::endl;
    std::cout << "converter command_name arguments 'in_path' ['out_path']" << std::endl;
    std::cout << "[] - possible, not needed, notice that not all functions need arguments" << std::endl;
	std:: cout << "Possible commands: " << std::endl;
    for (auto explanation : help_map)
    {
        std::cout << explanation.first << "    " << explanation.second << std::endl;
    }
}