#include <algorithm>
#include <future>
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

void PointsInPolygonMultiThreaded2()
{
  polygon_t poly;
  CreatePolygon(poly);

  point_t p1(.5, .5), p2(2.0, 2.0), p3(3.0, 3.0), p4(4.5, 4.5);

  std::vector<point_t>  p_vec1({ p1, p2 });
  std::vector<point_t>  p_vec2({ p3, p4 });

  std::vector<bool> vec_b1(p_vec1.size());
  std::vector<bool>::iterator it;

  using InputItType = std::vector<point_t>::iterator;
  using OutputItType = std::vector<bool>::iterator;
  auto const unaryOp = [poly](point_t& x) {return boost::geometry::within(x, poly); };
  using UnaryType = decltype(unaryOp);

  // Provide the missing type information the compiler fails to deduce.
  std::async(std::transform<InputItType, OutputItType, UnaryType>, begin(p_vec1), end(p_vec1), begin(vec_b1), unaryOp);

  std::vector<bool> vec_b2(p_vec1.size());
  std::async(std::transform<InputItType, OutputItType, UnaryType>, begin(p_vec2), end(p_vec2), begin(vec_b2), unaryOp);

  std::vector<bool> final_result(begin(vec_b1), end(vec_b1));
  final_result.insert(end(final_result), begin(vec_b2), end(vec_b2));
}
void PointsInPolygonMultiThreaded1()
{
  polygon_t poly;
  CreatePolygon(poly);

  point_t p1(.5, .5), p2(2.0, 2.0), p3(3.0, 3.0), p4(4.5, 4.5);

  std::vector<point_t>  p_vec1({ p1, p2 });
  std::vector<point_t>  p_vec2({ p3, p4 });

  std::vector<bool> vec_b1(p_vec1.size());
  std::vector<bool>::iterator it;
  //std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), [poly](point_t& x) {return boost::geometry::within(x, poly); });

  std::vector<bool> vec_b2(p_vec1.size());
  //std::async(std::transform, begin(p_vec2), end(p_vec2), begin(vec_b2), [poly](point_t& x) {return boost::geometry::within(x, poly); });

  std::vector<bool> final_result(begin(vec_b1), end(vec_b1));
  final_result.insert(end(final_result), begin(vec_b2), end(vec_b2));
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

bool fun(point_t &p)
{
  return true;
}

int square_it(int a)
{
  return a * a;
}


void PointsInPolygonMultiThreaded()
{
  polygon_t poly;
  CreatePolygon(poly);
  
  point_t p1(.5, .5), p2(2.0, 2.0), p3(3.0, 3.0), p4(4.5, 4.5);
  
  std::vector<point_t>  p_vec1({ p1, p2});
  std::vector<point_t>  p_vec2({ p3, p4 });


  std::vector<bool> vec_b1(p_vec1.size());
  std::vector<bool>::iterator it;
  //std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), [poly](point_t& x) {return boost::geometry::within(x, poly); });
  
  std::vector<bool> vec_b2(p_vec1.size());
  //std::async(std::transform, begin(p_vec2), end(p_vec2), begin(vec_b2), [poly](point_t& x) {return boost::geometry::within(x, poly); });

  std::vector<bool> final_result(begin(vec_b1),end(vec_b1));
  final_result.insert(end(final_result), begin(vec_b2), end(vec_b2));

  //std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), [poly](point_t& x) {return 1; });
  //std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), [](point_t &x) {return true; });
  
  //std::future <std::vector<bool>::iterator > it = std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), fun);
  //std::future <std::vector<bool>::iterator > it = std::async(std::transform<std::vector<point_t>::iterator, std::vector<bool>::iterator,bool(point_3)>, 
  //   begin(p_vec1), end(p_vec1), begin(vec_b1), fun);

  std::future<int> ft6 = std::async (square_it, 2);

  std::vector<bool>b2(p_vec2.size());

  std::array<int, 8> foo = { 3,5,7,11,13,17,19,23 };
  if (std::all_of(foo.begin(), foo.end(), [](int i) {return i % 2; }))
    std::cout << "All the elements are odd numbers.\n";
//  for (auto& x : vec_b)
//    std::cout << x << ";\t";
 // std::cout << std::endl;


}


