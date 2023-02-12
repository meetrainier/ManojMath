/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

#include <algorithm>
#include <future>
#include <iostream>
#include <random> 
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

namespace bg = boost::geometry;

typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
typedef bg::model::polygon<point_t> polygon_t;

//<typename T> 
void generate_random_points(long count, std::pair<double,double> limits, vector<point_t>& vecPoints)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  //std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
  std::uniform_real_distribution<> dis(limits.first, limits.second);//uniform distribution between 0 and 1
  point_t p(0.0,0.0);
  for (long n = 0; n < count; ++n) {
    //std::cout << dis(gen) << ' ';
    p.set<0>(dis(gen));
    p.set<1>(dis(gen));
   // p.set<2>(dis(gen));
    vecPoints.emplace_back(p);
  }
}

void CreatePolygon(polygon_t& poly)
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
  auto future1 = std::async(std::transform<InputItType, OutputItType, UnaryType>, begin(p_vec1), end(p_vec1), begin(vec_b1), unaryOp);

  std::vector<bool> vec_b2(p_vec1.size());
  std::vector<bool> final_result(begin(vec_b1), end(vec_b1));
  auto future2 = std::async(std::transform<InputItType, OutputItType, UnaryType>, begin(p_vec2), end(p_vec2), begin(vec_b2), unaryOp);

  final_result.insert(end(final_result), begin(vec_b2), end(vec_b2));

  for (auto x : final_result)
    std::cout << x << ";\t";
  std::cout << std::endl;

}

void PointsInPolygonMultiThreaded21()
{
  //A version of PointsInPolygonMultiThreaded2() that uses array 
  polygon_t poly;
  CreatePolygon(poly);

  point_t p1(.5, .5), p2(2.0, 2.0), p3(3.0, 3.0), p4(4.5, 4.5);

  std::vector<point_t> p_vec[2] = { { p1, p2 }, { p3, p4 } };

  std::vector<bool>::iterator it;

  using InputItType = std::vector<point_t>::iterator;
  using OutputItType = std::vector<bool>::iterator;
  auto const unaryOp = [poly](point_t& x) {return boost::geometry::within(x, poly); };
  using UnaryType = decltype(unaryOp);

  // Provide the missing type information the compiler fails to deduce.
  std::vector<bool> vec_b[2];
  std::vector<bool> final_result;
  for (int i = 0; i < 2; ++i)
  {
    vec_b[i].resize(2);
    auto future = std::async(std::transform<InputItType, OutputItType, UnaryType>, begin(p_vec[i]), end(p_vec[i]), begin(vec_b[i]), unaryOp);
  }

  for (int i = 0; i < 2; ++i)
  {
    final_result.insert(end(final_result), begin(vec_b[i]), end(vec_b[i]));
  }

  for (auto x : final_result)
    std::cout << x << ";\t";

  std::cout << std::endl;

}

void PointsInPolygonMultiThreaded22()
{
  //A version of PointsInPolygonMultiThreaded21() that uses array, and tries it with more number fo points. 
  polygon_t poly;
  CreatePolygon(poly);

  vector<point_t> vecPoints;
  long num_points = 1000'000;
  generate_random_points(1000'000, { .5,5 }, vecPoints);
  long size_of_one_vec = 100'000;

  std::vector<std::vector<point_t>> p_vec_vec;
  long num_of_vectors = num_points / size_of_one_vec;
  for (long i = 0L; i < num_of_vectors; ++i)
  {
    std::vector<point_t> vec;
    vec.insert(end(vec),begin(vecPoints)+i*size_of_one_vec, begin(vecPoints)+(i+1)*size_of_one_vec);
    p_vec_vec.emplace_back(vec);
  }

  std::vector<bool>::iterator it;

  using InputItType = std::vector<point_t>::iterator;
  using OutputItType = std::vector<bool>::iterator;
  auto const unaryOp = [poly](point_t& x) {return boost::geometry::within(x, poly); };
  using UnaryType = decltype(unaryOp);

  // Provide the missing type information the compiler fails to deduce.
  std::vector<std::vector<bool>> b_vec_vec;
  b_vec_vec.resize(num_of_vectors);
  std::vector<bool> final_result;
  for (int i = 0; i < num_of_vectors; ++i)
  {
    b_vec_vec[i].resize(size_of_one_vec);
    auto future = std::async(std::transform<InputItType, OutputItType, UnaryType>, begin(p_vec_vec[i]), end(p_vec_vec[i]), begin(b_vec_vec[i]), unaryOp);
  }

  for (int i = 0; i < num_of_vectors; ++i)
  {
    final_result.insert(end(final_result), begin(b_vec_vec[i]), end(b_vec_vec[i]));
  }

  for (auto x : final_result)
    std::cout << x << ";\t";

  std::cout << std::endl;

}

//void PointsInPolygonMultiThreaded1()
//{
//  polygon_t poly;
//  CreatePolygon(poly);
//
//  point_t p1(.5, .5), p2(2.0, 2.0), p3(3.0, 3.0), p4(4.5, 4.5);
//
//  std::vector<point_t>  p_vec1({ p1, p2 });
//  std::vector<point_t>  p_vec2({ p3, p4 });
//
//  std::vector<bool> vec_b1(p_vec1.size());
//  std::vector<bool>::iterator it;
//  auto future1 = std::async(std::transform<InputItType, OutputItType, bool [](point_t& x)>, begin(p_vec1), end(p_vec1), begin(vec_b1), [poly](point_t& x) {return boost::geometry::within(x, poly); });
//
//  //std::vector<bool> vec_b2(p_vec1.size());
//  //auto future2 = std::async(std::transform<InputItType, OutputItType, UnaryType>, begin(p_vec2), end(p_vec2), begin(vec_b2), [poly](point_t& x) {return boost::geometry::within(x, poly); });
//
//  std::vector<bool> final_result(begin(vec_b1), end(vec_b1));
//  final_result.insert(end(final_result), begin(vec_b2), end(vec_b2));
//
//  for (auto x : final_result)
//    std::cout << x << ";\t";
//  std::cout << std::endl;
//
//}

void PointsInPolygon()
{
  polygon_t poly;
  CreatePolygon(poly);
  point_t p1(.5, .5), p2(2.0, 2.0), p3(3.0, 3.0), p4(4.5, 4.5);
  std::vector<point_t>  p_vec({ p1, p2, p3, p4 });
  std::vector<bool> vec_b;
  for (auto& x : p_vec)
  {
    bool is_within = boost::geometry::within(x, poly);
    vec_b.emplace_back(is_within);
  }
  for (bool x : vec_b)
    std::cout << x << ";\t";
  std::cout << std::endl;

  std::vector<bool> vec_b1(p_vec.size());
  std::transform(begin(p_vec), end(p_vec), begin(vec_b1), [poly](point_t& x) {return boost::geometry::within(x, poly); });
  for (auto x : vec_b1)
    std::cout << x << ";\t";
  std::cout << std::endl;

}

bool fun(point_t& p)
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

  std::vector<point_t>  p_vec1({ p1, p2 });
  std::vector<point_t>  p_vec2({ p3, p4 });


  std::vector<bool> vec_b1(p_vec1.size());
  std::vector<bool>::iterator it;
  //std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), [poly](point_t& x) {return boost::geometry::within(x, poly); });

  std::vector<bool> vec_b2(p_vec1.size());
  //std::async(std::transform, begin(p_vec2), end(p_vec2), begin(vec_b2), [poly](point_t& x) {return boost::geometry::within(x, poly); });

  std::vector<bool> final_result(begin(vec_b1), end(vec_b1));
  final_result.insert(end(final_result), begin(vec_b2), end(vec_b2));

  //std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), [poly](point_t& x) {return 1; });
  //std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), [](point_t &x) {return true; });

  //std::future <std::vector<bool>::iterator > it = std::async(std::transform, begin(p_vec1), end(p_vec1), begin(vec_b1), fun);
  //std::future <std::vector<bool>::iterator > it = std::async(std::transform<std::vector<point_t>::iterator, std::vector<bool>::iterator,bool(point_3)>, 
  //   begin(p_vec1), end(p_vec1), begin(vec_b1), fun);

  std::future<int> ft6 = std::async(square_it, 2);

  std::vector<bool>b2(p_vec2.size());

  std::array<int, 8> foo = { 3,5,7,11,13,17,19,23 };
  if (std::all_of(foo.begin(), foo.end(), [](int i) {return i % 2; }))
    std::cout << "All the elements are odd numbers.\n";
  //  for (auto& x : vec_b)
  //    std::cout << x << ";\t";
   // std::cout << std::endl;


}



