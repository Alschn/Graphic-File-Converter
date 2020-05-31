#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/image.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testImage)
	{
	public:
		TEST_METHOD(testGetExtension0)
		{
			auto result = Image::getExtension("./abc.h");
			Assert::AreEqual(static_cast<std::string>(".h"), result);

		}
		TEST_METHOD(testGetExtension1)
		{
			auto result = Image::getExtension("./abc.bmp");
			Assert::AreEqual(static_cast<std::string>(".bmp"), result);
		}
		
	};
}
