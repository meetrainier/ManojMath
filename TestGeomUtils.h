#pragma once
#include "MnjPoint.h"

class TestGeomUtils{
 public:
 
static int Test();

static int TestDistancePointInfiniteLine();
static int TestDistancePointLine();

//A wrapper of other test cases 

static void TestGetExactArcCenterUsingRadius(void);
static void TestGetExactArcCenterUsingRadius1(void);
static void TestGetExactArcCenterUsingRadius2(void);
static void TestGetExactArcCenterUsingRadius3(void);

static int TestLineLineIntersect(void);
static int TestLineLineIntersect1(void);
static int TestLineLineIntersect2(void);
static int TestLineLineIntersect3(void);
static int TestLineLineIntersect4(void);

static int TestProject();
static int TestProject1(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				double tol = .001);
static int TestProject2(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				double tol = .001);
static int TestProject3(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				double tol = .001);
static int TestProject4(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				double tol = .001);
};