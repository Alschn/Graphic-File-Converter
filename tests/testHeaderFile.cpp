#include "pch.h"

#include "../graphic-file-converter/image_file_types/header_file.h"
#include "../graphic-file-converter/image_file_types/header_file.cpp"
#include "CppUnitTest.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testHeaderFile)
	{
	public:

		TEST_METHOD(testgetLetterIndexFromFName0)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h_0"));
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName1)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h_A"));
			Assert::AreEqual(10, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName2)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h_2"));
			Assert::AreEqual(2, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName3)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h_a"));
			Assert::AreEqual(35, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName4)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h"));
			Assert::AreEqual(0, result);
		}
	};
}
