//copyright(c) 2009- 2016 Manoj Lnu 
#include "MnjLine.h"
#include "MnjInfiniteLine.h"
#include "MnjPoint.h"
#include "GeomUtils.h"
#include "MnjDirection.h"

#include <cmath> 

#include <iostream> 

using namespace std;

 MnjInfiniteLine::MnjInfiniteLine(const MnjPoint<double> &ip,MnjDirection &iDir){
	   mPoint = ip;
	   mDir = iDir;
}
 //////////////////////////////////////////////////////////////////////////////
 void MnjInfiniteLine::Set(const MnjPoint<double> &ip,MnjDirection &iDir){
	   mPoint = ip;
	   mDir = iDir;
}
/////////////////////////////////////////////////////////

/*
double MnjInfiniteLine::GetMaxDistance(MnjPoint<double> &p){
    double d = GetDistance(p);
	return d;
}
*/


////////////////////////////////////////////////////////////////////////////////////
#if _DEBUG 
void MnjInfiniteLine::Print(void){
cout << "MnjInfiniteLine: ";
cout << "\tstart: ";
	mPoint.Print();
cout << "\tend: ";
//tbd	mDir.Print();
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
MnjInfiniteLine::MnjInfiniteLine(const MnjPoint<double> &s, const MnjPoint<double> &e){
	mPoint = s;
	mDir.Set(s,e); 
}
///////////////////////////////////////////////////////////////////////////////
MnjInfiniteLine::MnjInfiniteLine( MnjLine *const l){
	MnjPoint<double> s;
	MnjPoint<double> e;
	l->GetEnds(s,e);
	mPoint = s;
	mDir.Set(s,e);
}
//////////////////////////////////////////////////////////////////////////////
int MnjInfiniteLine::Intersect(MnjInfiniteLine &line, MnjPoint<double> &pIntersection){
	MnjPoint<double> sp1,ep1;
	GetAnyTwoPointsOnLine(sp1,ep1);

	MnjPoint<double> sp2,ep2;
	line.GetAnyTwoPointsOnLine(sp2,ep2);
	int flag = GeomUtils::LineLineIntersect(sp1,ep1,sp2,ep2,pIntersection);
	return flag;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MnjInfiniteLine::GetAnyTwoPointsOnLine(MnjPoint<double> &op1,MnjPoint<double> &op2)const{
	op1 = mPoint;
	MnjVector v(100*mDir.x,100*mDir.y,100*mDir.z);
	GeomUtils::Translate(mPoint,v,op2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int MnjInfiniteLine::Project(const MnjPoint<double> &p, MnjPoint<double> &pProjection,double tol ){
   double LineMag;
   double U;
     
	MnjPoint<double> LineStart, LineEnd;
	GetAnyTwoPointsOnLine(LineStart,LineEnd);
    GeomUtils::GetDistance( LineEnd, LineStart, LineMag );
 
    U = ( ( ( p.x - LineStart.x ) * ( LineEnd.x - LineStart.x ) ) +
        ( ( p.y - LineStart.y ) * ( LineEnd.y - LineStart.y ) ) +
        ( ( p.z - LineStart.z ) * ( LineEnd.z - LineStart.z ) ) ) /
        ( LineMag * LineMag );
 
   // if( U < 0.0f || U > 1.0f )
    //    return 0;   // closest point does not fall within the line segment
 
    pProjection.x = LineStart.x + U * ( LineEnd.x - LineStart.x );
    pProjection.y = LineStart.y + U * ( LineEnd.y - LineStart.y );
    pProjection.z = LineStart.z + U * ( LineEnd.z - LineStart.z );
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////
void MnjInfiniteLine::GetPoint(MnjPoint<double> &op)const {
	op = mPoint;
}
/////////////////////////////////////////////////////////////////////////////////////
void MnjInfiniteLine::GetDirection(MnjDirection &odir)const{
	odir = mDir;
}
////////////////////////////////////////////////////////////////////////////////////
MnjDirection MnjInfiniteLine::GetDirection(void)const{
	  return mDir;
}
////////////////////////////////////////////////////////////////////////////////////
int MnjInfiniteLine::GetExtermeEnds(MnjPoint<double> &oe1,MnjPoint<double> &oe2){
   const double tmpFactor =  1000000;
   MnjVector v1 = MnjVector(mPoint) + mDir*tmpFactor;
   oe1.Set(v1.x,v1.y,v1.z);
   MnjVector v2 = MnjVector(mPoint) - mDir*tmpFactor;
   oe2.Set(v2.x,v2.y,v2.z);
   return 0;
}