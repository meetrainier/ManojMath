#include "Header.h"
int Test1()
{
	Box b1(-2.0, -2.0, 3.0, 3.0);
	std::vector<Point2d> vec1{ {6,6}, {1,1 }, {2,2} };
	Ex ex1(2, 2, 0.0);
	std::future<std::vector<Point2d>> task1 = std::async(&Ex::FindWithin, &ex1, b1, std::ref(vec1));
	std::vector<Point2d> vec2{ {1,1 }, {2,2}, {3,3} };
	std::future<std::vector<Point2d>> task2 = std::async(&Ex::FindWithin, &ex1, b1, std::ref(vec2));
	std::vector<Point2d> vec3{ {6,6}, {7,7 }, {8,8} };
	std::future<std::vector<Point2d>> task3 = std::async(&Ex::FindWithin, &ex1, b1, std::ref(vec3));

	Box b2(-2.0, -2.0, 8.0, 8.0);
	std::vector<Point2d> vec4{ {6,6}, {7,7 }, {8,8} };
	std::future<std::vector<Point2d>> task4 = std::async(&Ex::FindWithin, &ex1, b2, std::ref(vec4));

	auto r1 = task1.get(); assert(2 == r1.size());
	auto r2 = task2.get(); assert(3 == r2.size());
	auto r3 = task3.get(); assert(0 == r3.size());

	auto r4 = task4.get(); assert(3 == r4.size());

	//std::future<std::vector<Point2d>> cTask = std::async(FindWithin2, 0.0, 0.0,5.0,5.0,vec1);

	return 0;
}

int Test2()
{
	Box b1(-2.0, -2.0, 3.0, 3.0);
	std::vector<Point2d> vec1{ {6,6}, {1,1 }, {2,2} };
	Ex ex1(2, 2, 0.0);
	std::future<std::vector<Point2d>> task1 = std::async(std::launch::deferred, &Ex::FindWithin, &ex1, b1, std::ref(vec1));
	std::vector<Point2d> vec2{ {1,1 }, {2,2}, {3,3} };
	std::future<std::vector<Point2d>> task2 = std::async(std::launch::deferred, &Ex::FindWithin, &ex1, b1, std::ref(vec2));
	std::vector<Point2d> vec3{ {6,6}, {7,7 }, {8,8} };
	std::future<std::vector<Point2d>> task3 = std::async(std::launch::deferred, &Ex::FindWithin, &ex1, b1, std::ref(vec3));

	Box b2(-2.0, -2.0, 8.0, 8.0);
	std::vector<Point2d> vec4{ {6,6}, {7,7 }, {8,8} };
	std::future<std::vector<Point2d>> task4 = std::async(std::launch::deferred, &Ex::FindWithin, &ex1, b2, std::ref(vec4));

	auto r1 = task1.get(); assert(2 == r1.size());
	auto r2 = task2.get(); assert(3 == r2.size());
	auto r3 = task3.get(); assert(0 == r3.size());

	auto r4 = task4.get(); assert(3 == r4.size());

	return 0;
}

int Test3()
{
	Box b1(-2.0, -2.0, 3.0, 3.0);
	std::vector<Point2d> vec1{ {6,6}, {1,1 }, {2,2} };
	Ex ex1(2, 2, 0.0);
	std::future<std::vector<Point2d>> task1 = std::async(std::launch::async, &Ex::FindWithin, &ex1, b1, std::ref(vec1));
	std::vector<Point2d> vec2{ {1,1 }, {2,2}, {3,3} };
	std::future<std::vector<Point2d>> task2 = std::async(std::launch::async, &Ex::FindWithin, &ex1, b1, std::ref(vec2));
	std::vector<Point2d> vec3{ {6,6}, {7,7 }, {8,8} };
	std::future<std::vector<Point2d>> task3 = std::async(std::launch::async, &Ex::FindWithin, &ex1, b1, std::ref(vec3));

	Box b2(-2.0, -2.0, 8.0, 8.0);
	std::vector<Point2d> vec4{ {6,6}, {7,7 }, {8,8} };
	std::future<std::vector<Point2d>> task4 = std::async(std::launch::async, &Ex::FindWithin, &ex1, b2, std::ref(vec4));

	auto r1 = task1.get(); assert(2 == r1.size());
	auto r2 = task2.get(); assert(3 == r2.size());
	auto r3 = task3.get(); assert(0 == r3.size());

	auto r4 = task4.get(); assert(3 == r4.size());
	return 0;
}

void TestAsync()
{
	Test1();
	Test2();
	Test3();
}

