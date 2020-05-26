#include "pch.h"

#include <CppUnitTest.h>


#include "../graphic-file-converter/conversions/converter.h"
#include "../graphic-file-converter/conversions/converter.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testcheckColorRange)
	{
	public:
		TEST_METHOD(testInRange)
		{
			const auto result = Converter::checkColorRange(120);
			Assert::AreEqual(120, static_cast<int>(result));
		}

		TEST_METHOD(testOutOfRangeUP)
		{
			const auto result = Converter::checkColorRange(256);
			Assert::AreEqual(255, static_cast<int>(result));
		}

		TEST_METHOD(testOutOfRangeDOWN)
		{
			const auto result = Converter::checkColorRange(-20);
			Assert::AreEqual(0, static_cast<int>(result));
		}
	};
}