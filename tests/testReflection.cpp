#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/reflection.h"
// #include "../graphic-file-converter/rotation.h"
// #include "../graphic-file-converter/converter.h"
// #include "../graphic-file-converter/converter.cpp"
// #include "../graphic-file-converter/rotation.cpp"
#include "../graphic-file-converter/reflection.cpp"
// #include "../graphic-file-converter/image.cpp"
// #include "../graphic-file-converter/image.h"
// #include "../graphic-file-converter/main.cpp"
// #include "../graphic-file-converter/utils.h"
// #include "../graphic-file-converter/utils.cpp"
#include <map>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testReflection)
	{
	public:
		static bool compareMaps(std::map <std::pair<int, int>, std::pair<int, int>> map_1, std::map <std::pair<int, int>, std::pair<int, int>> map_2)
		{
			if (map_1 == map_2)
			{
				return true;
			}
			return false;
		};

		TEST_METHOD(testCreateMap_sq0) // Square Vertical
		{
			auto result = Reflection::createMap(2, 2, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map0 = {
				{{0, 0}, {1, 0}},
				{{1, 0}, {0, 0}},
				{{0, 1}, {1, 1}},
				{{1, 1}, {0, 1}}
			};
			Assert::IsTrue(compareMaps(map0, result));
		}

		TEST_METHOD(testCreatemap_sq1) // Square Horizontal
		{
			auto result = Reflection::createMap(2, 2, 1);
			const std::map <std::pair<int, int>, std::pair<int, int>> map1 = {
				{{0, 0}, {0, 1}},
				{{1, 0}, {1, 1}},
				{{0, 1}, {0, 0}},
				{{1, 1}, {1, 0}}

			};
			Assert::IsTrue(compareMaps(map1, result));
		}

		TEST_METHOD(testCreatemap_sq2) // Square Diagonal 1
		{
			auto result = Reflection::createMap(2, 2, 2);
			const std::map <std::pair<int, int>, std::pair<int, int>> map2 = {
				{{0, 0}, {0, 0}},
				{{1, 0}, {0, 1}},
				{{0, 1}, {1, 0}},
				{{1, 1}, {1, 1}}
			};
			Assert::IsTrue(compareMaps(map2, result));
		}

		TEST_METHOD(testCreatemap_sq3) // Square Diagonal 2
		{
			auto result = Reflection::createMap(2, 2, 3);
			const std::map <std::pair<int, int>, std::pair<int, int>> map3 = {
				{{0, 0}, {1, 1}},
				{{1, 0}, {1, 0}},
				{{0, 1}, {0, 1}},
				{{1, 1}, {0, 0}}
			};
			Assert::IsTrue(compareMaps(map3, result));
		}

		TEST_METHOD(testCreatemap_rect0) // Rectangle Vertical
		{
			auto result = Reflection::createMap(3, 2, 0);
			const std::map <std::pair<int, int>, std::pair<int, int>> map4 = {
				{{0, 0}, {1, 0}},
				{{1, 0}, {0, 0}},
				{{0, 1}, {1, 1}},
				{{1, 1}, {0, 1}},
				{{0, 2}, {1, 2}},
				{{1, 2}, {0, 2}}
			};
			Assert::IsTrue(compareMaps(map4, result));
		}

		TEST_METHOD(testCreatemap_rect1) /// Rectangle Horizontal
		{
			auto result = Reflection::createMap(3, 2, 1);
			const std::map <std::pair<int, int>, std::pair<int, int>> map5 = {
				{{0, 0}, {0, 2}},
				{{1, 0}, {1, 2}},
				{{0, 1}, {0, 1}},
				{{1, 1}, {1, 1}},
				{{0, 2}, {0, 0}},
				{{1, 2}, {1, 0}}

			};
			Assert::IsTrue(compareMaps(map5, result));
		}
		TEST_METHOD(testCreatemap_rect2) // Rectangle Diagonal 1
		{
			auto result = Reflection::createMap(3, 2, 2);
			std::map <std::pair<int, int>, std::pair<int, int>> map6 = {
				{{0, 0}, {0, 0}},
				{{1, 0}, {0, 1}},
				{{0, 1}, {1, 0}},
				{{1, 1}, {1, 1}},
				{{0, 2}, {2, 0}},
				{{1, 2}, {2, 1}}
			};
			Assert::IsTrue(compareMaps(map6, result));
		}
		TEST_METHOD(testCreatemap_rect3) // Rectangle Diagonal 2
		{
			auto result = Reflection::createMap(3, 2, 3);
			std::map <std::pair<int, int>, std::pair<int, int>> map7 = {
				{{0, 0}, {1, 2}},
				{{1, 0}, {1, 1}},
				{{0, 1}, {0, 2}},
				{{1, 1}, {0, 1}},
				{{0, 2}, {-1, 2}},
				{{1, 2}, {-1, 1}}
			};
			Assert::IsTrue(compareMaps(map7, result));
		}

	};
}