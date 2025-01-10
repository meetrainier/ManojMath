#include "pch.h"
#include <vector> 
#include "TriangleSoupApi.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(group_triangles,basic_test)
{
  // Example points and triangles
  vector<Point3d> vec_points = {
      {0, 0, 1}, {1, 0, 1}, {0, 1, 1},   // Triangle 1 (positive side)
      {0, 0, -1}, {-1, 0, -1}, {0, -1, -1}, // Triangle 2 (negative side)
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0},   // Triangle 3 (on plane)
      {0, 0, 1}, {0, 1, -1}, {0, -1, 0}  // Triangle 4 (intersects plane)
  };

  vector<array<size_t, 3>> vec_triangles = {
      {0, 1, 2},  // Triangle 1
      {3, 4, 5},  // Triangle 2
      {6, 7, 8},  // Triangle 3
      {9, 10, 11} // Triangle 4
  };

  Plane plane = { {0, 0, 0}, {0, 0, 1} }; // z = 0 plane

  Triangle_groups triangle_groups;

  int result = group_triangles(vec_points, vec_triangles, plane, triangle_groups);

  if (result == 0) {
    EXPECT_EQ(1, triangle_groups.positive_set_exclusive.size());
    EXPECT_EQ(0, triangle_groups.positive_set_exclusive[0]);

    EXPECT_EQ(1, triangle_groups.negative_set_exclusive.size());
    EXPECT_EQ(1, triangle_groups.negative_set_exclusive[0]);
    
    EXPECT_EQ(1, triangle_groups.neutral_set_3_points_on_plane.size());
    EXPECT_EQ(2, triangle_groups.neutral_set_3_points_on_plane[0]);

    EXPECT_EQ(1, triangle_groups.triangles_intersected_by_plane.size());
    EXPECT_EQ(3, triangle_groups.triangles_intersected_by_plane[0]);

    cout << "Triangles successfully grouped." << endl;
  }
  else {
    cout << "Error in grouping triangles." << endl;
  }

}


TEST(group_triangles_mt, basic_test)
{
  // Example points and triangles
  vector<Point3d> vec_points = {
      {0, 0, 1}, {1, 0, 1}, {0, 1, 1},   // Triangle 1 (positive side)
      {0, 0, -1}, {-1, 0, -1}, {0, -1, -1}, // Triangle 2 (negative side)
      {0, 0, 0}, {1, 0, 0}, {0, 1, 0},   // Triangle 3 (on plane)
      {0, 0, 1}, {0, 1, -1}, {0, -1, 0}  // Triangle 4 (intersects plane)
  };

  vector<array<size_t, 3>> vec_triangles = {
      {0, 1, 2},  // Triangle 1
      {3, 4, 5},  // Triangle 2
      {6, 7, 8},  // Triangle 3
      {9, 10, 11} // Triangle 4
  };

  Plane plane = { {0, 0, 0}, {0, 0, 1} }; // z = 0 plane

  Triangle_groups triangle_groups;

  int result = group_triangles_mt(vec_points, vec_triangles, plane, triangle_groups);

  if (result == 0) {
    EXPECT_EQ(1, triangle_groups.positive_set_exclusive.size());
    EXPECT_EQ(0, triangle_groups.positive_set_exclusive[0]);

    EXPECT_EQ(1, triangle_groups.negative_set_exclusive.size());
    EXPECT_EQ(1, triangle_groups.negative_set_exclusive[0]);

    EXPECT_EQ(1, triangle_groups.neutral_set_3_points_on_plane.size());
    EXPECT_EQ(2, triangle_groups.neutral_set_3_points_on_plane[0]);

    EXPECT_EQ(1, triangle_groups.triangles_intersected_by_plane.size());
    EXPECT_EQ(3, triangle_groups.triangles_intersected_by_plane[0]);

    cout << "Triangles successfully grouped." << endl;
  }
  else {
    cout << "Error in grouping triangles." << endl;
  }

}


