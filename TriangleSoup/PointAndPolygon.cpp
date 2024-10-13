#include "pch.h"

#include <iostream>
#include <vector>
#include <cmath>

#include "TriangleSoupApi.h"

using namespace std;

// Helper function to check if two values are approximately equal (for floating-point comparisons)
bool is_approx_equal(double a, double b, double epsilon = 1e-9) {
  return fabs(a - b) < epsilon;
}

// Function to check if a point is collinear and lies on the line segment between two points A and B
bool is_point_on_segment(const Point3d& p, const Point3d& a, const Point3d& b) {
  // Check if the point is collinear with the segment using the cross-product approach
  double cross_product = (b.x - a.x) * (p.y - a.y) - (p.x - a.x) * (b.y - a.y);

  if (!is_approx_equal(cross_product, 0.0)) {
    return false;  // The point is not collinear with the segment
  }

  // Check if the point lies within the bounds of the segment
  if (p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
    p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y)) {
    return true;
  }

  return false;
}

// Function to determine if a point lies on the boundary of the polygon
bool point_on_polygon(const Point3d& point, const Polygon& polygon) {
  size_t n = polygon.vec_points.size();

  // Iterate through each edge of the polygon
  for (size_t i = 0; i < n; ++i) {
    const Point3d& a = polygon.vec_points[i];
    const Point3d& b = polygon.vec_points[(i + 1) % n];  // Ensure it wraps around to the first point

    if (is_point_on_segment(point, a, b)) {
      return true;  // The point lies on this edge
    }
  }

  return false;  // The point does not lie on any of the polygon's edges
}

// Example usage
//int main() {
//  // Define a polygon (square in this case)
//  Polygon polygon = { {{0, 0, 0}, {4, 0, 0}, {4, 4, 0}, {0, 4, 0}} };
//
//  // Define some points to test
//  Point3d point1 = { 2, 0, 0 };  // On the bottom edge
//  Point3d point2 = { 4, 2, 0 };  // On the right edge
//  Point3d point3 = { 2, 2, 0 };  // Inside the polygon
//  Point3d point4 = { 5, 0, 0 };  // Outside the polygon
//
//  // Test points
//  cout << "Point 1 on polygon: " << point_in_polygon(point1, polygon) << endl;  // Expected: true
//  cout << "Point 2 on polygon: " << point_in_polygon(point2, polygon) << endl;  // Expected: true
//  cout << "Point 3 on polygon: " << point_in_polygon(point3, polygon) << endl;  // Expected: false
//  cout << "Point 4 on polygon: " << point_in_polygon(point4, polygon) << endl;  // Expected: false
//
//  return 0;
//}
