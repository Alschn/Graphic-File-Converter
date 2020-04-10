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
#include "parameter.h"

std::map<const std::string, Converter*> UserInterface::conversions_map;
std::map<const std::string, const std::string> UserInterface::help_map;
std::map<const std::string, std::regex> UserInterface::regex_map;
std::map<const std::string, int> UserInterface::number_of_command_arguments_map;
std::map<const std::string, Parameter*> UserInterface::parameters_map;

void UserInterface::registerAction(const std::string& command_name, const std::string& command_explanation,
                                   Converter* conversion, std::regex command_regex, int number_of_arguments)
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
		std::regex choose_route_regex(R"###(^converter +load +(('|")[^']\S+[^']('|")) ?$)###");
		std::regex help_regex(R"(^converter +help *$)");
		std::smatch help_regex_matches;
		std::smatch choose_route_regex_matches;
		std::regex_search(command, help_regex_matches, help_regex);
		std::regex_search(command, choose_route_regex_matches, choose_route_regex);
		if (!choose_route_regex_matches.empty())
		{
			std::stringstream command_ss(command);
			std::vector<std::string> splitted;
			std::string buf_string;
			while (command_ss >> buf_string)
			{
				splitted.push_back(buf_string);
			}
			splitted[2].erase(splitted[2].begin());
			splitted[2].erase(splitted[2].end() - 1, splitted[2].end());
			std::string input_path = splitted[2];
			Image image(input_path, 1, ImageMode::read_from_bmp);
		ASK_LOOP:
			std::cout << "What do you want to do? (type one name of following functions)" << std::endl;
			for (auto a : help_map)
			{
				std::cout << a.first << std::endl;
			}
			std::string choose_command;
			std::cin >> choose_command;
			for (auto choosen_command : help_map)
			{
				if (choosen_command.first == choose_command)
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
				PARAM_LOOP:
					std::cout << "Any parameter? (if not type -)" << std::endl;
					for (auto parameter : parameters_map)
					{
						std::cout << parameter.first << std::endl;
					}
					std::string parameter;
					std::cin >> parameter;
					if (parameter == "-")
					{
						conversions_map[choose_command]->loadImage(&image);
						conversions_map[choose_command]->processImage(argument);
					}
					for (auto a : parameters_map)
					{
						if (a.first == parameter)
						{
							conversions_map[choose_command]->loadImage(&image);
							conversions_map[choose_command]->processImage(argument);
							parameters_map[parameter]->executeParam(image);
						}
						else
						{
							std::cout << "Wrong parameter, try again!" << std::endl;
							goto PARAM_LOOP;
						}
					}
					std::cout << "Do you want to save file ? [y/n]" << std::endl;
					std::string decision;
					std::cin >> decision;

					if (decision == "y")
					{
						std::cout << "Out path" << std::endl;
						std::string out_path;
						std::getline(std::cin, out_path);
						conversions_map[choose_command]->saveImage(out_path);
					}
					else
					{
						;
					}
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
			int no_function = 0;
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
					splitted[3].erase(splitted[3].end() - 1, splitted[3].end());
					std::string input_path = splitted[3];
					std::string output_path;
					if (splitted.size() > 4)
					{
						splitted[4].erase(splitted[4].begin());
						splitted[4].erase(splitted[4].end() - 1, splitted[4].end());
						output_path = splitted[4];
					}
					else
					{
						for(int i = input_path.size()-1; i>0;i--)
						{
							if(input_path[i]=='.')
							{
								output_path = input_path;
								output_path = output_path.insert(i, "_out");
								break;
							}							
						}
					}
					for (auto param : parameters_map)
					{
						if (std::find(splitted.begin(), splitted.end(), param.first) != splitted.end())
						{
							param.second->executeParam(
								executeAction(command_name.first, input_path, output_path, argument));
						}
						else
						{
							executeAction(command_name.first, input_path, output_path, argument);
						}
					}
					std::cout << "Action executed!" << std::endl;
					break;
				}
				else
				{
					no_function++;
				}
			}
			if (no_function = conversions_map.size())
			{
				std::cout << std::endl;
				std::cout <<
					"There is no such command or you made spelling mistake! Try again or type \"converter help\"" << std
					::endl;
			}
		}
	}
}

Image UserInterface::executeAction(const std::string& command, const std::string& path, const std::string& out_path,
                                   int argument)
{
	Image image(path, 1, ImageMode::read_from_bmp, ColorDepth::bpp24);
	Converter* conversion = conversions_map[command];
	conversion->loadImage(&image);
	conversion->processImage(argument);
	conversion->saveImage(out_path);
	return image;
}

void UserInterface::registerHelp(const std::string& command_name, const std::string& explanation)
{
	help_map.emplace(command_name, explanation);
}

void UserInterface::showHelp()
{
	std::cout << "Command structure:" << std::endl;
	std::cout << "converter [command_name] [argument] ['in_path'] {'out_path'} {-parameter}" << std::endl;
	std::cout << "( {} - possible )" << std::endl;
	for (int i = 0; i < 90; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
	std::cout << "Possible commands: " << std::endl;
	std::cout << "load" << "   |   " << "step-by-step operations" << std::endl;
	for (auto explanation : help_map)
	{
		std::cout << explanation.first << "   |   " << explanation.second << std::endl;
	}
	std::cout << std::endl;
}

void UserInterface::displayImage(Image image)
{
	std::cout << image;
}

void UserInterface::registerParameter(const std::string name, Parameter* action)
{
	parameters_map.emplace(name, action);
}
