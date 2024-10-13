#include "pch.h"
#include <vector> 
#include <limits>
#include "TriangleSoupApi.h"

TEST(point_on_polygon_test,basic_test)
{
  // Define a polygon (square in this case)
  Polygon polygon = { {{0, 0, 0}, {4, 0, 0}, {4, 4, 0}, {0, 4, 0}} };

  // Define some points to test
  Point3d point1 = { 2, 0, 0 };  // On the bottom edge
  Point3d point2 = { 4, 2, 0 };  // On the right edge
  Point3d point3 = { 2, 2, 0 };  // Inside the polygon
  Point3d point4 = { 5, 0, 0 };  // Outside the polygon

  // Test points
  EXPECT_TRUE(point_on_polygon(point1, polygon));  
  EXPECT_TRUE(point_on_polygon(point2, polygon));  
  EXPECT_FALSE(point_on_polygon(point3, polygon));  
  EXPECT_FALSE(point_on_polygon(point4, polygon));  
 
  //out
  //cout << "Point 1 on polygon: " << point_in_polygon(point1, polygon) << endl; 
  //cout << "Point 2 on polygon: " << point_in_polygon(point2, polygon) << endl; 
  //cout << "Point 3 on polygon: " << point_in_polygon(point3, polygon) << endl; 
  //cout << "Point 4 on polygon: " << point_in_polygon(point4, polygon) << endl; 

}
