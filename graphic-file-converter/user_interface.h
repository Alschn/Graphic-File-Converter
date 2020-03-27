#pragma once
#include "converter.h"
#include <map>
using namespace std;

class UserInterface
{

public:

	typedef void (Converter:: *action_pointer)();
	static map <const string, action_pointer > actions_map;
	static map <const string, vector<int> > actions_parameters;

	void registerAction(const string command_name, action_pointer action);
	void display();
	void executeAction(const string& command);
	void showHelp();
}

	