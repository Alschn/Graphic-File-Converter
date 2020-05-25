//Created by Wojciech Nowicki
#include <iostream>
#include "user_interface.h"
#include <map>
#include <string>
#include <regex>
#include <sstream>
#include <vector>
#include "../image.h"
#include "../conversions/converter.h"
#include <algorithm>
#include "../parameters/parameter.h"

/*
	Each map contains info about all types of conversions.
//*/
std::map<const std::string, Converter*> UserInterface::conversions_map;
std::map<const std::string, const std::string> UserInterface::help_map;
std::map<const std::string, std::regex> UserInterface::regex_map;
std::map<const std::string, Arguments*> UserInterface::arguments_map;
std::map<const std::string, Parameter*> UserInterface::parameters_map;
std::map<const std::string, int> UserInterface::arguments_required_map;


void UserInterface::registerAction(const std::string& command_name, const std::string& command_explanation,
                                   Converter* conversion, const std::regex& command_regex, Arguments* arguments, int arguments_required)
{
	/*
		Function registers new functionality.
	//*/
	conversions_map.emplace(command_name, conversion);
	help_map.emplace(command_name, command_explanation);
	regex_map.emplace(command_name, command_regex);
	arguments_map.emplace(command_name, arguments);
	arguments_required_map.emplace(command_name, arguments_required);
}


void UserInterface::display(const std::string& command)
{
	/*
	 Main function of UserInterface - responsible for
	 detecting command and choosing action to execute.
	//*/
	if (!check_regex_if_empty(std::regex(R"###(^load +(('|")[^']\S+[^']('|")) ?$)###"), command))
	{
		/*
		 Step-by-step method - still in progress.
		//*/
		std::stringstream command_ss(command);
		std::vector<std::string> splitted;
		std::string buf_string;
		while (command_ss >> buf_string)
		{
			splitted.push_back(buf_string);
		}
		splitted[1].erase(splitted[1].begin());
		splitted[1].erase(splitted[1].end() - 1, splitted[1].end());
		std::string input_path = splitted[1];
		Image* img_pointer;
		try
		{
			img_pointer = new Image(input_path);
		}
		catch (std::bad_function_call)
		{
			throw std::exception("Wrong path!");
		}
		Converter* conversion;
	ASK_LOOP:
		std::cout << "What do you want to do ?" << std::endl;
		for (const auto& explanation : help_map)
		{
			std::cout << explanation.first << "   |   " << explanation.second << std::endl;
		}
		std::string entered_command;
		std::getline(std::cin, entered_command);
		int command_flag = 0;
		for (auto command_name : arguments_required_map)
		{
			if (entered_command == command_name.first)
			{
				conversion = conversions_map[entered_command];
				conversion->loadImage(img_pointer);
				std::vector<double> args;
				while (command_name.second > args.size())
				{
					ARG_LOOP:
					std::cout << "Enter argument " << args.size() + 1 << " :   " << std::endl;
					std::string line;
					std::getline(std::cin, line);
					try
					{
						double arg = std::stod(line);
						args.push_back(arg);
					}
					catch (...)
					{
						std::cout << "Argument inappropriate!" << std::endl;
					}
				}
				arguments_map[entered_command]->set_arguments(args);
				try
				{
					conversion->processImage(arguments_map[entered_command]);
				}
				catch(...)
				{
					std::cout << "Argument inappropriate!" << std::endl;
					args.clear();
					goto ARG_LOOP;
				}
				std::string parameter;
				std::cout << "Enter parameter (if do not want any, type '-'): " << std::endl;
				std::getline(std::cin, parameter);
				if (parameter == "-")
				{
					;
				}
				else
				{
					for (auto par : parameters_map)
					{
						if (par.first == parameter)
						{
							parameters_map[parameter]->executeParam(conversion->newImage);
						}
					}

				}
				std::string save_answer;
			SAVING:
				std::cout << "Save file? [y/n]" << std::endl;
				std::getline(std::cin, save_answer);
				if (save_answer == "y")
				{
				SAVING_PATH:
					std::string output_path;
					std::cout << "Enter output path: " << std::endl;
					std::getline(std::cin, output_path);
					try
					{
						conversion->saveImage(output_path);
					}
					catch (...)
					{
						std::cout << "Your output path is invalid! Try again!" << std::endl;
						goto SAVING_PATH;
					}
				}
				else if (save_answer == "n")
				{

				}
				else
				{
					std::cout << "Wrong letter entered!" << std::endl;
					goto SAVING;
				}
				command_flag++;
			}
		}
		if (command_flag == 1)
		{
		EXIT_ANSWER:
			std::string exit_answer;
			std::cout << "Exit? [y/n]" << std::endl;
			std::getline(std::cin, exit_answer);
			if (exit_answer == "y")
			{
				exit(0);
			}
			else if (exit_answer == "n")
			{
				goto ASK_LOOP;
			}
			else
			{
				goto EXIT_ANSWER;
			}
		}
		else
		{
			std::cout << "Command not found try again!" << std::endl;
			goto ASK_LOOP;
		}

	}
	else if (!check_regex_if_empty(std::regex(R"(^help *$)"), command))
	{
		/*
			Help display.
		//*/
		std::cout << std::endl;
		showHelp();
		
	}
	else
	{
		/*
			Fully correct command inserted in cmd executes here.
		//*/
		std::string command_fullname;
		int no_function = 0;
		for (const auto& command_name : regex_map)
		{
			if (!check_regex_if_empty(command_name.second, command))
			{
				/*
					Pulling out arguments from command and storing them
					in vector.
				//*/
				command_fullname = command_name.first;
				std::stringstream command_ss(command);
				std::vector<std::string> splitted;
				std::string buf_string;
				while (command_ss >> buf_string)
				{
					splitted.push_back(buf_string);
				}
				std::vector<double> args;
				double argument;
				for (auto& command_element : splitted)
				{
					if (command_element[0] == '-')
					{
						command_element.erase(0, 1);
						try
						{
							argument = std::stod(command_element);
							argument = -argument;
							args.push_back(argument);
						}
						catch (...)
						{
							command_element.insert(0, "-");
						}
					}
					else
					{
						try
						{
							argument = std::stod(command_element);
							args.push_back(argument);
						}
						catch (...)
						{
							;
						}
					}
				}
				arguments_map[command_fullname]->set_arguments(args);
				/*
					Stripping input path from quotation marks (').
				//*/
				splitted[args.size() + 1].erase(splitted[args.size() + 1].begin());
				splitted[args.size() + 1].erase(splitted[args.size() + 1].end() - 1, splitted[args.size() + 1].end());
				std::string input_path = splitted[args.size() + 1];
				std::string output_path;
				if (splitted.size() > args.size() + 2)
				{
					if (splitted[args.size() + 2].size() > 2)
					{
						/*
						Stripping output path from quotation marks (') (if given).
						//*/
						splitted[args.size() + 2].erase(splitted[args.size() + 2].begin());
						splitted[args.size() + 2].erase(splitted[args.size() + 2].end() - 1,
							splitted[args.size() + 2].end());
						output_path = splitted[args.size() + 2];
					}
					else
					{
						;
					}
				}
				else
				{
					/*
						Creating output path if it was not given.
					//*/
					for (int i = input_path.size() - 1; i > 0; i--)
					{
						if (input_path[i] == '.')
						{
							output_path = input_path;
							output_path = output_path.insert(i, "_out");
							break;
						}
					}
				}
				for (auto param : parameters_map)
				{
					/*
						Checking if any parameter was given.
					//*/
					if (std::find(splitted.begin(), splitted.end(), param.first) != splitted.end())
					{
						try
						{
							param.second->executeParam(
								executeAction(command_name.first, input_path, output_path, arguments_map[command_fullname]));
						}
						catch(const std::exception & ex)
						{
							std::cerr << ex.what() << std::endl;
							exit(1);
						}
					}
					else
					{
						try
						{
							executeAction(command_name.first, input_path, output_path, arguments_map[command_fullname]);
						}
						catch (const std::exception& ex)
						{
							std::cerr << ex.what() << std::endl;
							exit(1);
						}
					}
				}
				std::cout << "Action executed!" << std::endl;
			}
			else
			{
				no_function++;
			}
		}
		if (no_function == conversions_map.size())
		{
			std::cout << std::endl;
			std::cout <<
				"There is no such command or you made spelling mistake! Try again or type \"help\"" << std
				::endl;
		}
	}
}

Image* UserInterface::executeAction(const std::string& command, const std::string& path, const std::string& out_path,
                                    Arguments* args)
{
	Image* img_pointer = new Image(path);
	Converter* conversion = conversions_map[command];
	conversion->loadImage(img_pointer);
	conversion->processImage(args);
	try
	{
		conversion->saveImage(out_path);
	}
	catch(...)
	{
		throw std::runtime_error("Wrong path!");
	}
	return conversion->newImage;
}

void UserInterface::registerHelp(const std::string& command_name, const std::string& explanation)
{
	help_map.emplace(command_name, explanation);
}

void UserInterface::showHelp()
{
	/*
		Displays help.
	//*/
	std::cout << "Command structure:" << std::endl;
	std::cout << "graphic-file-converter.exe [command_name] [argument] ['in_path'] {'out_path'} {-parameter}" << std::
		endl;
	std::cout << "( {} - possible )" << std::endl;
	for (int i = 0; i < 90; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
	std::cout << "Possible commands: " << std::endl;
	std::cout << "load" << "   |   " << "step-by-step operations" << std::endl;
	for (const auto& explanation : help_map)
	{
		std::cout << explanation.first << "   |   " << explanation.second << std::endl;
	}
	std::cout << std::endl;
}


void UserInterface::registerParameter(const std::string name, Parameter* action)
{
	parameters_map.emplace(name, action);
}

std::string argv_to_string(char* arg[], int number_of_arg)
{
	/*
		Function forms one string from argvs to be checked by regex.
	//*/
	std::string command;
	std::vector<std::string> argList(arg + 1, arg + number_of_arg);
	for (size_t i = 0; i < argList.size(); i++) 
	{
		if (i == 0)
		{
			command += argList[i];
		}
		else
		{
			command += " " + argList[i];
		}
	}
	return command;
}

bool check_regex_if_empty(std::regex reg, const std::string& command)
{
	std::smatch matches;
	std::regex_search(command, matches, reg);
	return matches.empty();
}
