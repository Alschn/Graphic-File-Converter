#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/utils.h"
// #include "../graphic-file-converter/utils.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testImage)
	{
	public:

		TEST_METHOD(testUtils)
		{
			char buf[10];
			Utils::writeIntToCharBufffer(buf, 65535, 2);
			Assert::AreEqual((char)255, buf[2]);
			Assert::AreEqual((char)255, buf[3]);
		}
	};
}
