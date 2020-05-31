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


		TEST_METHOD(testgetLetterIndexFromFName4)
		{
			auto result = HeaderFile::getLetterIndexFromFName(std::string("abc.h"));
			Assert::AreEqual<unsigned char>(0, result);
		}
	};
}
