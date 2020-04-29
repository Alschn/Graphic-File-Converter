#include "pch.h"
#include "CppUnitTest.h"
// #include "../graphic-file-converter/utils.cpp"
#include "../graphic-file-converter/image.h"
#include "../graphic-file-converter/image.cpp"
#include "../graphic-file-converter/file.h"
#include "../graphic-file-converter/file.cpp"
#include "../graphic-file-converter/header_file.h"
#include "../graphic-file-converter/header_file.cpp"
#include "../graphic-file-converter/image_content.h"
#include "../graphic-file-converter/image_content.cpp"
#include "../graphic-file-converter/Bpp1.h"
#include "../graphic-file-converter/Bpp1.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testImage)
	{
	public:

		TEST_METHOD(testRowsize0)
		{
			const auto result = Image::rowSize(10, ColorDepth::bpp24);
			Assert::AreEqual(static_cast<unsigned int>(32), result);
		}
		TEST_METHOD(testRowsize1)
		{
			const auto result = Image::rowSize(10, ColorDepth::bpp1);
			Assert::AreEqual(static_cast<unsigned int>(4), result);
		}
		TEST_METHOD(testRowsize2)
		{
			const auto result = Image::rowSize(24, ColorDepth::bpp1);
			Assert::AreEqual(static_cast<unsigned int>(4), result);
		}
		TEST_METHOD(testRowsize3)
		{
			const auto result = Image::rowSize(33, ColorDepth::bpp1);
			Assert::AreEqual(static_cast<unsigned int>(8), result);
		}
		TEST_METHOD(testRowsize4)
		{
			const auto result = Image::rowSize(32, ColorDepth::bpp1);
			Assert::AreEqual(static_cast<unsigned int>(4), result);
		}
		TEST_METHOD(testPadding)
		{
			const auto result = Image::rowPadding(10, ColorDepth::bpp24);
			Assert::AreEqual(static_cast<unsigned int>(2), result);
		}

		TEST_METHOD(testInternalRowSize)
		{
			// Image im = Image(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::read_from_bmp);
			//
			// im.resize(10, 12);
			// Assert::AreEqual(static_cast<unsigned int>(32), im.row_size);
			//
			// im.resize(100, 100);
			// Assert::AreEqual(static_cast<unsigned int>(300), im.row_size);
		}
		TEST_METHOD(testCalculatePixelIndex)
		{
			Image im = Image(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::read_from_bmp);
			auto result = im.calculatePixelIndex(9, 1, 0);
			Assert::AreEqual(57, result);
			
		}
		TEST_METHOD(testGetExtension0)
		{
			auto result = Image::getExtension("abc.h_a");
			Assert::AreEqual(static_cast<std::string>(".h"), result);

		}
		TEST_METHOD(testGetExtension1)
		{
			auto result = Image::getExtension("abc.bmp");
			Assert::AreEqual(static_cast<std::string>(".bmp"), result);

		}
		
	};
}
