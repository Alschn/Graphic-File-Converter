#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/utils.h"
#include "../graphic-file-converter/utils.cpp"
#include <regex>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testUtils)
	{
	public:
		TEST_METHOD(testFourCharsToInt0)
		{
			const std::vector<unsigned char> input = {0, 0, 0, 0};
			auto result = Utils::fourCharsToInt(input, 0);
			Assert::AreEqual(static_cast<unsigned>(0), result);
		}

		TEST_METHOD(testFourCharsToInt1)
		{
			const std::vector<unsigned char> input = {3, 0, 0, 0};
			auto result = Utils::fourCharsToInt(input, 0);
			Assert::AreEqual(static_cast<unsigned>(3), result);
		}

		TEST_METHOD(testFourCharsToInt2)
		{
			const std::vector<unsigned char> input = {0, 0xFF, 0, 0};
			auto result = Utils::fourCharsToInt(input, 0);
			Assert::AreEqual(static_cast<unsigned>(65280), result);
		}
		TEST_METHOD(testFourCharsToInt3)
		{
			const std::vector<unsigned char> input = { 0xFF, 0xFF, 0xFF, 0xFF,0x00,0x00 };
			auto result = Utils::fourCharsToInt(input, 2);
			Assert::AreEqual(static_cast<unsigned>(UINT16_MAX), result);
		}

		TEST_METHOD(testWriteIntToCharBuffer0)
		{
			char buf[10];
			Utils::writeIntToCharBuffer(buf, 65535, 2);
			Assert::AreEqual(static_cast<char>(255), buf[2]);
			Assert::AreEqual(static_cast<char>(255), buf[3]);
		}
		TEST_METHOD(testWriteIntToCharBuffer1)
		{
			std::vector<uint8_t> buf;
			buf.resize(4);
			Utils::writeIntToCharBuffer(buf, 255, 0);
			Assert::AreEqual(static_cast<uint8_t>(255), buf[0]);
			Assert::AreEqual(static_cast<uint8_t>(0), buf[1]);
		}
		TEST_METHOD(testWriteIntToCharBuffer2)
		{
			uint8_t buf[4];
			Utils::writeIntToCharBuffer(buf, 2882399982, 0);
			Assert::AreEqual(static_cast<uint8_t>(0xEE), buf[0]);
			Assert::AreEqual(static_cast<uint8_t>(0xEE), buf[1]);
			Assert::AreEqual(static_cast<uint8_t>(0xCD), buf[2]);
			Assert::AreEqual(static_cast<uint8_t>(0xAB), buf[3]);
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
			const char input = 0x80;
			auto result = Utils::isBitSet(input, 7);
			Assert::IsTrue(result);
			result = Utils::isBitSet(input, 5);
			Assert::IsFalse(result);
		}

		TEST_METHOD(closestFourMultiple0)
		{
			const auto result = Utils::closestFourMultiple(31);
			Assert::AreEqual(static_cast<unsigned>(32), result);
		}

		TEST_METHOD(closestFourMultiple1)
		{
			const auto result = Utils::closestFourMultiple(0);
			Assert::AreEqual(static_cast<unsigned>(0), result);
		}

		TEST_METHOD(closestFourMultiple2)
		{
			const auto result = Utils::closestFourMultiple(4);
			Assert::AreEqual(static_cast<unsigned>(4), result);
		}

		TEST_METHOD(closestFourMultiple4)
		{
			const auto result = Utils::closestFourMultiple(10);
			Assert::AreEqual(static_cast<unsigned>(12), result);
		}

		TEST_METHOD(findMatch0)
		{
			std::string output;
			const auto result = Utils::findMatch("abc", std::regex(R"((abc))"), output);
			Assert::AreEqual(std::string("abc"), output);
			Assert::IsTrue(result);
		}

		TEST_METHOD(findMatch1)
		{
			std::string output;
			const auto result = Utils::findMatch("xddd", std::regex(R"(abc)"), output);
			Assert::AreEqual(std::string(""), output);
			Assert::IsFalse(result);
		}

		TEST_METHOD(findMatch2)
		{
			std::string output;
			const auto result = Utils::findMatch("dddcde", std::regex(R"((ddd)(cde))"), output);
			Assert::AreEqual(std::string("ddd"), output);
			Assert::IsTrue((result));
		}

		TEST_METHOD(splitString0)
		{
			const auto result = Utils::splitString(std::string(""), ',');
			Assert::AreEqual(static_cast<size_t>(0), result.size());
		}

		TEST_METHOD(splitString1)
		{
			const auto result = Utils::splitString(std::string("a,b,c"), ',');
			Assert::AreEqual(static_cast<size_t>(3), result.size());
		}

		TEST_METHOD(splitString2)
		{
			const auto result = Utils::splitString(std::string("a,b,c"), 'x');
			Assert::AreEqual(static_cast<size_t>(1), result.size());
		}
	};
}
