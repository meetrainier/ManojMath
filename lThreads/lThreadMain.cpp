#include <vector>
#include <future>
#include <thread>
#include "Header.h"
#include "lThreadTest.h"

Ex::Vec2d Ex::FindWithin(Box box, std::vector<Point2d>& vec) const
{
	box.Translate(m_x, 0.0);
	//do some calculations 
	auto d1 = sqrt(3) + sqrt(5) - sqrt(7);
	auto d2 = pow(d1, 5);
	//
	box.Translate(0.0, m_y);
	Vec2d vecLocal;
	for (auto& p : vec)
	{
		if (p.x < box.xmax && p.x > box.xmin)
		{
			if (p.y < box.ymax && p.x > box.ymin)
			{
				vecLocal.emplace_back(p);
			}
		}
	}
	return vecLocal;
}

void TestThread()
{

}
int main()
{
	TestAsync();
}
