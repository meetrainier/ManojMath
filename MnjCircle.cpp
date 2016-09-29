//copyright(c) 2009- 2016 Manoj Lnu 
//Manoj 09/27/2016 Increased use of "auto"
#include <iostream>
#include <cmath>
#include <vector>

#include "MnjCircle.h" 
#include "GeomUtils.h" 
#include "Mnj4x4Matrix.h"
#include "MnjMathNamespace.h"

using namespace std;
using namespace MnjMath; 

void GetPointOnCircle(double &r,std::vector<double> &angleVec, std::vector<dbl_3d_pt> &pointVec){

	std::vector<double>::iterator  it; 
    for ( it=angleVec.begin(); it != angleVec.end() ; it++ ) 
	{
		auto x = r*cos(*it);
		auto y = r*sin(*it);
		auto z = 0.0;
        dbl_3d_pt p(x,y,z);
		pointVec.push_back(p);
	}
}
/*
If the point in pointVec was (0,0,0 ), it will transform to the coordinate of point  
*/
template <class T> 
void MoveCoordinates(MnjPoint<T> &point, std::vector<MnjPoint<T>> &pointVec, std::vector<MnjPoint<T>> &opointVec){

	std::vector<MnjPoint<T>>::iterator  it; 
	opointVec.empty();
    for ( it=pointVec.begin(); it != pointVec.end() ; it++ ) 
	{
        opointVec.push_back(*it + point);
	}
}
///-----------------------------------------------------------------------#include "MnjCircle.h"

int MnjCircle::Intersect(
      const MnjLine& line, 
      double* line_t0,
      dbl_3d_pt& circle_point0,
      double* line_t1,
      dbl_3d_pt& circle_point1
      )
{
  // transform to coordinate system where equation of circle
  // is x^2 + y^2 = R^2 and solve for line parameter(s).
  Mnj4x4Matrix xform;
  MnjPlane xy_plane(dbl_3d_pt(0,0,0),MnjVector(0,0,1));
  xform.ChangeBasis( mplane, xy_plane );
  xform.ChangeBasis( xy_plane, mplane );
  MnjLine L = line;
  L.Transform(xform);
  auto r = fabs(mradius);
  auto tol = r*MNJ_SQRT_EPSILON;
  if ( tol < MNJ_ZERO_TOLERANCE )
    tol = MNJ_ZERO_TOLERANCE;
  int xcnt;
  if (    fabs(L.StartPoint().x - L.EndPoint().x) <= tol 
       && fabs(L.StartPoint().y - L.EndPoint().y) <= tol
       && fabs(L.StartPoint().z - L.EndPoint().z) > tol )
  {
    xcnt = 0;
  }
  else
  {
	//MnjPoint<double> from(L.from.x,L.from.y,L.from.z); //mnj
	dbl_3d_pt from(L.StartPoint()); 
    dbl_3d_pt to(L.EndPoint());
	//xcnt = Intersect2dLineCircle( L.from, L.to, r, tol, line_t0, line_t1 );
	xcnt = GeomUtils::Intersect2dLineCircle( from, to, r, tol, line_t0, line_t1 );
    if ( xcnt == 3 )
      xcnt = 1;
  }
  
  if ( xcnt == 0 )
  {
    if ( L.ClosestPointTo( Center(), line_t0 ) )
    {
      xcnt = 1;
      *line_t1 = *line_t0;
    }
  }
  dbl_3d_pt line_point1, line_point0 = line.PointAt(*line_t0);
  circle_point0 = ClosestPointTo(line_point0);
  double d1, d0 = line_point0.DistanceTo(circle_point0);
  if ( xcnt == 2 ) 
  {
    line_point1 = line.PointAt(*line_t1);
    circle_point1 = ClosestPointTo(line_point1);
    d1 = line_point1.DistanceTo(circle_point1);
  }
  else
  {
    line_point1 = line_point0;
    circle_point1 = circle_point0;
    d1 = d0;
  }
  if ( xcnt==2 && (d0 > tol && d1 > tol) )
  {
    xcnt = 1;
    if ( d0 <= d1 ) 
    {
      *line_t1 = *line_t0;
      line_point1 = line_point0;
      circle_point1 = circle_point0;
      d1 = d0;
    }
    else
    {
      *line_t0 = *line_t1;
      line_point0 = line_point1;
      circle_point0 = circle_point1;
      d0 = d1;
    }
  }
  if ( xcnt == 1 && d0 > tol )
  {
    // TODO: iterate to closest point
  }
  return xcnt;
}
/////////////////////////////////////////////////////////////////////
MnjCircle::MnjCircle( const MnjPlane& p, double r )
{
  Create( p, r );
}
/////////////////////////////////////////////////////////////////////
MnjCircle::MnjCircle( const MnjArc& a ){

    MnjPlane plane(a.GetCenter(),a.GetXAxis(),a.GetYAxis());
    mplane =plane;
    mradius = a.GetRadius();
}
//-------------------------------------------------------------------
MnjCircle::MnjCircle( const std::shared_ptr<MnjArc> a ){

    MnjPlane plane(a->GetCenter(),a->GetXAxis(),a->GetYAxis());
    mplane =plane;
    mradius = a->GetRadius();
}
bool MnjCircle::Create( const MnjPlane& p, double r )
{
  mplane = p;
  //if ( !plane.IsValid() )
   // plane.UpdateEquation(); // people often forget to set equation
  mradius = r;
  return ( mradius > 0.0 );
}
	
double MnjCircle::Radius() const
{
  return mradius;
}
//////////////////////////////////////////////////////////////
void MnjCircle::SetRadius(double &r){
    mradius = r;
}
////////////////////////////////////////////////////////////
const dbl_3d_pt& MnjCircle::Center() const
	{
	 return mplane.origin;
	}
dbl_3d_pt MnjCircle::PointAt( double t ) const
{
  return mplane.PointAt( cos(t)*mradius, sin(t)*mradius );
}

	  // circle is in the plane with center at plane.m_origin.
	dbl_3d_pt MnjCircle::ClosestPointTo( const dbl_3d_pt& point ) const
{
  dbl_3d_pt P;
  MnjVector V = mplane.ClosestPointTo( point ) - Center();
  if ( V.Unitize() ) {
    V.Unitize();
    P = Center() + Radius()*V;
  }
  else {
    P = PointAt(0.0);
  }
  return P;
}
//////////////////////////////////////////////////////////////////////////////
int MnjCircle::Intersect(MnjInfiniteLine &il, shared_ptr_vec_pt  &opt_vec) {
        int error = 0;
        dbl_3d_pt e1,e2;
        il.GetExtermeEnds(e1,e2);
        MnjLine line(e1,e2); 
        double line_t0;
        dbl_3d_pt circle_point0;
        double line_t1;
        dbl_3d_pt circle_point1;
        Intersect(line,&line_t0,circle_point0,&line_t1,circle_point1);
        shared_ptr_pt sp1(new dbl_3d_pt(circle_point0.x,circle_point0.y,circle_point0.z));
        std::shared_ptr<dbl_3d_pt> sp2(new dbl_3d_pt(circle_point1.x,circle_point1.y,circle_point1.z));
        opt_vec.push_back(sp1);
        opt_vec.push_back(sp2);
        return error;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
   int MnjCircle::Intersect(MnjCircle &ic, shared_ptr_vec_pt &opt_vec){

       //Create a frame of reference located : The origin of the reference plane are same as center of circle1
       //The line connection to the two center is X-axis. 

       //call 2d circle intersection method. first center is at origin, the second center 
       // at coords ( x1, 0,0 ) where x1 = distance betwen circles. 
         dbl_3d_pt C1 = Center();
         dbl_3d_pt PI1;
         dbl_3d_pt PI2;
         dbl_3d_pt C2 = ic.Center();
         double d = GeomUtils::GetDistance(C1,C2);
         dbl_3d_pt C2InXY(d,0,0);
         dbl_3d_pt C1InXY(0,0,0);
         int error = GeomUtils::GetIntersectionOfCircles2D(C1InXY,Radius(),C2InXY,ic.Radius(),PI1,PI2);

       //Tansform the intersection point from P0,X0,Y0,Z0 coords to P1,X1,Y1,Z1 
         dbl_3d_pt  P0;//(0,0,0);

       MnjPlane thisPlane = Plane();
       //Mnj4x4Matrix trans(P0,XAxis,YAxis,ZAxis,C1,thisPlane.xaxis,thisPlane.yaxis,thisPlane.zaxis); 

       MnjDirection X1(C1,C2);
       MnjDirection Y1 = GeomUtils::CrossProduct(X1,MnjVector::ZAxis);
       MnjDirection Z1 = GeomUtils::CrossProduct(X1,Y1);
       Mnj4x4Matrix trans;
       trans.Rotation(P0,MnjVector::XAxis,MnjVector::YAxis,MnjVector::ZAxis,C1,X1,Y1,Z1); 
    
       dbl_3d_pt oPI1 =trans*PI1;
       std::shared_ptr<dbl_3d_pt> pt1(new dbl_3d_pt(oPI1));
       opt_vec.push_back(pt1);

       dbl_3d_pt oPI2 =trans*PI2;
       shared_ptr_pt pt2(new dbl_3d_pt(oPI2));
       opt_vec.push_back(pt2);
       return error;
   }
