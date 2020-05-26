#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/image.h"
#include "../graphic-file-converter/image.cpp"
#include "../graphic-file-converter/image_file_types/file.h"
#include "../graphic-file-converter/image_file_types/file.cpp"
#include "../graphic-file-converter/image_file_types/bmp_file.h"
#include "../graphic-file-converter/image_file_types/bmp_file.cpp"
#include "../graphic-file-converter/image_content/image_content.h"
#include "../graphic-file-converter/image_content/image_content.cpp"
#include "../graphic-file-converter/image_content/Bpp24.h"
#include "../graphic-file-converter/image_content/Bpp24.cpp"
#include<conio.h>
#include<cstdio>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testFile)
	{
	public:

		TEST_METHOD(testFileExists0)
		{
			auto result = File::fileExists("ZZZ:/xxxxddd");
			Assert::IsFalse(result);
		}
		TEST_METHOD(testFileExists1)
		{
			auto result = File::fileExists("EEEEE:\\xxxxddd");
			Assert::IsFalse(result);
		}
		TEST_METHOD(testFileExists2)
		{
			std::ofstream outfile("test.txt");
			outfile << "xd";
			outfile.close();
			auto result = File::fileExists("test.txt");
			Assert::IsTrue(result);
			remove("test.txt");
		}
	};
}
