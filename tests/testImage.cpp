#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/utils.cpp"
#include "../graphic-file-converter/image.h"
#include "../graphic-file-converter/image.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testImage)
	{
	public:

		TEST_METHOD(testRowsize)
		{
			const auto result = Image::rowSize(10, 3);
			Assert::AreEqual(static_cast<unsigned int>(32), result);
		}

		TEST_METHOD(testPadding)
		{
			const auto result = Image::rowPadding(10, 3);
			Assert::AreEqual(static_cast<unsigned int>(2), result);
		}

		TEST_METHOD(testInternalRowSize)
		{
			Image im = Image(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);

			im.resize(10, 12);
			Assert::AreEqual(static_cast<unsigned int>(32), im.row_size);

			im.resize(100, 100);
			Assert::AreEqual(static_cast<unsigned int>(300), im.row_size);
		}
		TEST_METHOD(testCalculatePixelIndex)
		{
			Image im = Image(R"(..\sample_bmps\10x10.bmp)", true, ImageMode::ReadFromBMP);
			auto result = im.calculatePixelIndex(9, 1, 0);
			Assert::AreEqual(57, result);
			
		}
		
	};
}
