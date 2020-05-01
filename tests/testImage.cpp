#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/image.h"
#include "../graphic-file-converter/image.cpp"
#include "../graphic-file-converter/file.h"
#include "../graphic-file-converter/file.cpp"
#include "../graphic-file-converter/header_file.h"
#include "../graphic-file-converter/header_file.cpp"
#include "../graphic-file-converter/bmp_file.h"
#include "../graphic-file-converter/bmp_file.cpp"
#include "../graphic-file-converter/image_content.h"
#include "../graphic-file-converter/image_content.cpp"
#include "../graphic-file-converter/Bpp1.h"
#include "../graphic-file-converter/Bpp1.cpp"
#include "../graphic-file-converter/Bpp24.h"
#include "../graphic-file-converter/Bpp24.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testImage)
	{
	public:



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
