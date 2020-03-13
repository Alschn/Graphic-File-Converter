#include "pch.h"
#include "CppUnitTest.h"

#include "../graphic-file-converter/TestExample.h"
#include "../graphic-file-converter/TestExample.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(multiply)
		{
			int result = test_example::multiply(2, 3);
			Assert::AreEqual(6, result);
		}

		TEST_METHOD(divide)
		{
			Assert::ExpectException<std::invalid_argument>([] { test_example::divide(2, 0); });
		}
	};
}
