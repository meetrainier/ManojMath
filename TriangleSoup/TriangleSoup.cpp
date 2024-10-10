// TriangleSoup.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

#include <iostream>
#include <vector>
#include <array>
#include "TriangleSoupApi.h"

using namespace std;

// Helper function to compute the signed distance from a point to the plane
double signed_distance_to_plane(const Point3d& point, const Plane& plane) {
  return (point.x - plane.p.x) * plane.normal.x +
    (point.y - plane.p.y) * plane.normal.y +
    (point.z - plane.p.z) * plane.normal.z;
}

// Function to group triangles based on the relation to the plane
int group_triangles(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles, Plane plane, Triangle_groups& triangle_groups) {
  const double EPSILON = 1e-9;  // Tolerance for floating-point comparison

  for (size_t i = 0; i < vec_triangles.size(); ++i) {
    const array<size_t, 3>& triangle = vec_triangles[i];

    // Get the 3 points of the triangle
    const Point3d& p0 = vec_points[triangle[0]];
    const Point3d& p1 = vec_points[triangle[1]];
    const Point3d& p2 = vec_points[triangle[2]];

    // Compute the signed distances of each point from the plane
    double d0 = signed_distance_to_plane(p0, plane);
    double d1 = signed_distance_to_plane(p1, plane);
    double d2 = signed_distance_to_plane(p2, plane);

    // Classify each point based on its signed distance
    int on_plane = 0, positive = 0, negative = 0;

    auto classify_point = [&](double d) {
      if (abs(d) < EPSILON) on_plane++;
      else if (d > 0) positive++;
      else negative++;
    };

    classify_point(d0);
    classify_point(d1);
    classify_point(d2);

    // Classify the triangle based on the number of points in each category
    if (positive == 3) {
      // All points are on the positive side
      triangle_groups.positive_set_exclusive.emplace_back(i);
    }
    else if (negative == 3) {
      // All points are on the negative side
      triangle_groups.negative_set_exclusive.emplace_back(i);
    }
    else if (on_plane == 3) {
      // All points lie on the plane
      triangle_groups.neutral_set_3_points_on_plane.emplace_back(i);
    }
    else if (positive == 2 && on_plane == 1) {
      // Two points are on the positive side, one point on the plane
      triangle_groups.positive_set_1p_on_plane.emplace_back(i);
    }
    else if (positive == 1 && on_plane == 2) {
      // One point on the positive side, two points on the plane
      triangle_groups.positive_set_2p_on_plane.emplace_back(i);
    }
    else if (negative == 2 && on_plane == 1) {
      // Two points on the negative side, one point on the plane
      triangle_groups.negative_set_1p_on_plane.emplace_back(i);
    }
    else if (negative == 1 && on_plane == 2) {
      // One point on the negative side, two points on the plane
      triangle_groups.negative_set_2p_on_plane.emplace_back(i);
    }
    else if (positive > 0 && negative > 0) {
      // Triangle intersects the plane, with points on both sides
      triangle_groups.triangles_intersected_by_plane.emplace_back(i);
    }
    else {
      return -1;  // Error: unhandled case
    }
  }

  return 0;  // Success
}

