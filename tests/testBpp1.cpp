#include "pch.h"

#include "CppUnitTest.h"
#include "../graphic-file-converter/image_content/bpp1.h"
#include "../graphic-file-converter/image_content/bpp1.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testBpp1)
	{
	public:

		TEST_METHOD(testBufferSize0)
		{
			auto b = Bpp1();
			b.resize(10, 10);
			auto result = b.calculateBufferSize();
			Assert::AreEqual(static_cast<size_t>(13), result);
		}
		TEST_METHOD(testBufferSize1)
		{
			auto b = Bpp1();
			b.resize(8, 8);
			auto result = b.calculateBufferSize();
			Assert::AreEqual(static_cast<size_t>(8), result);
		}

		TEST_METHOD(test_putPixel_then_getPixel)
		{
			auto b = Bpp1();
			uint8_t pix_in = 0xff;
			uint8_t pix_out = 0;
			b.resize(1, 1);
			b.putPixel(0, 0, &pix_in);
			b.getPixel(0, 0, &pix_out);
			Assert::AreEqual<uint8_t>(pix_out, 0x01);
		}

		TEST_METHOD(testToString0)
		{
			auto b = Bpp1();
			uint8_t input = 0;
			b.resize(2, 2);
			b.putPixel(0, 0, &input);
			input = 1;
			b.putPixel(1, 1, &input);
			b.putPixel(0, 1, &input);
			b.putPixel(1, 0, &input);
			auto s = b.toString();
			auto expected = std::string("**\n *\n");
			Assert::AreEqual(expected, s);
		}
		TEST_METHOD(testToString1)
		{
			auto b = Bpp1();
			uint8_t input = 0;
			b.resize(3, 2);
			b.putPixel(0, 0, &input);
			b.putPixel(2, 0, &input);
			input = 1;
			b.putPixel(1, 1, &input);
			b.putPixel(0, 1, &input);
			b.putPixel(1, 0, &input);
			b.putPixel(2, 1, &input);
			auto s = b.toString();
			auto expected = std::string("***\n * \n");
			Assert::AreEqual(expected, s);
		}
		TEST_METHOD(testEightRound0)
		{
			auto res = Bpp1::eightDivisor(8);
			Assert::AreEqual(static_cast<unsigned>(1), res);
		}
		TEST_METHOD(testEightRound1)
		{
			auto res = Bpp1::eightDivisor(7);
			Assert::AreEqual(static_cast<unsigned>(1), res);
		}
		TEST_METHOD(testEightRound2)
		{
			auto res = Bpp1::eightDivisor(1);
			Assert::AreEqual(static_cast<unsigned>(1), res);
		}
		TEST_METHOD(testmemRowSize0)
		{
			auto b = Bpp1();
			b.resize(10, 10);
			auto res = b.memRowSize();
			Assert::AreEqual(2, res);
		}
		TEST_METHOD(testmemRowSize1)
		{
			auto b = Bpp1();
			b.resize(8, 10);
			auto res = b.memRowSize();
			Assert::AreEqual(1, res);
		}
		TEST_METHOD(testBmpRowSize0)
		{
			auto b = Bpp1();
			b.resize(64, 10);
			auto res = b.bmpRowSize();
			Assert::AreEqual(static_cast<unsigned>(8), res);
		}
		TEST_METHOD(testBmpRowSize1)
		{
			auto b = Bpp1();
			b.resize(80, 10);
			auto res = b.bmpRowSize();
			Assert::AreEqual(static_cast<unsigned>(12), res);
		}
	};
}
