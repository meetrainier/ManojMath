#pragma once
//copyright(c) 2009- 2016 Manoj Lnu 
#include "MnjPoint.h"
#include "MnjVector.h"
#include "MnjOperators.h"
#include "GeomUtils.h"

class MnjPlane{
public:
   
	MnjPoint<double>  origin;

  // unit X axis of plane
  MnjVector xaxis;

  // unit Y axis of plane
  MnjVector yaxis;

  // unit Z axis of plane
  MnjVector zaxis;
  // equation of plane
  //MnjPlaneEquation plane_equation;
MnjPlane() 
        : origin(0.0,0.0,0.0), 
          xaxis(1.0,0.0,0.0), yaxis(0.0,1.0,0.0), zaxis(0.0,0.0,1.0)
{
//  plane_equation.x = plane_equation.y = plane_equation.d = 0.0;
 // plane_equation.z = 1.0;
}

~MnjPlane()
{}
/////////////////////////////
MnjPlane(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& N  // non-zero normal to the plane
    );
MnjPlane(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& X, // non-zero vector in plane
    const MnjVector& Y  // another vector in the plane not parallel to X
    );

MnjPlane(
    const MnjPoint<double>&  P, // point on the plane
    const MnjDirection& X, // non-zero vector in plane
    const MnjDirection& Y  // another vector in the plane not parallel to X
    );


///////////////////////////////////////////////
bool CreateFromFrame(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& X, // non-zero vector in plane
    const MnjVector& Y  // another non-zero vector in the plane
    );

///////////////////////////////////////////////
bool CreateFromNormal(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& N  // non-zero normal to the plane
    );
  bool ClosestPointTo( MnjPoint<double> p, double* s, double* t ) const;

MnjPoint<double> ClosestPointTo( MnjPoint<double> p ) const;

MnjPoint<double> PointAt( double s, double t ) const;



MnjPoint<double> PointAt( double s, double t, double c ) const;



};
/*
extern  const MnjPlane ON_xy_plane;
extern  const MnjPlane ON_yz_plane;
extern  const MnjPlane ON_zx_plane;
*/
