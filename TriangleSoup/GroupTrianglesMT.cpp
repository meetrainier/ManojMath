#include "pch.h"
#include <iostream>
#include <vector>
#include <array>
#include <thread>
#include <mutex>

#include "TriangleSoupApi.h"

using namespace std;

// Mutex to handle thread-safe operations
std::mutex group_mutex;

// Helper function to compute the signed distance from a point to the plane
extern double signed_distance_to_plane(const Point3d& point, const Plane& plane);

// Function that processes a subset of triangles and adds them to the appropriate group
void process_triangles_chunk(
  vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles,
  Plane plane, Triangle_groups& triangle_groups, size_t start, size_t end)
{
  const double EPSILON = 1e-9;  // Tolerance for floating-point comparison
  Triangle_groups local_groups;

  for (size_t i = start; i < end; ++i) {
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
      local_groups.positive_set_exclusive.push_back(i);
    }
    else if (negative == 3) {
      local_groups.negative_set_exclusive.push_back(i);
    }
    else if (on_plane == 3) {
      local_groups.neutral_set_3_points_on_plane.push_back(i);
    }
    else if (positive == 2 && on_plane == 1) {
      local_groups.positive_set_1p_on_plane.push_back(i);
    }
    else if (positive == 1 && on_plane == 2) {
      local_groups.positive_set_2p_on_plane.push_back(i);
    }
    else if (negative == 2 && on_plane == 1) {
      local_groups.negative_set_1p_on_plane.push_back(i);
    }
    else if (negative == 1 && on_plane == 2) {
      local_groups.negative_set_2p_on_plane.push_back(i);
    }
    else if (positive > 0 && negative > 0) {
      local_groups.triangles_intersected_by_plane.push_back(i);
    }
  }

  // Merge local results into global result
  std::lock_guard<std::mutex> guard(group_mutex);  // Lock the mutex to ensure thread safety
  triangle_groups.positive_set_exclusive.insert(
    triangle_groups.positive_set_exclusive.end(),
    local_groups.positive_set_exclusive.begin(),
    local_groups.positive_set_exclusive.end());

  triangle_groups.positive_set_1p_on_plane.insert(
    triangle_groups.positive_set_1p_on_plane.end(),
    local_groups.positive_set_1p_on_plane.begin(),
    local_groups.positive_set_1p_on_plane.end());

  triangle_groups.positive_set_2p_on_plane.insert(
    triangle_groups.positive_set_2p_on_plane.end(),
    local_groups.positive_set_2p_on_plane.begin(),
    local_groups.positive_set_2p_on_plane.end());

  triangle_groups.neutral_set_3_points_on_plane.insert(
    triangle_groups.neutral_set_3_points_on_plane.end(),
    local_groups.neutral_set_3_points_on_plane.begin(),
    local_groups.neutral_set_3_points_on_plane.end());

  triangle_groups.negative_set_exclusive.insert(
    triangle_groups.negative_set_exclusive.end(),
    local_groups.negative_set_exclusive.begin(),
    local_groups.negative_set_exclusive.end());

  triangle_groups.negative_set_1p_on_plane.insert(
    triangle_groups.negative_set_1p_on_plane.end(),
    local_groups.negative_set_1p_on_plane.begin(),
    local_groups.negative_set_1p_on_plane.end());

  triangle_groups.negative_set_2p_on_plane.insert(
    triangle_groups.negative_set_2p_on_plane.end(),
    local_groups.negative_set_2p_on_plane.begin(),
    local_groups.negative_set_2p_on_plane.end());

  triangle_groups.triangles_intersected_by_plane.insert(
    triangle_groups.triangles_intersected_by_plane.end(),
    local_groups.triangles_intersected_by_plane.begin(),
    local_groups.triangles_intersected_by_plane.end());
}

// Multithreaded function to group triangles
int group_triangles_mt(vector<Point3d>& vec_points, vector<array<size_t, 3>>& vec_triangles, Plane plane, Triangle_groups& triangle_groups) {
  size_t num_threads = thread::hardware_concurrency();
  size_t num_triangles = vec_triangles.size();
  size_t chunk_size = num_triangles / num_threads;

  vector<thread> threads;

  // Launch threads
  for (size_t t = 0; t < num_threads; ++t) {
    size_t start = t * chunk_size;
    size_t end = (t == num_threads - 1) ? num_triangles : (t + 1) * chunk_size;

    threads.emplace_back(process_triangles_chunk, ref(vec_points), ref(vec_triangles), plane, ref(triangle_groups), start, end);
  }

  // Join threads
  for (auto& th : threads) {
    th.join();
  }

  return 0;  // Success
}

// Example usage
//int main() {
//  // Example points and triangles
//  vector<Point3d> vec_points = {
//      {0, 0, 1}, {1, 0, 1}, {0, 1, 1},   // Triangle 1 (positive side)
//      {0, 0, -1}, {-1, 0, -1}, {0, -1, -1}, // Triangle 2 (negative side)
//      {0, 0, 0}, {1, 0, 0}, {0, 1, 0},   // Triangle 3 (on plane)
//      {0, 0, 1}, {0, 1, -1}, {0, -1, 0}  // Triangle 4 (intersects plane)
//  };
//
//  vector<array<size_t, 3>> vec_triangles = {
//      {0, 1, 2},  // Triangle 1
//      {3, 4, 5},  // Triangle 2
//      {6, 7, 8},  // Triangle 3
//      {9, 10, 11} // Triangle 4
//  };
//
//  Plane plane = { {0, 0, 0}, {0, 0, 1} }; // z = 0 plane
//
//  Triangle_groups triangle_groups;
//
//  int result = group_triangles(vec_points, vec_triangles, plane, triangle_groups);
//
//  if (result == 0) {
//    cout << "Triangles successfully grouped in a multithreaded manner." << endl;
//  }
//  else {
//    cout << "Error in grouping triangles." << endl;
//  }
//
//  return 0;
//}
