#include "MnjPlane.h"

bool MnjPlane::CreateFromFrame(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& X, // non-zero vector in plane
    const MnjVector& Y  // another non-zero vector in the plane
    )
{
  origin = P;

  xaxis = X;
  xaxis.Unitize();
  yaxis = Y - GeomUtils::DotProduct( Y, xaxis)*xaxis;
  yaxis.Unitize();
  zaxis = GeomUtils::CrossProduct( xaxis, yaxis );
  bool b = zaxis.Unitize();
  //UpdateEquation();
  if ( b )
  {
	  /*tbd
    b = IsValid();
    if ( b )
    {
      // make sure zaxis is perp to Y
      if ( fabs(Y*zaxis) > ON_SQRT_EPSILON*Y.Length() )
        b = false;
    }
	*/
  }
  return b;
}
///////////////////////////////////////////
MnjPlane::MnjPlane(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& N  // non-zero normal to the plane
    )
{
  CreateFromNormal(P,N);
}
MnjPlane::MnjPlane(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& X, // non-zero vector in plane
    const MnjVector& Y  // another vector in the plane not parallel to X
    )
{
  CreateFromFrame(P,X,Y);
}

MnjPlane::MnjPlane(
    const MnjPoint<double>&  P, // point on the plane
    const MnjDirection& X, // non-zero vector in plane
    const MnjDirection& Y  // another vector in the plane not parallel to X
    )
{
  MnjVector X1(X);
  MnjVector Y1(Y);
  CreateFromFrame(P,X1,Y1);
}


///////////////////////////////////////////////
MnjPoint<double> MnjPlane::ClosestPointTo( MnjPoint<double> p ) const
{
  double s, t;
  ClosestPointTo( p, &s, &t );
  return PointAt( s, t );
}

MnjPoint<double> MnjPlane::PointAt( double s, double t ) const
{
  return (origin + s*xaxis + t*yaxis);
}



MnjPoint<double> MnjPlane::PointAt( double s, double t, double c ) const
{
  return (origin + s*xaxis + t*yaxis + c*zaxis);
}
//////////////////////////////////////////////////
bool MnjPlane::CreateFromNormal(
    const MnjPoint<double>&  P, // point on the plane
    const MnjVector& N  // non-zero normal to the plane
    )
{
  origin = P;
  zaxis = N;
  bool b = zaxis.Unitize();
  xaxis.PerpendicularTo( zaxis );
  xaxis.Unitize();
  yaxis = GeomUtils::CrossProduct( zaxis, xaxis );
  yaxis.Unitize();

  //UpdateEquation();

  return b;
}
/////////////////////////////////////////////////////////////////////////////////////////
  bool MnjPlane::ClosestPointTo( MnjPoint<double> p, double* s, double* t ) const
{
  const MnjVector v = p - origin;
  if ( s )
    *s = v*xaxis;
  if ( t )
    *t = v*yaxis;
  return true;
}

