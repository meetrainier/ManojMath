#include <algorithm> 
#include <iostream>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

namespace bg = boost::geometry;

typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
typedef bg::model::polygon<point_t> polygon_t; 

void CreatePolygon(polygon_t &poly)
{
  polygon_t polygon2{ {{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}, {0.0, 0.0}},
                       {{1.0, 1.0}, {4.0, 1.0}, {4.0, 4.0}, {1.0, 4.0}, {1.0, 1.0}} }; 
  poly = polygon2;

}

void PointsInPolygon()
{
  polygon_t poly;
  CreatePolygon(poly);
  point_t p1(.5, .5), p2(2.0, 2.0), p3(3.0, 3.0), p4(4.5, 4.5);
  std::vector<point_t>  p_vec({ p1, p2, p3, p4 });
  std::vector<bool> vec_b;
  for (auto &x:p_vec)
  {
    bool is_within = boost::geometry::within(x,poly);
    vec_b.emplace_back(is_within);
  }
  for (auto& x : vec_b)
    std::cout << x << ";\t";
  std::cout << std::endl;

  std::vector<bool> vec_b1(p_vec.size());
  std::transform(begin(p_vec), end(p_vec), begin(vec_b1), [poly](point_t &x) {return boost::geometry::within(x, poly); });
  for (auto& x : vec_b1)
    std::cout << x << ";\t";
  std::cout << std::endl;


}


