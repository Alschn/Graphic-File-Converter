#include "pch.h"
#include "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\VS\UnitTest\include\CppUnitTest.h"
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::map <std::pair<int, int>, std::pair<int, int>> create_map(int height, int width, int num)
{
	std::map <std::pair<int, int>, std::pair<int, int>> conv_map;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int x_n = j;
			int y_n = i;
			switch (num)
			{
			case 0:
				x_n = width - j - 1;
				break;
			case 1:
				y_n = height - i - 1;
				break;
			case 2:
				x_n = i;
				y_n = j;
				break;
			case 3:
				x_n = width - i - 1;
				y_n = height - j - 1;
				break;
			default:
				break;
			}
			conv_map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(x_n, y_n)));
		}
	}
	return conv_map;
};

namespace Tests
{
	TEST_CLASS(testReflection)
	{
	public:

		TEST_METHOD(testCreateMap_sq0) // Square Vertical
		{
			const auto result = create_map(2, 2, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map0 = {
				{{0, 0} , {0, 1}}, {{0, 1} , {0, 0}}, {{1, 0} , {1, 1}}, {{1, 1} , {1, 0}},
			};
			Assert::AreEqual(map0, result);
		}
		
		TEST_METHOD(testCreatemap_sq1) // Square Horizontal
		{
			const auto result = create_map(3, 3, 1);
			const std::map <std::pair<int, int>, std::pair<int, int>> map1 = { 
				{{0,0} , {2,0}}, {{0,1} , {2,1}}, {{0,2} , {2,2}}, {{1,0} , {1,0}},  {{1,1} , {1,1}}, {{1,2} , {1,2}}, {{2,0} , {0,0}}, {{2,1} , {0,1}}, {{2,2} , {0,2}}
			};
			Assert::AreEqual(map1, result);
		}
		
		TEST_METHOD(testCreatemap_sq2) // Square Diagonal 1
		{
			const auto result = create_map(3, 3, 2);
			const std::map <std::pair<int, int>, std::pair<int, int>> map2 = {
				{{0, 0}, {0, 0}}, {{0, 1}, {1, 0}}, {{0, 2} , {2, 0}}, {{1, 0} , {0, 1}}, {{1, 1}, {1, 1}}, {{1, 2} , {2, 1}}, {{2, 0} , {0, 2}}, {{2, 1} , {1, 2}}, {{2, 2} , {2, 2}},
			};
			Assert::AreEqual(map2, result);
		}
		
		TEST_METHOD(testCreatemap_sq3) // Square Diagonal 2
		{
			const auto result = create_map(2, 2, 3);
			const std::map <std::pair<int, int>, std::pair<int, int>> map3 = {
				{{0, 0} , {1, 1}}, {{0, 1} , {0, 1}}, {{1, 0} , {1, 0}}, {{1, 1} , {0, 0}}
			};
			Assert::AreEqual(map3, result);
		}
		
		TEST_METHOD(testCreatemap_rect0) // Rectangle Vertical
		{
			const auto result = create_map(2, 3, 1);
			const std::map <std::pair<int, int>, std::pair<int, int>> map4 = {
				{{0, 0}, {0, 1}}, {{0, 1}, {0, 0}}, {{1, 0}, {1, 1}}, {{1, 1}, {1, 0}}, {{2, 0}, {2, 1}}, {{2, 1}, {2, 0}}
			};
			Assert::AreEqual(map4, result);
		}
		
		TEST_METHOD(testCreatemap_rect1) /// Rectangle Horizontal
		{
			const auto result = create_map(3, 2, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map5 = {
				{{0, 0} , {1, 0}},
				{{0, 1}, {1, 1}},
				{{0, 2}, {1, 2}},
				{{1, 0}, {0, 0}},
				{{1, 1}, {0, 1}},
				{{1, 2} , {0, 2}}
			};
			Assert::AreEqual(map5, result);
		}
		TEST_METHOD(testCreatemap_rect2) // Rectangle Diagonal 1
		{
			const auto result = create_map(3, 2, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map6 = {
				{{0, 0}, {0, 0}},
				{{0, 1}, {1, 0}},
				{{0, 2} , {2, 0}},
				{{1, 0} , {0, 1}},
				{{1, 1}, {1, 1}},
				{{1, 2}, {2, 1}}
			};
			Assert::AreEqual(map6, result);
		}
		TEST_METHOD(testCreatemap_rect3) // Rectangle Diagonal 2
		{
			const auto result = create_map(3, 2, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map7 = {
				{{0, 0} , {1, 2}},
				{{0, 1}, {0, 2}},
				{{0, 2}, {-1, 2}},
				{{1, 0}, {1, 1}},
				{{1, 1}, {0, 1}},
				{{1, 2}, {-1, 1}}
			};
			Assert::AreEqual(map7, result);
		}

	};
}