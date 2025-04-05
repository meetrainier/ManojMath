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
bool point_in_polygon1(const Point3d& point, const Polygon& polygon) {
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
  return point_in_polygon1(point, prism.base_polygon) &&
    (point.z == 0 || fabs(point.z - prism.height) < 1e-9);
}

// Function to check if a point is inside the prism (not on the surface)
bool point_inside_prism(const Point3d& point, const Prism& prism) {
  return point_in_polygon1(point, prism.base_polygon) && point.z >= 0 && point.z <= prism.height;
}

// Function to check if a triangle lies fully on the same prism face (base, top, or a vertical wall)
bool triangle_on_same_prism_face(const array<size_t, 3>& triangle, const vector<Point3d>& vec_points, const Prism& prism) {
  bool on_base = true, on_top = true, on_vertical = true;

  for (size_t i = 0; i < 3; ++i) {
    const Point3d& p = vec_points[triangle[i]];

    // Check if points are all on the base or all on the top
    if (!(point_in_polygon1(p, prism.base_polygon) && p.z == 0)) {
      on_base = false;
    }
    if (!(point_in_polygon1(p, prism.base_polygon) && fabs(p.z - prism.height) < 1e-9)) {
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

/*
// Helper function to determine if a point is inside the polygon (base of the prism)
//bool point_in_polygon(const Point3d& point, const Polygon& polygon) {
//  int crossings = 0;
//  size_t n = polygon.vec_points.size();
//  for (size_t i = 0; i < n; ++i) {
//    const Point3d& p1 = polygon.vec_points[i];
//    const Point3d& p2 = polygon.vec_points[(i + 1) % n];
//    if (((p1.y > point.y) != (p2.y > point.y)) &&
//      (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)) {
//      crossings++;
//    }
//  }
//  return (crossings % 2 == 1);
//}

// Function to compute the intersection of a line segment with a horizontal plane (z = constant)
bool intersect_with_horizontal_plane(const Point3d& p1, const Point3d& p2, double z_plane, Point3d& intersection) {
  if ((p1.z < z_plane && p2.z > z_plane) || (p1.z > z_plane && p2.z < z_plane)) {
    double t = (z_plane - p1.z) / (p2.z - p1.z);
    intersection.x = p1.x + t * (p2.x - p1.x);
    intersection.y = p1.y + t * (p2.y - p1.y);
    intersection.z = z_plane;
    return true;
  }
  return false;
}

// Function to compute the intersection of a line segment with a vertical face of the prism
bool intersect_with_vertical_face(const Point3d& p1, const Point3d& p2, const Point3d& a, const Point3d& b, Point3d& intersection) {
  // The vertical face is the line segment from a to b, extending between z = 0 and z = height
  double t_numerator = (b.x - a.x) * (p1.y - a.y) - (b.y - a.y) * (p1.x - a.x);
  double t_denominator = (b.x - a.x) * (p2.y - p1.y) - (b.y - a.y) * (p2.x - p1.x);

  if (fabs(t_denominator) < 1e-9) return false;  // Lines are parallel

  double t = t_numerator / t_denominator;
  if (t >= 0 && t <= 1) {
    intersection.x = p1.x + t * (p2.x - p1.x);
    intersection.y = p1.y + t * (p2.y - p1.y);
    double s = ((intersection.x - a.x) * (b.x - a.x) + (intersection.y - a.y) * (b.y - a.y)) /
      ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    return (s >= 0 && s <= 1);  // Intersection is between points a and b
  }
  return false;
}

// Function to split a triangle with a prism and return the resulting polygons inside the prism
int split_triangle_with_prism(const Triangle& triangle, const Prism& prism, vector<Polygon>& vec_polygons) {
  vector<Point3d> inside_points, intersection_points;

  // Check each triangle vertex if it is inside the prism
  for (const auto& vertex : triangle.vertices) {
    if (point_in_polygon(vertex, prism.base_polygon) && vertex.z >= 0 && vertex.z <= prism.height) {
      inside_points.push_back(vertex);
    }
  }

  // Check each edge of the triangle for intersections with the top and bottom planes of the prism
  for (size_t i = 0; i < 3; ++i) {
    Point3d p1 = triangle.vertices[i];
    Point3d p2 = triangle.vertices[(i + 1) % 3];

    // Intersect with horizontal planes (base at z = 0 and top at z = prism.height)
    Point3d intersection;
    if (intersect_with_horizontal_plane(p1, p2, 0, intersection)) {
      intersection_points.push_back(intersection);
    }
    if (intersect_with_horizontal_plane(p1, p2, prism.height, intersection)) {
      intersection_points.push_back(intersection);
    }

    // Check intersections with each vertical face of the prism
    size_t n = prism.base_polygon.vec_points.size();
    for (size_t j = 0; j < n; ++j) {
      Point3d a = prism.base_polygon.vec_points[j];
      Point3d b = prism.base_polygon.vec_points[(j + 1) % n];
      if (intersect_with_vertical_face(p1, p2, a, b, intersection)) {
        intersection_points.push_back(intersection);
      }
    }
  }

  // Combine inside points and intersection points to form new polygons
  if (!inside_points.empty() || !intersection_points.empty()) {
    Polygon new_polygon;
    new_polygon.vec_points = inside_points;
    new_polygon.vec_points.insert(new_polygon.vec_points.end(), intersection_points.begin(), intersection_points.end());
    vec_polygons.push_back(new_polygon);
  }

  return 0;  // Success
}
*/


//Implementation 3
/*
// Helper function to compute intersection of a segment with a horizontal plane (z = constant)
bool intersect_with_horizontal_plane(const Point3d& p1, const Point3d& p2, double z_plane, Point3d& intersection) {
  if ((p1.z < z_plane && p2.z > z_plane) || (p1.z > z_plane && p2.z < z_plane)) {
    double t = (z_plane - p1.z) / (p2.z - p1.z);
    intersection.x = p1.x + t * (p2.x - p1.x);
    intersection.y = p1.y + t * (p2.y - p1.y);
    intersection.z = z_plane;
    return true;
  }
  return false;
}

// Sutherland-Hodgman Polygon Clipping Algorithm to clip polygon against a line
vector<Point3d> sutherland_hodgman_clip(const vector<Point3d>& polygon, const Point3d& p1, const Point3d& p2) {
  vector<Point3d> output_list = polygon;
  vector<Point3d> input_list;

  // Define the edge's direction vector
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;

  // Loop through each edge of the polygon
  for (size_t i = 0; i < polygon.size(); ++i) {
    input_list = output_list;
    output_list.clear();

    Point3d S = input_list.back(); // Start point is the last vertex of the polygon

    for (const auto& E : input_list) { // Loop over each point in the input polygon
      // Determine the position of S relative to the clipping line
      double S_position = (E.x - p1.x) * dy - (E.y - p1.y) * dx;
      double E_position = (S.x - p1.x) * dy - (S.y - p1.y) * dx;

      // If S is inside the clip edge, add it to the output
      if (E_position >= 0) {
        if (S_position < 0) { // Line crossing from outside to inside
          // Compute intersection point with the edge
          double t = E_position / (E_position - S_position);
          Point3d intersection = {
              E.x + t * (S.x - E.x),
              E.y + t * (S.y - E.y),
              S.z  // Keep z as S for now (2D clipping)
          };
          output_list.push_back(intersection);
        }
        output_list.push_back(E); // Add current point E
      }
      else if (S_position >= 0) {
        // Compute intersection point
        double t = E_position / (E_position - S_position);
        Point3d intersection = {
            E.x + t * (S.x - E.x),
            E.y + t * (S.y - E.y),
            S.z
        };
        output_list.push_back(intersection);
      }

      S = E;
    }
  }

  return output_list;
}

// Clip triangle against the vertical faces and horizontal planes of the prism
int split_triangle_with_prism(const Triangle& triangle, const Prism& prism, vector<Polygon>& vec_polygons) {
  vector<Point3d> inside_points, intersection_points;

  // Step 1: Clip against horizontal planes (z = 0 and z = height)
  vector<Point3d> clipped_polygon;
  clipped_polygon.assign(triangle.vertices.begin(), triangle.vertices.end());

  vector<Point3d> result_polygon;

  for (const auto& vertex : clipped_polygon) {
    if (vertex.z >= 0 && vertex.z <= prism.height) {
      result_polygon.push_back(vertex);
    }
  }

  for (size_t i = 0; i < clipped_polygon.size(); ++i) {
    Point3d p1 = clipped_polygon[i];
    Point3d p2 = clipped_polygon[(i + 1) % clipped_polygon.size()];

    // Intersect with z = 0 plane
    Point3d intersection;
    if (intersect_with_horizontal_plane(p1, p2, 0, intersection)) {
      result_polygon.push_back(intersection);
    }

    // Intersect with z = height plane
    if (intersect_with_horizontal_plane(p1, p2, prism.height, intersection)) {
      result_polygon.push_back(intersection);
    }
  }

  // Step 2: Clip the resulting polygon against the sides of the prism using Sutherland-Hodgman algorithm
  size_t n = prism.base_polygon.vec_points.size();
  for (size_t i = 0; i < n; ++i) {
    Point3d a = prism.base_polygon.vec_points[i];
    Point3d b = prism.base_polygon.vec_points[(i + 1) % n];
    result_polygon = sutherland_hodgman_clip(result_polygon, a, b);
  }

  // Store result polygon
  if (!result_polygon.empty()) {
    Polygon new_polygon;
    new_polygon.vec_points = result_polygon;
    vec_polygons.push_back(new_polygon);
  }

  return 0;  // Success
}
*/

//Implementation 4
// Sutherland-Hodgman Polygon Clipping Algorithm to clip polygon against a line
void sutherland_hodgman_clip(const vector<Point3d>& polygon, const Point3d& p1, const Point3d& p2, vector<Point3d>& output_list) {
  output_list.clear();  // Clear the output list before clipping starts
  vector<Point3d> input_list = polygon;

  // Define the edge's direction vector
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;

  if (input_list.empty()) {
    return;  // If the polygon is empty, no need to clip
  }

  // Loop through each edge of the polygon
  Point3d S = input_list.back();  // Start point is the last vertex of the polygon

  for (const auto& E : input_list) {  // Loop over each point in the input polygon
    // Determine the position of E and S relative to the clipping line
    double E_position = (E.x - p1.x) * dy - (E.y - p1.y) * dx;
    double S_position = (S.x - p1.x) * dy - (S.y - p1.y) * dx;

    if (E_position >= 0) {
      if (S_position < 0) {  // Line crosses from outside to inside
        // Compute intersection point with the edge
        double t = E_position / (E_position - S_position);
        Point3d intersection = {
            E.x + t * (S.x - E.x),
            E.y + t * (S.y - E.y),
            S.z  // Keep z as S for now (2D clipping)
        };
        output_list.push_back(intersection);
      }
      // Add current point E to the output if it's inside
      output_list.push_back(E);
    }
    else if (S_position >= 0) {  // Line crosses from inside to outside
      // Compute intersection point
      double t = E_position / (E_position - S_position);
      Point3d intersection = {
          E.x + t * (S.x - E.x),
          E.y + t * (S.y - E.y),
          S.z
      };
      output_list.push_back(intersection);
    }

    S = E;  // Update S for next iteration
  }
}

// Function to compute intersection of a segment with a horizontal plane (z = constant)
bool intersect_with_horizontal_plane(const Point3d& p1, const Point3d& p2, double z_plane, Point3d& intersection) {
  if ((p1.z < z_plane && p2.z > z_plane) || (p1.z > z_plane && p2.z < z_plane)) {
    double t = (z_plane - p1.z) / (p2.z - p1.z);
    intersection.x = p1.x + t * (p2.x - p1.x);
    intersection.y = p1.y + t * (p2.y - p1.y);
    intersection.z = z_plane;
    return true;
  }
  return false;
}

// Function to clip triangle against the horizontal planes (z = 0 and z = height)
void clip_against_horizontal_planes(const vector<Point3d>& triangle, double height, vector<Point3d>& result_polygon) {
  result_polygon.clear();

  for (size_t i = 0; i < triangle.size(); ++i) {
    const Point3d& p1 = triangle[i];
    const Point3d& p2 = triangle[(i + 1) % triangle.size()];

    // Keep points inside the horizontal bounds
    if (p1.z >= 0 && p1.z <= height) {
      result_polygon.push_back(p1);
    }

    // Check for intersection with horizontal planes at z = 0 and z = height
    Point3d intersection;
    if (intersect_with_horizontal_plane(p1, p2, 0, intersection)) {
      result_polygon.push_back(intersection);
    }
    if (intersect_with_horizontal_plane(p1, p2, height, intersection)) {
      result_polygon.push_back(intersection);
    }
  }
}

// Clip triangle against the vertical faces and horizontal planes of the prism
//int split_triangle_with_prism(const vect& triangle, const Polygon& base_polygon, double height, vector<Polygon>& vec_polygons) {
int split_triangle_with_prism(const Triangle& triangle, const Prism& prism, vector<Polygon>& vec_polygons)
{
  if (triangle.vertices.empty()) return -1;  // Invalid input

  vector<Point3d> result_polygon;

  // Step 1: Clip the triangle against the horizontal planes (z = 0 and z = height)
  clip_against_horizontal_planes({triangle.vertices.begin(), triangle.vertices.end()}, prism.height, result_polygon);

  // If the polygon has no valid points after clipping, return
  if (result_polygon.empty()) return 0;

  // Step 2: Clip the resulting polygon against the sides of the prism using Sutherland-Hodgman algorithm
  size_t n = prism.base_polygon.vec_points.size();
  vector<Point3d> temp_result;
  for (size_t i = 0; i < n; ++i) {
    Point3d a = prism.base_polygon.vec_points[i];
    Point3d b = prism.base_polygon.vec_points[(i + 1) % n];

    sutherland_hodgman_clip(result_polygon, a, b, temp_result);  // Clip against each vertical face
    result_polygon = temp_result;  // Update result_polygon with the clipped version

    if (result_polygon.empty()) return 0;  // If no points are left, return
  }

  // Store result polygon if it contains valid points
  if (!result_polygon.empty()) {
    Polygon new_polygon;
    new_polygon.vec_points = result_polygon;
    vec_polygons.push_back(new_polygon);
  }

  return 0;  // Success
}






//#include <gtest/gtest.h>
//#include <vector>
//
//using namespace std;
//
//TEST(PrismTriangleIntersection, LargeTriangleAroundConcavePrism) {
//  // A large triangle that intersects the concave prism
//  vector<Point3d> triangle = { {{-10, -10, 1.5}, {10, -10, 1.5}, {0, 10, 1.5}} };
//
//  // Define a concave base polygon (U-shape)
//  Polygon concave_polygon = { {{0, 0, 0}, {3, 0, 0}, {3, 1, 0}, {1, 1, 0}, {1, 3, 0}, {0, 3, 0}} };
//
//  double prism_height = 3.0;
//  vector<Polygon> result;
//
//  int status = split_triangle_with_prism(triangle, concave_polygon, prism_height, result);
//
//  EXPECT_EQ(status, 0);
//  EXPECT_EQ(result.size(), 1);  // Should generate one polygon
//
//  // The resulting polygon should match the shape of the concave cross-section of the prism
//  EXPECT_EQ(result[0].vec_points.size(), concave_polygon.vec_points.size());  // Same number of vertices as base polygon
//}
//
//int main(int argc, char** argv) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}




