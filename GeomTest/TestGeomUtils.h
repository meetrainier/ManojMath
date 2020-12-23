#pragma once
//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
#include "MnjPoint.h"

 class TestGeomUtils{
	public:

		static int Test();
                  /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect1(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect2(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect3(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect4(void);
		static int TestLineLineIntersect5(void);
                /*
                 Refer to the documentation of 
                 */
		static int TestDistancePointInfiniteLine();
		 /*
                 Refer to the documentation of DistancePointLine() 
                 */
		static int TestDistancePointLine();

		//A wrapper of other test cases 
                   /*
                 Refer to the documentation of GetExactArcCenterUsingRadius() 
                 */
		static void TestGetExactArcCenterUsingRadius(void);
		   /*
                 Refer to the documentation of 
                 */
		// static void TestGetExactArcCenterUsingRadius1(void);
		// static void TestGetExactArcCenterUsingRadius2(void);
		// static void TestGetExactArcCenterUsingRadius3(void);

               
		//static int TestProject();
/* 		static int TestProject1(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
		static int TestProject2(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
		static int TestProject3(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
		static int TestProject4(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
 */	};