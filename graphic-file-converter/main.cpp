#include <iostream>
#include <fstream>
#include "rotation.h"
#include "reflection.h"
#include "arialDig32x24.h"
#include "display_parameter.h"
#include "user_interface.h"

using namespace std;

int main(int argc, char *argv[])
{
	UserInterface Desktop;
	Rotation conversion;
	DisplayParameter display;
	Reflection conversion2;
	Desktop.registerParameter("-d", &display);
	Desktop.registerAction("rotation", "rotates picture by n degrees", &conversion,
		regex(
			R"###(^converter +rotation +\d+ +(('|")[^'][^"]\S+[^'][^"]('|")) *(('|")[^'][^"]\S+[^'][^"]('|"))? *(-\w)? *$)###"),
		1);
	Desktop.registerAction("reflection", "reflects picture over selected axis", &conversion2,
		regex(
			R"###(^converter +reflection +\d +(('|")[^'][^"]\S+[^'][^"]('|")) *(('|")[^'][^"]\S+[^'][^"]('|"))? *(-\w)? *$)###"),
		1);
	if (argc > 1)
	{	
		Desktop.display(argv_to_string(argv, argc));
	}
	else
	{
		std::cout << "No command typed! Try again!" << std::endl;
		Desktop.showHelp();
	}
}
