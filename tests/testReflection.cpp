#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/reflection.h"
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testReflection)
	{
	public:

		TEST_METHOD(testCreateMap_sq0) // Square Vertical
		{
			auto result = Reflection::create_map(2, 2, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map0 = {
				{{0, 0} , {0, 1}}, {{1, 0} , {1, 1}}, {{0, 1} , {0, 0}}, {{1, 1} , {1, 0} }
		};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map0), result);
		}
		
		TEST_METHOD(testCreatemap_sq1) // Square Horizontal
		{
			auto result = Reflection::create_map(2, 2, 1);
			const std::map <std::pair<int, int>, std::pair<int, int>> map1 = { 
				{{0, 0} , {1, 0}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {0, 1} }
			};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map1), result);
		}
		
		TEST_METHOD(testCreatemap_sq2) // Square Diagonal 1
		{
			auto result = Reflection::create_map(2, 2, 2);
			const std::map <std::pair<int, int>, std::pair<int, int>> map2 = {
				{{0, 0} , {0, 0}}, {{1, 0} , {0, 1}}, {{0, 1} , {1, 0}}, {{1, 1} , {1, 1} }
			};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map2), result);
		}
		
		TEST_METHOD(testCreatemap_sq3) // Square Diagonal 2
		{
			auto result = Reflection::create_map(2, 2, 3);
			const std::map <std::pair<int, int>, std::pair<int, int>> map3 = {
				{{0, 0}, {1, 1}}, {{1, 0}, {1, 0}}, {{0, 1}, {0, 1}}, {{1, 1}, {0, 0} }
			};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map3), result);
		}
		
		TEST_METHOD(testCreatemap_rect0) // Rectangle Vertical
		{
			auto result = Reflection::create_map(2, 3, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map4 = {
				{{0, 0} , {0, 2}}, {{1, 0} , {1, 2}}, {{0, 1} , {0, 1}}, {{1, 1} , {1, 1}}, {{0, 2} , {0, 0}}, {{1, 2} , {1, 0} }
			};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map4), result);
		}
		
		TEST_METHOD(testCreatemap_rect1) /// Rectangle Horizontal
		{
			auto result = Reflection::create_map(3, 2, 1);
			const std::map <std::pair<int, int>, std::pair<int, int>> map5 = {
				{{0, 0} , {1, 0}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {0, 1}}, {{0, 2} , {1, 2}}, {{1, 2} , {0, 2} }
			};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map5), result);
		}
		TEST_METHOD(testCreatemap_rect2) // Rectangle Diagonal 1
		{
			auto result = Reflection::create_map(3, 2, 2);
			std::map <std::pair<int, int>, std::pair<int, int>> map6 = {
				{{0, 0} , {0, 0}}, {{1, 0} , {0, 1}}, {{0, 1} , {1, 0}}, {{1, 1} , {1, 1}}, {{0, 2} , {2, 0}}, {{1, 2} , {2, 1} }
			};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map6), result);
		}
		TEST_METHOD(testCreatemap_rect3) // Rectangle Diagonal 2
		{
			auto result = Reflection::create_map(3, 2, 3);
			std::map <std::pair<int, int>, std::pair<int, int>> map7 = {
				{{0, 0}, {1, 2}}, {{1, 0}, {1, 1}}, {{0, 1}, {0, 2}}, {{1, 1}, {0, 1}}, {{0, 2}, {-1, 2}}, {{1, 2}, {-1, 1} }
			};
			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map7), result);
		}

	};
}