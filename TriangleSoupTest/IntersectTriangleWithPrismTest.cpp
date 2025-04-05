#include "pch.h"
#include <vector> 
#include <limits>
#include "TriangleSoupApi.h"

TEST(group_triangles_with_respect_to_prism_test,convex_polygon) {
  // Define points of a sample prism (square base)
  Polygon base_polygon = { {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}} };
  Prism prism = { base_polygon, 2.0 };  // height = 2.0

  // Define some example points and triangles
  vector<Point3d> vec_points = {
    // {0.5, 0.5, 1.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 2.0},   // Triangle inside
     {0.5, 0.5, 1.0}, {0.5, 0.7, 0.0}, {0.5, 0.7, 1.5},   // Triangle inside
     {1.5, 1.5, 1.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 2.0},   // Triangle intersects
      {0.0, 0.0, 2.0}, {1.0, 0.0, 2.0}, {1.0, 1.0, 2.0},    // Triangle on top surface
      {0, 0, 1.0}, {1.0, 0, 1.0}, {1, 1, 1.0} //tbd: all vertices on the prism boundary. Triangle is really inside. It classfied as on the prism!!!! 
  };

  vector<array<size_t, 3>> vec_triangles = {
      {0, 1, 2},  // 
      {3, 4, 5},  //
      {6, 7, 8},   // 
      {9, 10, 11}   // 
  };

  Prism_Triangle_Groups triangle_groups;

  int result = group_triangles_with_respect_to_prism(vec_points, vec_triangles, prism, triangle_groups);
  EXPECT_EQ(0,result);
  if (result == 0) {
    EXPECT_EQ(0, triangle_groups.in_prism[0]);
    EXPECT_EQ(1, triangle_groups.intersecting_prism[0]);
    EXPECT_EQ(2, triangle_groups.intersecting_prism[1]);
    EXPECT_EQ(2, triangle_groups.on_prism[2]);//tbd. failing the test knowingly. need to be fixed. 
    cout << "Triangles successfully grouped." << endl;
  }
  else {
    cout << "Error in grouping triangles." << endl;
  }

  // Print out the grouped triangles
  cout << "In prism: ";
  for (size_t idx : triangle_groups.in_prism) {
    cout << idx << " ";
  }
  cout << endl;

  cout << "On prism: ";
  for (size_t idx : triangle_groups.on_prism) {
    cout << idx << " ";
  }
  cout << endl;

  cout << "Intersecting prism: ";
  for (size_t idx : triangle_groups.intersecting_prism) {
    cout << idx << " ";
  }
  cout << endl;

}

// Example usage with a concave polygon base
TEST(group_triangles_with_respect_to_prism_test, concave_polygon) {
  // Define points of a concave polygon (XY-plane)
  Polygon concave_polygon = { {{0, 0, 0}, {4, 0, 0}, {4, 4, 0}, {2, 2, 0}, {0, 4, 0}} };
  Prism prism = { concave_polygon, 100'000};  // height = 3.0

  // Define some example points and triangles
  vector<Point3d> vec_points = {
      {1.0, 1.0, 1.5}, {1.5, 2.0, 1.5}, {2.0, 1.0, 1.5},   // in:Triangle fully inside
      {2.5, 2.5, 3.0}, {3.5, 3.5, 2.5}, {2.0, 2.0, 2.0},   // on:Triangle on one face of the prism. 
      {0.5, 0.5, 0.0}, {4.0, 0.0, 0.0}, {2.0, 2.0, 0.0},   // intersecting: Triangle sharing one vertex with the prism and and one vertex along an edge of the prism. 
                                                           // The tringles is inside the prism.
      {5.0, 5.0, 1.0}, {2.0, 3.0, 1.0}, {0.0, 0.0, 1.0}    // intersecting: Triangle is partially outside. 
  };

  vector<array<size_t, 3>> vec_triangles = {
      {0, 1, 2},  // 
      {3, 4, 5},  // 
      {6, 7, 8},  // 
      {9, 10, 11} //
  };

  Prism_Triangle_Groups triangle_groups;

  int result = group_triangles_with_respect_to_prism(vec_points, vec_triangles, prism, triangle_groups);
  EXPECT_EQ(0, result);
  if (result == 0) {
    EXPECT_EQ(0, triangle_groups.in_prism[0]);
    EXPECT_EQ(1, triangle_groups.on_prism[0]);
    EXPECT_EQ(2, triangle_groups.intersecting_prism[0]);
    EXPECT_EQ(3, triangle_groups.intersecting_prism[1]);
    cout << "Triangles successfully grouped." << endl;
  }
  else {
    cout << "Error in grouping triangles." << endl;
  }

  // Print out the grouped triangles
  cout << "In prism: ";
  for (size_t idx : triangle_groups.in_prism) {
    cout << idx << " ";
  }
  cout << endl;

  cout << "On prism: ";
  for (size_t idx : triangle_groups.on_prism) {
    cout << idx << " ";
  }
  cout << endl;

  cout << "Intersecting prism: ";
  for (size_t idx : triangle_groups.intersecting_prism) {
    cout << idx << " ";
  }
  cout << endl;

}

TEST(PrismTriangleIntersection, TriangleFullyInsidePrism) {
  // Triangle fully inside the prism
  Triangle triangle = { {{{1, 1, 1}, {2, 1, 1}, {1.5, 2, 1}}} };
  Polygon base_polygon = { {{0, 0, 0}, {3, 0, 0}, {3, 3, 0}, {0, 3, 0}} };
  Prism prism = { base_polygon, 3.0 };  // Height of the prism is 3

  vector<Polygon> result;
  int status = split_triangle_with_prism(triangle, prism, result);

  EXPECT_EQ(status, 0);
  EXPECT_EQ(result.size(), 1);  // Should generate one polygon
}

TEST(PrismTriangleIntersection, TrianglePartiallyIntersecting) {
  // Triangle partially intersecting the prism
  Triangle triangle = { {{{1, 1, 1}, {2, 1, 4}, {1.5, 2, 1}}} };  // One vertex outside the prism (z = 4)
  Polygon base_polygon = { {{0, 0, 0}, {3, 0, 0}, {3, 3, 0}, {0, 3, 0}} };
  Prism prism = { base_polygon, 3.0 };  // Height of the prism is 3

  vector<Polygon> result;
  int status = split_triangle_with_prism(triangle, prism, result);

  EXPECT_EQ(status, 0);
  EXPECT_EQ(result.size(), 1);  // Should generate one polygon
  // Further checks can be done to verify the vertices of the resulting polygon
}

TEST(PrismTriangleIntersection, TriangleOutsidePrism) {
  // Triangle fully outside the prism
  Triangle triangle = { {{{4, 4, 4}, {5, 4, 4}, {4.5, 5, 4}}} };  // Entire triangle outside the prism
  Polygon base_polygon = { {{0, 0, 0}, {3, 0, 0}, {3, 3, 0}, {0, 3, 0}} };
  Prism prism = { base_polygon, 3.0 };  // Height of the prism is 3

  vector<Polygon> result;
  int status = split_triangle_with_prism(triangle, prism, result);

  EXPECT_EQ(status, 0);
  EXPECT_EQ(result.size(), 0);  // No polygons should be generated
}

TEST(PrismTriangleIntersection, LargeTriangleAroundPrism) {
  // A triangle large enough to contain the entire prism
  Triangle triangle = { {{{-10, -10, 1.5}, {10, -10, 1.5}, {0, 10, 1.5}}} };
  Polygon base_polygon = { {{0, 0, 0}, {3, 0, 0}, {3, 3, 0}, {0, 3, 0}} };
  Prism prism = { base_polygon, 3.0 };  // Height of the prism is 3

  vector<Polygon> result;
  int status = split_triangle_with_prism(triangle, prism, result);

  EXPECT_EQ(status, 0);
  EXPECT_EQ(result.size(), 1);  // Should generate one polygon

  // The resulting polygon should have the same shape as the base polygon of the prism
  EXPECT_EQ(result[0].vec_points.size(), 4);  // The prism's base polygon has 4 points
}

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(PrismTriangleIntersection, LargeTriangleAroundConcavePrism) {
  // A large triangle that intersects the concave prism
  Triangle triangle = { {{{-10, -10, 1.5}, {10, -10, 1.5}, {0, 10, 1.5}}} };

  // Define a concave base polygon (U-shape)
  Polygon concave_polygon = { {{0, 0, 0}, {3, 0, 0}, {3, 1, 0}, {1, 1, 0}, {1, 3, 0}, {0, 3, 0}} };

  Prism prism = { concave_polygon, 3.0 };  // Height of the prism is 3

  vector<Polygon> result;
  int status = split_triangle_with_prism(triangle, prism, result);

  EXPECT_EQ(status, 0);
  EXPECT_EQ(result.size(), 1);  // Should generate one polygon

  // The resulting polygon should match the shape of the concave cross-section of the prism
  EXPECT_EQ(result[0].vec_points.size(), concave_polygon.vec_points.size());  // Same number of vertices as base polygon
}

