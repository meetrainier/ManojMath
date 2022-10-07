////////////////////////////////////////////////////////////
//copyright(c) 2009- 2016 Manoj Lnu 
///
///     Project : Insert arc among a sequence of segments(lines/arcs).
///     Subsystem : None
///     Author : Manoj Lnu
///     Date : 4/23/2012
///
///		All rights reserved.
///
////////////////////////////////////////////////////////////
#include "MnjOperators.h"

#include "GeomUtils.h"
///////////////////////////////////////////////////////////////////////////////

MnjVector MnjCrossProduct( const MnjVector& a , const MnjVector& b )
{
  return MnjVector(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y );
}
double MnjDotProduct( const MnjVector& a , const MnjVector& b )
{
  // inner (dot) product between 3d vectors
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}

MnjVector operator*(double d, const MnjVector& v)
{
  return MnjVector(d*v.x,d*v.y,d*v.z);
}

/*
MnjPoint<double> operator*(int i, const MnjPoint<double>& p)
{
  double d = i;
  return MnjPoint<double>(d*p.x,d*p.y,d*p.z);
}

MnjPoint<double> operator*(float f, const MnjPoint<double>& p)
{
  double d = f;
  return MnjPoint<double>(d*p.x,d*p.y,d*p.z);
}

MnjPoint<double> operator*(double d, const MnjPoint<double>& p)
{
  return MnjPoint<double>(d*p.x,d*p.y,d*p.z);
}
*/
