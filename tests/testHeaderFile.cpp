#include "pch.h"


#include "../graphic-file-converter/font.h"
#include "../graphic-file-converter/font.cpp"
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
			Assert::AreEqual<unsigned char>(0, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName1)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h_A"));
			Assert::AreEqual<unsigned char>(10, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName2)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h_2"));
			Assert::AreEqual<unsigned char>(2, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName3)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h_a"));
			Assert::AreEqual<unsigned char>(35, result);
		}
		TEST_METHOD(testgetLetterIndexFromFName4)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h"));
			Assert::AreEqual<unsigned char>(0, result);
		}
	};
}
