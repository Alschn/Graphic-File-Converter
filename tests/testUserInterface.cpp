#include "pch.h"

#include "../graphic-file-converter/rotation.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/user_interface.h"
#include "../graphic-file-converter/user_interface.cpp"
#include <regex>
#include <string>
#include "../graphic-file-converter/image.h"
#include "../graphic-file-converter/converter.h"
#include "../graphic-file-converter/converter.cpp"
#include "../graphic-file-converter/rotation.cpp"
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testUserInterface)
	{
	public:
		TEST_METHOD(testregisterAction)
		{
			UserInterface Desktop;
			Rotation conversion;
			Desktop.registerAction("rotation", "rotates picture by n degrees", &conversion, std::regex(R"###(^converter +rotation +\d\d +(('|")[^']\S+[^']('|")) *('\+[^']')? *$)###"), 1);
			const auto result1 = Desktop.help_map["rotation"];
			const auto result2 = Desktop.number_of_command_arguments_map["rotation"];
			Assert::AreEqual(static_cast<std::basic_string<char>>("rotates picture by n degrees"), result1);
			Assert::AreEqual(1, result2);
		}
	};
}
