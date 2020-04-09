#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/rotation.h"
#include "../graphic-file-converter/image.h"

#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testRotation)
	{
	public:
		static bool compareMaps(std::map <std::pair<int, int>, std::pair<int, int>> map_1, std::map <std::pair<int, int>, std::pair<int, int>> map_2)
		{
			if (map_1 == map_2)
			{
				return true;
			}
			else
			{
				return false;
			}
		};
		TEST_METHOD(testCreatemap_rot90sq) // rotate square by 90 deg
		{
			auto result = Rotation::create_map(2, 2, 90);
			const std::map <std::pair<int, int>, std::pair<int, int>> map0 = {
				{{0, 0} , {0, 1}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {1, 0}}
			};
			Assert::IsTrue(compareMaps(map0, result));
		}

		TEST_METHOD(testCreatemap_rot180sq) // rotate square by 180 deg
		{
			auto result = Rotation::create_map(2, 2, 180);
			const std::map <std::pair<int, int>, std::pair<int, int>> map1 = {
				{{0, 0} , {1, 1}}, {{1, 0} , {0, 1}}, {{0, 1} , {1, 0}}, {{1, 1} , {0, 0}}
			};
			Assert::IsTrue(compareMaps(map1, result));
		}

		TEST_METHOD(testCreatemap_rot270sq) // rotate square by 270 deg
		{
			auto result = Rotation::create_map(2, 2, 270);
			const std::map <std::pair<int, int>, std::pair<int, int>> map2 = {
				{{0, 0} , {1, 1}}, {{1, 0} , {0, 1}}, {{0, 1} , {1, 0}}, {{1, 1} , {0, 0}}
			};
			Assert::IsTrue(compareMaps(map2, result));
		}

		TEST_METHOD(testCreatemap_rot360sq) // rotate square by 360 deg
		{
			auto result = Rotation::create_map(2, 2, 360);
			const std::map <std::pair<int, int>, std::pair<int, int>> map3 = {
				{{0, 0}, {0, 0}}, {{1, 0}, {1, 0}}, {{0, 1}, {0, 1}}, {{1, 1}, {1, 1}}
			};
			Assert::IsTrue(compareMaps(map3, result));
		}
		//TEST_METHOD(testCreatemap_randang) // rotate square by angle which is not multiple of 90
		//{
		//	// tutaj oczekiwanie wyjatku
		//}
		TEST_METHOD(testCreatemap_largeang) // rotate square by angle greater than 360
		{
			auto result = Rotation::create_map(2, 2, 450);
			const std::map <std::pair<int, int>, std::pair<int, int>> map4 = {
				{{0, 0} , {0, 1}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {1, 0}}
			};
			Assert::IsTrue(compareMaps(map4, result));
		}
		TEST_METHOD(testCreatemap_rot90rect) // rotate rectangle by 90 deg
		{
			auto result = Rotation::create_map(3, 2, 90);
			const std::map <std::pair<int, int>, std::pair<int, int>> map5 = {
				{{0, 0} , {0, 1}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {1, 0}}, {{0, 2} , {2, 1}}, {{1, 2} , {2, 0}}
			};
			Assert::IsTrue(compareMaps(map5, result));
		}

		TEST_METHOD(testCreatemap_rot180rect) // rotate rectangle by 180 deg
		{
			auto result = Rotation::create_map(3, 2, 180);
			const std::map <std::pair<int, int>, std::pair<int, int>> map6 = {
				{{0, 0} , {1, 2}}, {{1, 0} , {0, 1}}, {{0, 1} , {1, 1}}, {{1, 1} , {0, 0}}, {{0, 2} , {1, 0}}, {{1, 2} , {0, 0}}
			};
			Assert::IsTrue(compareMaps(map6, result));
		}

		TEST_METHOD(testCreatemap_rot270rect) // rotate rectangle by 270 deg
		{
			auto result = Rotation::create_map(3, 2, 270);
			const std::map <std::pair<int, int>, std::pair<int, int>> map7 = {
				{{0, 0} , {2, 0}}, {{1, 0} , {1, 1}}, {{0, 1} , {1, 0}}, {{1, 1} , {0, 0}}, {{0, 2} , {0, 0}}, {{1, 2} , {0, 0}}
			};
			Assert::IsTrue(compareMaps(map7, result));
		}

		TEST_METHOD(testCreatemap_rot360rect) // rotate rectangle by 360 deg
		{
			auto result = Rotation::create_map(3, 2, 360);
			const std::map <std::pair<int, int>, std::pair<int, int>> map8 = {
				{{0, 0}, {0, 0}}, {{1, 0}, {1, 0}}, {{0, 1}, {0, 1}}, {{1, 1}, {1, 1}}, {{0, 2}, {0, 2}}, {{1, 2}, {1, 2}}
			};
			Assert::IsTrue(compareMaps(map8, result));
		}
	};
}