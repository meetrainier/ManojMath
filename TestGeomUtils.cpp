#include <cassert>
#include <iostream>
#include <cmath>

#include "MNJPoint.h" 
#include "GeomUtils.h"
#include "TestGeomUtils.h"

using namespace std;

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
void TestGeomUtils::TestGetExactArcCenterUsingRadius3(){

	//testing when bisector is parallel to Y;
	double xc; double yc;
	GetExactArcCenterUsingRadius(-5,0,5,0,.01,.01,xc,yc);
	cout << "\nExpected Center: 0,0 \n";
	cout << "\nComputed Center(approx): " << xc <<", " << yc << endl;

}

//Case: When the two points are along x-axis. 
//
void TestGeomUtils::TestGetExactArcCenterUsingRadius2(){

	//testing when bisector is parallel to Y;
	double xc; double yc;
	GetExactArcCenterUsingRadius(-5,5,5,5,.01,.01,xc,yc);
	cout << "\nExpected Center: 0,0 \n";
	cout << "\nComputed Center(approx): " << xc <<", " << yc << endl;

}

///////////////////////////////////////////////////////////////

//Case: when the two points are along y-axis. 
void TestGeomUtils::TestGetExactArcCenterUsingRadius1(){

	 double xc; double yc;
	GetExactArcCenterUsingRadius(-5,5,-5,-5,.01,.01,xc,yc);
	cout << "\nExpected Center: 0,0 \n";
	cout << "\nComputed Center(approx): " << xc <<", " << yc << endl;

}
///////////////////////////////////////////////////////////////
void TestGeomUtils::TestGetExactArcCenterUsingRadius(){
	TestGetExactArcCenterUsingRadius1();
	TestGetExactArcCenterUsingRadius2();
	TestGetExactArcCenterUsingRadius3();
}
///////////////////////////////////////////////////////////////
int TestGeomUtils::TestDistancePointInfiniteLine(){
	//MnjPoint p(10,10,0);
	MnjPoint<double> p(-5.0,1,0);
	MnjPoint<double>  s(0.0,0,0);
	MnjPoint<double>  e(10.0,0,0);
	double d=-1;
    GeomUtils::DistancePointInfiniteLine(p,s,e,d);
	
	return 0;
}
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
	//test1 intersect x and y segment. the result should be origin. 
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(-10,0,0);
	MnjPoint<double> p3(0,10,0);	MnjPoint<double> p4(0,-10,0);


	MnjPoint<double> pa;    MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
	pa.Print();
	pb.Print();
	return flag;
}
int TestGeomUtils::TestLineLineIntersect2()
{

	//test2 intersect x-axis and parallel to y-axis segments. the result should (15,0,0). 
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(20,0,0);
	MnjPoint<double> p3(15,10,0);	MnjPoint<double> p4(15,-10,0);

	MnjPoint<double> pa;    MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
	pa.Print();
	pb.Print();
	return flag;
}
////////////////////////////////////////////////////////////////////////
int TestGeomUtils::TestLineLineIntersect3()
{

	//test3: The intersection is exactly at one end. the result should (10,0,0). 
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(20,0,0);
	MnjPoint<double> p3(10,10,0);	MnjPoint<double> p4(10,-10,0);

	MnjPoint<double> pa;    MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
	pa.Print();
	pb.Print();
	return flag;
}
int TestGeomUtils::TestLineLineIntersect4()
{
	//test4: Input parallel lines. It should return 0. That is error.  
	MnjPoint<double> p1(10,0,0);    MnjPoint<double> p2(20,0,0);
	MnjPoint<double> p3(10,10,0);	MnjPoint<double> p4(10,10,0);

	MnjPoint<double> pa;    MnjPoint<double> pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b);
	pa.Print();
	pb.Print();
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
	return flag;
}
///////////////////////////////////////////////////////////////////////////////////
int TestGeomUtils::TestProject4(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				double tol ){
	 MnjPoint<double> p=LineStart;
	 MnjPoint<double> pProjection;
		  
     return GeomUtils::Project(LineStart, LineEnd, p,pProjection);
}
//////////////////////////////////////////////////////////////////////////////////////
int TestGeomUtils::TestProject3(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				double tol ){
	 MnjPoint<double> p(5,5,0);
	 MnjPoint<double> pProjection;
		  
     return GeomUtils::Project(LineStart, LineEnd, p,pProjection);
}
////////////////////////////////////////////////////////////////////////////////////////
int TestGeomUtils::TestProject2(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
				double tol ){
	 MnjPoint<double> p(11,0,0);
	 MnjPoint<double> pProjection;
		  
     return GeomUtils::Project(LineStart, LineEnd, p,pProjection);
}
///////////////////////////////////////////////////////////////////////////////////
int TestGeomUtils::TestProject1(const MnjPoint<double> LineStart, const MnjPoint<double> LineEnd,
					   double tol ){
	 MnjPoint<double> p(1,0,0);
	 MnjPoint<double> pProjection;
		  
     return GeomUtils::Project(LineStart, LineEnd, p,pProjection);
}
///////////////////////////////////////////////////////////////////////////////////
int TestGeomUtils::TestProject(){
	const MnjPoint<double> LineStart(-10,0,0); 
	const MnjPoint<double> LineEnd(10,0,0);
	
   //case: Point is on line segment;
	int	flag = TestProject1(LineStart,LineEnd);
	assert(1==flag);
   //error case: Point is on the line but beyond segement
	    flag = TestProject2(LineStart,LineEnd);
		assert(0==flag);
   
   //test usual case
		flag = TestProject3(LineStart,LineEnd);
        assert(1==flag);
   // test  at boundary
        flag = TestProject4(LineStart,LineEnd);
		assert(1==flag);
		return flag;
}
int TestGeomUtils::Test(){

int error = TestDistancePointInfiniteLine();
error = TestDistancePointLine();

//A wrapper of other test cases 

TestGetExactArcCenterUsingRadius();
error = TestLineLineIntersect();
error = TestProject();
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