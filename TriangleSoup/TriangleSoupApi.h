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


struct Polygon {
  vector<Point3d> vec_points;  // Only the x and y coordinates are relevant for the polygon
};

struct Prism {
  Polygon base_polygon;        // The base polygon of the prism in the XY-plane
  double height;               // The height of the prism along the z-axis
};

struct Prism_Triangle_Groups {
  vector<size_t> in_prism;
  vector<size_t> on_prism;
  vector<size_t> intersecting_prism;
};

//Note that the current implenmentation is grouping a triangle that is inside but one of the vertices on the boundary of the prism as intersectiong. 
//For details, refer to the implemenation.
int group_triangles_with_respect_to_prism(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles,
  Prism& prism, Prism_Triangle_Groups& triangle_groups);

bool point_on_polygon(const Point3d& point, const Polygon& polygon);