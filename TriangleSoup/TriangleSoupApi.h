#pragma once
#include <array> 
#include <vector> 
#include "MnjPoint.h"

using Point3d = MnjPoint<double>;

struct Plane {
  Point3d p;       // A point on the plane
  Point3d normal;  // The normal vector of the plane
};

struct Triangle_groups {
  vector<size_t> positive_set_exclusive;
  vector<size_t> positive_set_1p_on_plane;
  vector<size_t> positive_set_2p_on_plane;
  vector<size_t> neutral_set_3_points_on_plane;
  vector<size_t> negative_set_exclusive;
  vector<size_t> negative_set_1p_on_plane;
  vector<size_t> negative_set_2p_on_plane;
  vector<size_t> triangles_intersected_by_plane;
};

int group_triangles(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles,
  Plane plane, Triangle_groups& triangle_groups); 
int group_triangles_mt(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles, 
  Plane plane, Triangle_groups& triangle_groups);