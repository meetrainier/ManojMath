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


// Helper function to check if a point is inside a polygon using ray-casting
//bool point_in_polygon(const Point3d& point, const Polygon& polygon) {
//  int crossings = 0;
//  size_t n = polygon.vec_points.size();
//  for (size_t i = 0; i < n; ++i) {
//    const Point3d& p1 = polygon.vec_points[i];
//    const Point3d& p2 = polygon.vec_points[(i + 1) % n];
//    // Check if the ray from the point crosses the edge of the polygon
//    if (((p1.y > point.y) != (p2.y > point.y)) &&
//      (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)) {
//      crossings++;
//    }
//  }
//  // If the number of crossings is odd, the point is inside the polygon
//  return (crossings % 2 == 1);
//}
//
//// Function to check if a point is on the vertical surface of the prism
//bool point_on_prism_surface(const Point3d& point, const Prism& prism) {
//  // Check if the point is on the base polygon or on the top face
//  return point_in_polygon(point, prism.base_polygon) &&
//    (point.z == 0 || fabs(point.z - prism.height) < 1e-9);
//}
//
//// Function to check if all points of the triangle lie within the prism
//bool triangle_in_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
//  for (size_t i = 0; i < 3; ++i) {
//    const Point3d& p = vec_points[triangle[i]];
//    if (!point_in_polygon(p, prism.base_polygon) || p.z < 0 || p.z > prism.height) {
//      return false;
//    }
//  }
//  return true;
//}
//
//// Function to check if a triangle is on the prism surface
//bool triangle_on_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
//  for (size_t i = 0; i < 3; ++i) {
//    const Point3d& p = vec_points[triangle[i]];
//    if (!point_on_prism_surface(p, prism)) {
//      return false;
//    }
//  }
//  return true;
//}

// Function to check if a triangle intersects the prism
//bool triangle_intersects_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
//  bool has_inside = false, has_outside = false;
//  for (size_t i = 0; i < 3; ++i) {
//    const Point3d& p = vec_points[triangle[i]];
//    if (point_in_polygon(p, prism.base_polygon) && p.z >= 0 && p.z <= prism.height) {
//      has_inside = true;
//    }
//    else {
//      has_outside = true;
//    }
//    if (has_inside && has_outside) {
//      return true;
//    }
//  }
//  return false;
//}

// Main function to group triangles
//int group_triangles(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles, Prism& prism, Prism_Triangle_Groups& triangle_groups) {
//  for (size_t i = 0; i < vec_triangles.size(); ++i) {
//    const array<size_t, 3>& triangle = vec_triangles[i];
//
//    if (triangle_in_prism(triangle, vec_points, prism)) {
//      triangle_groups.in_prism.push_back(i);
//    }
//    else if (triangle_on_prism(triangle, vec_points, prism)) {
//      triangle_groups.on_prism.push_back(i);
//    }
//    else if (triangle_intersects_prism(triangle, vec_points, prism)) {
//      triangle_groups.intersecting_prism.push_back(i);
//    }
//  }
//
//  return 0;  // Success
//}

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

