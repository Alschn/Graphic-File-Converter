#include <map>
#include "pch.h"
#include "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\VS\UnitTest\include\CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::map <std::pair<int, int>, std::pair<int, int>> create_map(int height, int width, int angle)
{
	std::map <std::pair<int, int>, std::pair<int, int>> map;
	if (angle % 90 != 0)
	{
		throw std::exception("Angle has to be a multiple of 90 degrees");
	}
	if (angle > 360)
	{
		int multiple = angle / 360;
		angle = angle - multiple * 360;
	}
	if (angle != 360 || angle != 0)
	{
		const auto pi = std::acos(-1);
		double deg = angle * pi / 180;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				double x_n = j * std::cos(-deg) - i * std::sin(-deg);
				double y_n = j * std::sin(-deg) + i * std::cos(-deg);
				switch (angle)
				{
				case 90:
					y_n += (width - 1);
					break;
				case 180:
					x_n += (width - 1);
					y_n += (height - 1);
					break;
				case 270:
					x_n += (height - 1);
					break;
				default:
					break;
				}
				map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(int(round(x_n)), int(round(y_n)))));
			}
		}
	}
	return map;
};

namespace Tests
{
	TEST_CLASS(testReflection)
	{
	public:

		TEST_METHOD(testCreatemap_rot90sq) // rotate square by 90 deg
		{
			const auto result = create_map(3, 3, 90);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}

		TEST_METHOD(testCreatemap_rot180sq) // rotate square by 180 deg
		{
			const auto result = create_map(3, 3, 180);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}

		TEST_METHOD(testCreatemap_270sq) // rotate square by 270 deg
		{
			const auto result = create_map(3, 3, 270);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}

		TEST_METHOD(testCreatemap_360sq) // rotate square by 360 deg
		{
			const auto result = create_map(3, 3, 360);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}
		TEST_METHOD(testCreatemap_randang) // rotate square by angle which is not multiple of 90
		{
			const auto result = create_map(3, 3, 155);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}
		TEST_METHOD(testCreatemap_largeang) // rotate square by angle greater than 360
		{
			const auto result = create_map(3, 3, 1350);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}
		TEST_METHOD(testCreatemap_rot90rect) // rotate rectangle by 90 deg
		{
			const auto result = create_map(2, 2, 90);
			const std::map <std::pair<int, int>, std::pair<int, int>> my_map = { {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}} };
			Assert::AreEqual(my_map, result);
		}

		TEST_METHOD(testCreatemap_rot180rect) // rotate rectangle by 180 deg
		{
			const auto result = create_map(3, 3, 180);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}

		TEST_METHOD(testCreatemap_rot270rect) // rotate rectangle by 270 deg
		{
			const auto result = create_map(2, 2, 270);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = { {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}} };
			Assert::AreEqual(map, result);
		}

		TEST_METHOD(testCreatemap_rot360rect) // rotate rectangle by 360 deg
		{
			const auto result = create_map(3, 3, 360);
			const std::map <std::pair<int, int>, std::pair<int, int>> map = {
				{{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}, {{0,0},{1,1}}
			};
			Assert::AreEqual(map, result);
		}
	};
}