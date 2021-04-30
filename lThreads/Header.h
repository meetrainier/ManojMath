#pragma once
#include <vector>
#include <future>
#include <thread>

#include <vector>
#include <cmath> 
#include <future>
#include <thread>
#include <cassert> 

struct Point2d
{
	double x, y;
};

struct Box
{
	double xmin, ymin, xmax, ymax;
	Box() {
		xmin = 0;
		ymin = 0;
		xmax = 0;
		ymax = 0;

	}
	Box(double xmin1, double ymin1, double xmax1, double ymax1)
	{
		xmin = xmin1;
		ymin = ymin1;
		xmax = xmax1;
		ymax = ymax1;
	}

	void Translate(double delta_x, double delta_y)
	{
		xmin += delta_x;
		ymin += delta_y;
		xmax += delta_x;
		ymax += delta_y;
	}
};

class Ex {

	double m_x;
	double m_y;
	double m_qf;

public:
	Ex(double in_x, double in_y, double in_qf)
	{
		m_x = in_x;
		m_y = in_y;
		m_qf = in_qf;

	}
	using Vec2d = std::vector<Point2d>;
	using Result = std::vector<std::vector<Point2d>>;
	//Ex::Result Query(const Box& ipEnvelope)const;
	Vec2d FindWithin(Box box, std::vector<Point2d>& vec) const;

};

struct P2d
{
    double x, y;
};


