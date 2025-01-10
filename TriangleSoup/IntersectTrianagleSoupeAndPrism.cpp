#include "pch.h"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#include "TriangleSoupApi.h"

using namespace std;

//Implementation 1 
/*
// Helper function to check if a point is inside a polygon using ray-casting
bool point_in_polygon(const Point3d& point, const Polygon& polygon) {
  int crossings = 0;
  size_t n = polygon.vec_points.size();
  for (size_t i = 0; i < n; ++i) {
    const Point3d& p1 = polygon.vec_points[i];
    const Point3d& p2 = polygon.vec_points[(i + 1) % n];
    // Check if the ray from the point crosses the edge of the polygon
    if (((p1.y > point.y) != (p2.y > point.y)) &&
      (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)) {
      crossings++;
    }
  }
  // If the number of crossings is odd, the point is inside the polygon
  return (crossings % 2 == 1);
}

// Function to check if a point is on the vertical surface of the prism
bool point_on_prism_surface(const Point3d& point, const Prism& prism) {
  // Check if the point is on the base polygon or on the top face
  return point_in_polygon(point, prism.base_polygon) &&
    (point.z == 0 || fabs(point.z - prism.height) < 1e-9);
}

// Function to check if all points of the triangle lie within the prism
bool triangle_in_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
  for (size_t i = 0; i < 3; ++i) {
    const Point3d& p = vec_points[triangle[i]];
    if (!point_in_polygon(p, prism.base_polygon) || p.z < 0 || p.z > prism.height) {
      return false;
    }
  }
  return true;
}

// Function to check if a triangle is on the prism surface
bool triangle_on_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
  for (size_t i = 0; i < 3; ++i) {
    const Point3d& p = vec_points[triangle[i]];
    if (!point_on_prism_surface(p, prism)) {
      return false;
    }
  }
  return true;
}

// Function to check if a triangle intersects the prism
bool triangle_intersects_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
  bool has_inside = false, has_outside = false;
  for (size_t i = 0; i < 3; ++i) {
    const Point3d& p = vec_points[triangle[i]];
    if (point_in_polygon(p, prism.base_polygon) && p.z >= 0 && p.z <= prism.height) {
      has_inside = true;
    }
    else {
      has_outside = true;
    }
    if (has_inside && has_outside) {
      return true;
    }
  }
  return false;
}

// Main function to group triangles
int group_triangles_with_respect_to_prism(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles, Prism& prism, Prism_Triangle_Groups& triangle_groups) {
  for (size_t i = 0; i < vec_triangles.size(); ++i) {
    const array<size_t, 3>& triangle = vec_triangles[i];

    if (triangle_in_prism(triangle, vec_points, prism)) {
      triangle_groups.in_prism.push_back(i);
    }
    else if (triangle_on_prism(triangle, vec_points, prism)) {
      triangle_groups.on_prism.push_back(i);
    }
    else if (triangle_intersects_prism(triangle, vec_points, prism)) {
      triangle_groups.intersecting_prism.push_back(i);
    }
  }

  return 0;  // Success
}
*/
//Implementation2


// Helper function to check if a point is inside a polygon using ray-casting
bool point_in_polygon(const Point3d& point, const Polygon& polygon) {
  int crossings = 0;
  size_t n = polygon.vec_points.size();
  for (size_t i = 0; i < n; ++i) {
    const Point3d& p1 = polygon.vec_points[i];
    const Point3d& p2 = polygon.vec_points[(i + 1) % n];
    // Check if the ray from the point crosses the edge of the polygon
    if (((p1.y > point.y) != (p2.y > point.y)) &&
      (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)) {
      crossings++;
    }
  }
  // If the number of crossings is odd, the point is inside the polygon
  return (crossings % 2 == 1);
}

// Function to check if a point is on the base or top surface of the prism
bool point_on_base_or_top(const Point3d& point, const Prism& prism) {
  return point_in_polygon(point, prism.base_polygon) &&
    (point.z == 0 || fabs(point.z - prism.height) < 1e-9);
}

// Function to check if a point is inside the prism (not on the surface)
bool point_inside_prism(const Point3d& point, const Prism& prism) {
  return point_in_polygon(point, prism.base_polygon) && point.z >= 0 && point.z <= prism.height;
}

// Function to check if a triangle lies fully on the same prism face (base, top, or a vertical wall)
bool triangle_on_same_prism_face(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
  bool on_base = true, on_top = true, on_vertical = true;

  for (size_t i = 0; i < 3; ++i) {
    const Point3d& p = vec_points[triangle[i]];

    // Check if points are all on the base or all on the top
    if (!(point_in_polygon(p, prism.base_polygon) && p.z == 0)) {
      on_base = false;
    }
    if (!(point_in_polygon(p, prism.base_polygon) && fabs(p.z - prism.height) < 1e-9)) {
      on_top = false;
    }
    // Points are on the vertical surface if they're in the polygon and their z is between 0 and height
    if (!(point_on_polygon(p, prism.base_polygon) && p.z > 0 && p.z < prism.height)) {
      on_vertical = false;
    }
  }

  // The triangle must have all three points on the same face
  return (on_base || on_top || on_vertical);
}

// Function to check if a triangle is fully inside the prism (including surface points)
bool triangle_in_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
  for (size_t i = 0; i < 3; ++i) {
    const Point3d& p = vec_points[triangle[i]];
    if (!point_inside_prism(p, prism)) {
      return false;
    }
  }
  return true;
}

// Function to check if a triangle intersects the prism (part inside, part outside)
bool triangle_intersects_prism(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
  bool has_inside = false, has_outside = false;
  for (size_t i = 0; i < 3; ++i) {
    const Point3d& p = vec_points[triangle[i]];
    if (point_inside_prism(p, prism)) {
      has_inside = true;
    }
    else {
      has_outside = true;
    }
    if (has_inside && has_outside) {
      return true;
    }
  }
  return false;
}

// Main function to group triangles (mutually exclusive groups)
int group_triangles_with_respect_to_prism(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles, Prism& prism, Prism_Triangle_Groups& triangle_groups) {
  for (size_t i = 0; i < vec_triangles.size(); ++i) {
    const array<size_t, 3>& triangle = vec_triangles[i];

    // Check if the triangle is on the same face of the prism (base, top, or vertical)
    if (triangle_on_same_prism_face(triangle, vec_points, prism)) {
      triangle_groups.on_prism.push_back(i);  // On the prism surface
    }
    // Check if all points are inside the prism (can include points on the surface)
    else if (triangle_in_prism(triangle, vec_points, prism)) {
      triangle_groups.in_prism.push_back(i);  // Fully inside
    }
    // If some points are inside and some are outside, the triangle intersects the prism
    else if (triangle_intersects_prism(triangle, vec_points, prism)) {
      triangle_groups.intersecting_prism.push_back(i);  // Intersects
    }
  }

  return 0;  // Success
}

