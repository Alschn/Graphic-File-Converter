#include "pch.h"
#include "CppUnitTest.h"
#include <map>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(testRotation)
	{
	public:

		static std::map <std::pair<int, int>, std::pair<int, int>> test_map(int height, int width, int num)
		{
			std::map <std::pair<int, int>, std::pair<int, int>> map;

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					int x_n = j;
					int y_n = i;
					switch (num)
					{
					case 0:
						// vertical mirror reflection
						x_n = width - j - 1;
						break;
					case 1:
						// horizontal mirror reflection
						y_n = height - i - 1;
						break;
					case 2:
						// diagonal mirror reflection y = x ONLY FOR SQUARES
						x_n = i;
						y_n = j;
						break;
					case 3:
						// diagonal mirror reflection y = -x+height ONLY FOR SQUARES
						x_n = width - i - 1;
						y_n = height - j - 1;
						break;
					default:
						break;
					}

					map.emplace(std::make_pair(std::make_pair(j, i), std::make_pair(x_n, y_n)));
				}
			}
			return this->map;
		};
		TEST_METHOD(test)
		{
			Assert::AreEqual(1, 1);
		}
	};
}
