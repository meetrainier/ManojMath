//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 

#include <cassert>
#include <iostream>
#include <cmath>

#include "MNJPoint.h" 
#include "GeomUtils.h"
#include "TestGeomUtils.h"

using namespace std;
#define _DEBUG
//Case: When the two input points are diametrically opposite 
//		and along x-axis. 
//

/*
template <class T>
int DistancePointInfiniteLine( MnjPoint<T> *p, MnjPoint<T> *LineStart, MnjPoint<T> *LineEnd, double &od )
 {
    double LineMag;
    double U;
    MnjPoint<T>  Intersection;
 
    GetDistance( *LineEnd, *LineStart, LineMag );
 
    U = ( ( ( p->x - LineStart->x ) * ( LineEnd->x - LineStart->x ) ) +
        ( ( p->y - LineStart->y ) * ( LineEnd->y - LineStart->y ) ) +
        ( ( p->z - LineStart->z ) * ( LineEnd->z - LineStart->z ) ) ) /
        ( LineMag * LineMag );
 
    Intersection.x = LineStart->x + U * ( LineEnd->x - LineStart->x );
    Intersection.y = LineStart->y + U * ( LineEnd->y - LineStart->y );
    Intersection.z = LineStart->z + U * ( LineEnd->z - LineStart->z );
 
    GetDistance<T>( *p, Intersection,od );
 
    return 0;
}
*/
//tbd: commnted just to compile
// void GeomUtils::TestGeomUtils::TestGetExactArcCenterUsingRadius3(){

	// //testing when bisector is parallel to Y;
	// double xc; double yc;
	// GeomUtils::GetExactArcCenterUsingRadius(-5,0,5,0,.01,.01,xc,yc);
	// cout << "\nExpected Center: 0,0 \n";
	// cout << "\nComputed Center(approx): " << xc <<", " << yc << endl;

// }

// //Case: When the two points are along x-axis. 
// //
// void GeomUtils::TestGeomUtils::TestGetExactArcCenterUsingRadius2(){

	// //testing when bisector is parallel to Y;
	// double xc; double yc;
	// GeomUtils::GetExactArcCenterUsingRadius(-5, 5, 5, 5, .01, .01, xc, yc);
	// cout << "\nExpected Center: 0,0 \n";
	// cout << "\nComputed Center(approx): " << xc <<", " << yc << endl;

// }

///////////////////////////////////////////////////////////////

//Case: when the two points are along y-axis. 
// void GeomUtils::TestGeomUtils::TestGetExactArcCenterUsingRadius1(){

	// double xc; double yc;
	// GeomUtils::GetExactArcCenterUsingRadius(-5,5,-5,-5,.01,.01,xc,yc);
	// cout << "\nExpected Center: 0,0 \n";
	// cout << "\nComputed Center(approx): " << xc <<", " << yc << endl;

// }
// ///////////////////////////////////////////////////////////////
// void GeomUtils::TestGeomUtils::TestGetExactArcCenterUsingRadius(){
	// TestGeomUtils::TestGetExactArcCenterUsingRadius1();
	// TestGeomUtils::TestGetExactArcCenterUsingRadius2();
	// TestGeomUtils::TestGetExactArcCenterUsingRadius3();
// }
///////////////////////////////////////////////////////////////
// int GeomUtils::TestGeomUtils::TestDistancePointInfiniteLine(){
	// //MnjPoint p(10,10,0);
	// MnjPoint<double> p(-5.0,1,0);
	// MnjPoint<double>  s(0.0,0,0);
	// MnjPoint<double>  e(10.0,0,0);
	// double d=-1;
    // GeomUtils::DistancePointInfiniteLine(p,s,e,d);
	
	// return 0;
// }
//////////////////////////////////////////////////////////////
int TestGeomUtils::TestDistancePointLine(){
	//MnjPoint p(10,10,0);
	MnjPoint<double>  p(-5,1,0);
	MnjPoint<double>  s(0,0,0);
	MnjPoint<double>  e(10,0,0);
	double d=-1;
	//DistancePointLine<double>(&p,&s,&e,d);
	GeomUtils::DistancePointLine(p,s,e,d);
	return 0;
}

int TestGeomUtils::TestLineLineIntersect1()
{
	cout << "In:Function:" << __FUNCTION__ <<endl;
	//test1 intersect x and y segment. the result should be origin. 
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(-10,0,0);
	MnjPoint<double> p3(0,10,0);	MnjPoint<double> p4(0,-10,0);

	MnjPoint<double> pa;    MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
    assert(0==pa.x);
    assert(0==pa.y);
    assert(0==pa.z);
#ifdef _DEBUG
	pa.Print();
	pb.Print();	
	cout<<"a=" <<a << endl;
	cout<<"b=" <<b << endl;
	cout<<"flag=" <<flag << endl;
#endif 
	return flag;
}

int TestGeomUtils::TestLineLineIntersect2()
{
	cout << "In:Function:" << __FUNCTION__ <<endl;
	//test2 intersect x-axis and parallel to y-axis segments. the result should (15,0,0). 
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(20,0,0);
	MnjPoint<double> p3(15,10,0);	MnjPoint<double> p4(15,-10,0);

	MnjPoint<double> pa;    MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
#ifdef _DEBUG
	pa.Print();
	pb.Print();
	cout<<"a=" <<a << endl;
	cout<<"b=" <<b << endl;
	cout<<"flag=" <<flag << endl;
#endif
	return flag;
}

////////////////////////////////////////////////////////////////////////
int TestGeomUtils::TestLineLineIntersect3()
{
	cout << "In:Function:" << __FUNCTION__ <<endl;
	//test3: The intersection is exactly at one end. the result should (10,0,0). 
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(20,0,0);
	MnjPoint<double> p3(10,10,0);	MnjPoint<double> p4(10,-10,0);

	MnjPoint<double> pa;    MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
#ifdef _DEBUG
	pa.Print();
	pb.Print();
	cout<<"a=" <<a << endl;
	cout<<"b=" <<b << endl;
	cout<<"flag=" <<flag << endl;
#endif
	return flag;
}

int TestGeomUtils::TestLineLineIntersect4()
{
	cout << "In:Function:" << __FUNCTION__ <<endl;
	//test4: Input parallel lines. It should return 0. That is error.  
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(20,0,0);
	MnjPoint<double> p3(10,10,0);	MnjPoint<double> p4(20,10,0);

	MnjPoint<double> pa; MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
#ifdef _DEBUG
	pa.Print();
	pb.Print();
	cout<<"a=" <<a << endl;
	cout<<"b=" <<b << endl;
	cout<<"flag=" <<flag << endl;
#endif
	return flag;
}

int TestGeomUtils::TestLineLineIntersect5()
{
	cout << "In:Function:" << __FUNCTION__ <<endl;
	//test5: No intersection case. It should return 0. That is error.  
	MnjPoint<double> p1(0,0,0);  MnjPoint<double> p2(5,5,5);
	MnjPoint<double> p3(0,50,0); MnjPoint<double> p4(0,50,0);

	MnjPoint<double> pa; MnjPoint<double> pb;
	double a=-999 ,b=-999;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
#ifdef _DEBUG
	pa.Print();
	pb.Print();
	cout<<"a=" <<a << endl;
	cout<<"b=" <<b << endl;
	cout<<"flag=" <<flag << endl;
#endif
	return flag;
}
////////////////////////////////////////////////////////////////
int TestGeomUtils::TestLineLineIntersect()
{
	int flag = -1;
	flag = TestLineLineIntersect1();
	flag = TestLineLineIntersect2();
	flag = TestLineLineIntersect3();
	//test4: Input parallel lines. It should return 0. 0 error flag.  
	flag = TestLineLineIntersect4();
	flag = TestLineLineIntersect5();
	return flag;
}
/////////////////////////////////////////////////////////////////////////////////
// int TestGeomUtils::TestProject4(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				// double tol ){
	 // MnjPoint<double> p=LineStart;
	 // MnjPoint<double> pProjection;
		  
     // return GeomUtils::Project<dbl_3d_pt>(LineStart, LineEnd, p,pProjection);
// }
// //////////////////////////////////////////////////////////////////////////////////////
// int TestGeomUtils::TestProject3(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				// double tol ){
	 // MnjPoint<double> p(5,5,0);
	 // MnjPoint<double> pProjection;
		  
     // return GeomUtils::Project<dbl_3d_pt>(LineStart, LineEnd, p,pProjection);
// }
// ////////////////////////////////////////////////////////////////////////////////////////
// int TestGeomUtils::TestProject2(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				// double tol ){
	 // MnjPoint<double> p(11,0,0);
	 // MnjPoint<double> pProjection;
		  
     // return GeomUtils::Project<dbl_3d_pt>(LineStart, LineEnd, p,pProjection);
// }
// ///////////////////////////////////////////////////////////////////////////////////
// int TestGeomUtils::TestProject1(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
					   // double tol ){
	 // MnjPoint<double> p(1,0,0);
	 // MnjPoint<double> pProjection;
		  
     // return GeomUtils::Project<MnjPoint<double>>(LineStart, LineEnd, p,pProjection);
// }
///////////////////////////////////////////////////////////////////////////////////
// int GeomUtils::TestGeomUtils::TestProject(){
	// const MnjPoint<double> LineStart(-10,0,0); 
	// const MnjPoint<double> LineEnd(10,0,0);
	
   // //case: Point is on line segment;
	// int	flag = TestProject1(LineStart,LineEnd);
	// assert(1==flag);
   // //error case: Point is on the line but beyond segement
	    // flag = TestProject2(LineStart,LineEnd);
		// assert(0==flag);
   
   // //test usual case
		// flag = TestProject3(LineStart,LineEnd);
        // assert(1==flag);
   // // test  at boundary
        // flag = TestProject4(LineStart,LineEnd);
		// assert(1==flag);
		// return flag;
// }

int TestGeomUtils::Test(){

//int error = TestDistancePointInfiniteLine();
//error = TestDistancePointLine();

//A wrapper of other test cases 

//TestGetExactArcCenterUsingRadius();
auto error = TestLineLineIntersect();
//error = TestProject();
return error;
}
/*
int main(){
    
	//TestDistancePointLine();
	//TestDistancePointInfiniteLine();
	//TestGetExactArcCenterUsingRadius();
	//TestLineLineIntersect();
	TestProject();
}
*/