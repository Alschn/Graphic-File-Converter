#include "pch.h"
#include "CppUnitTest.h"
#include "../graphic-file-converter/rotation.h"
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//namespace Tests
//{
//	TEST_CLASS(testReflection)
//	{
//	public:
//
//		TEST_METHOD(testCreatemap_rot90sq) // rotate square by 90 deg
//		{
//			auto result = Rotation::create_map(2, 2, 90);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0} , {0, 1}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {1, 0} }
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//
//		TEST_METHOD(testCreatemap_rot180sq) // rotate square by 180 deg
//		{
//			auto result = Rotation::create_map(2, 2, 180);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0} , {1, 1}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 0}}, {{1, 1} , {0, 0} }
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//
//		TEST_METHOD(testCreatemap_270sq) // rotate square by 270 deg
//		{
//			auto result = Rotation::create_map(2, 2, 270);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0} , {1, 0}}, {{1, 0} , {0, 1}}, {{0, 1} , {0, 0}}, {{1, 1} , {0, 0} }
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//
//		TEST_METHOD(testCreatemap_360sq) // rotate square by 360 deg
//		{
//			auto result = Rotation::create_map(2, 2, 360);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0}, {0, 0}}, {{1, 0}, {1, 0}}, {{0, 1}, {0, 1}}, {{1, 1}, {1, 1} }
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//		TEST_METHOD(testCreatemap_randang) // rotate square by angle which is not multiple of 90
//		{
//			// tutaj oczekiwanie wyjatku
//		}
//		TEST_METHOD(testCreatemap_largeang) // rotate square by angle greater than 360
//		{
//			auto result = Rotation::create_map(2, 2, 450);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0} , {0, 1}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {1, 0} }
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//		TEST_METHOD(testCreatemap_rot90rect) // rotate rectangle by 90 deg
//		{
//			auto result = Rotation::create_map(3, 2, 90);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0} , {0, 1}}, {{1, 0} , {0, 0}}, {{0, 1} , {1, 1}}, {{1, 1} , {1, 0}}, {{0, 2} , {2, 1}}, {{1, 2} , {2, 0}}
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//
//		TEST_METHOD(testCreatemap_rot180rect) // rotate rectangle by 180 deg
//		{
//			auto result = Rotation::create_map(3, 2, 180);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0} , {1, 2}}, {{1, 0} , {0, 1}}, {{0, 1} , {1, 1}}, {{1, 1} , {0, 0}}, {{0, 2} , {1, 0}}, {{1, 2} , {0, 0}}
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//
//		TEST_METHOD(testCreatemap_rot270rect) // rotate rectangle by 270 deg
//		{
//			auto result = Rotation::create_map(3, 2, 270);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0} , {2, 0}}, {{1, 0} , {1, 1}}, {{0, 1} , {1, 0}}, {{1, 1} , {0, 0}}, {{0, 2} , {0, 0}}, {{1, 2} , {0, 0} }
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//
//		TEST_METHOD(testCreatemap_rot360rect) // rotate rectangle by 360 deg
//		{
//			auto result = Rotation::create_map(3, 2, 360);
//			std::map <std::pair<int, int>, std::pair<int, int>> map = {
//				{{0, 0}, {0, 0}}, {{1, 0}, {1, 0}}, {{0, 1}, {0, 1}}, {{1, 1}, {1, 1}}, {{0, 2}, {0, 2}}, {{1, 2}, {1, 2} }
//			};
//			Assert::AreEqual(static_cast<std::map <std::pair<int, int>, std::pair<int, int>>>(map), result);
//		}
//	};
//}