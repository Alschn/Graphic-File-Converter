#include "pch.h"

#include "../graphic-file-converter/conversions/rotation.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/user_interface/user_interface.h"
#include "../graphic-file-converter/user_interface/user_interface.cpp"
#include <regex>
#include <string>
#include <map>
#include "../graphic-file-converter/arguments/rotation_arguments.cpp"
#include "../graphic-file-converter/image.h"
#include "../graphic-file-converter/conversions/rotation.cpp"
#include "../graphic-file-converter/arguments/arguments.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testUserInterface)
	{
	public:
		/*TEST_METHOD(testregisterAction)
		{
			UserInterface Desktop;
			Rotation conversion;
			RotationArguments rot_args;
			Desktop.registerAction("rotate", "rotates picture by n degrees", &conversion,
			                       std::regex(
					R"###(^rotate +\d+ +('[^']\S+[^']') *('[^']\S+[^']')? *(-\w)? *$)###"),
				&rot_args);
			const auto result1 = Desktop.help_map["rotate"];
			Assert::AreEqual(static_cast<std::basic_string<char>>("rotates picture by n degrees"), result1);
		}*/
		TEST_METHOD(testregisterHelp)
		{
			UserInterface Desktop;
			Desktop.registerHelp("rotate", "rotates picture by n degrees");
			Assert::AreEqual(static_cast<std::basic_string<char>>("rotates picture by n degrees"), Desktop.help_map["rotate"]);
		}
	};
}
