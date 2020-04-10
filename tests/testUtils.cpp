#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/utils.h"
// #include "../graphic-file-converter/utils.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testUtils)
	{
	public:

		TEST_METHOD(testWriteIntToCharBuffer)
		{
			char buf[10];
			Utils::writeIntToCharBufffer(buf, 65535, 2);
			Assert::AreEqual((char)255, buf[2]);
			Assert::AreEqual((char)255, buf[3]);
		}
		TEST_METHOD(isBitSet0)
		{
			char input = 0x00;
			auto result = Utils::isBitSet(input, 0);
			Assert::IsFalse(result);
		}
		TEST_METHOD(isBitSet1)
		{
			char input = 0x01;
			auto result = Utils::isBitSet(input, 0);
			Assert::IsTrue(result);
		}
		TEST_METHOD(isBitSet2)
		{
			char input = 0x80;
			auto result = Utils::isBitSet(input, 7);
			Assert::IsTrue(result);
			result = Utils::isBitSet(input, 5);
			Assert::IsFalse(result);
		}
	};
}
