#include <iostream>
#include "converter.h"
#include "user_interface.h"
#include <map>
#include <string>

using namespace std;


void UserInterface::registerAction(const string command_name, action_pointer action, const vector<int> params)
{
    this->actions_map.emplace(command_name, action));
    this->actions_parameters.emplace(command_name, params)
}


void UserInterface::display()
{
    cout << "Welcome to file converter!" << endl;
    cout << "Type command or --help to get commands examples" << endl;
    string command;
    for (::)
    {
        cin << command;

        if (actions_map.find(command) == actions_map.end() )
        {
            cout << "There is no such function!" << endl;
            showHelp();
        }
        else if (command == "--help")
        {
            showHelp();
        }
        else
        {
            executeAction(command);
        }
    }
}

void UserInterface::executeAction(const string &command)
{
    action_pointer action = actions_map[command];
    (this->*action)(); //dilemma about passing arguments
}

void UserInterface::showHelp()
{
    cout << "Possible commands: " << endl;
    for (auto command : this->actions_map)
    {
        cout << command.first << endl;
    }
}

