////////////////////////////////////////////////////////////
///
///     Project : Insert arc among a sequence of segments(lines/arcs).
///     Subsystem : None
///     Author : Manoj Lnu
///     Date : 4/23/2012
///
///     Copyright (C) Manoj Lnu 2009-2016 
///		All rights reserved.
///
////////////////////////////////////////////////////////////
#include "Mnj4x4Matrix.h"
#include "GeomUtils.h"
#include "MnjPlane.h"

Mnj4x4Matrix::Mnj4x4Matrix()
	{
	  memset( m_xform, 0, sizeof(m_xform) );
	  m_xform[3][3] = 1.0;
	}

Mnj4x4Matrix::Mnj4x4Matrix( const double m[4][4] )
{
  memcpy( &m_xform[0][0], &m[0][0], sizeof(m_xform) );
}
Mnj4x4Matrix::Mnj4x4Matrix( const MnjPoint<double>& P,
														 const MnjDirection& X,
														 const MnjDirection& Y,
														 const MnjDirection& Z)
{
 Mnj4x4Matrix::Mnj4x4Matrix(P,
														 MnjVector(X),
														 MnjVector(Y),
														 MnjVector(Z));
}

Mnj4x4Matrix::Mnj4x4Matrix( const MnjPoint<double>& P,
														 const MnjVector& X,
														 const MnjVector& Y,
														 const MnjVector& Z)
{
  m_xform[0][0] = X[0];
  m_xform[1][0] = X[1];
  m_xform[2][0] = X[2];
  m_xform[3][0] = 0;

  m_xform[0][1] = Y[0];
  m_xform[1][1] = Y[1];
  m_xform[2][1] = Y[2];
  m_xform[3][1] = 0;

  m_xform[0][2] = Z[0];
  m_xform[1][2] = Z[1];
  m_xform[2][2] = Z[2];
  m_xform[3][2] = 0;

  m_xform[0][3] = P[0];
  m_xform[1][3] = P[1];
  m_xform[2][3] = P[2];
  m_xform[3][3] = 1;
}
/////////////////////////////////////////////////////////////////////////////////////
Mnj4x4Matrix Mnj4x4Matrix::Inverse( double* pivot ) const
{
  Mnj4x4Matrix inv;
  double d = 0.0, p = 0.0;
  //int rank = 
  GeomUtils::Inv( &m_xform[0][0], inv.m_xform, &d, &p );
  if ( pivot )
    *pivot = p;
  return inv;
}


void Mnj4x4Matrix::Rotation(
  const MnjVector&  X0, // initial frame X (X,Y,Z = right handed orthonormal frame)
  const MnjVector&  Y0, // initial frame Y
  const MnjVector&  Z0, // initial frame Z
  const MnjVector&  X1, // final frame X (X,Y,Z = another right handed orthonormal frame)
  const MnjVector&  Y1, // final frame Y
  const MnjVector&  Z1  // final frame Z
  )
{
  // transformation maps X0 to X1, Y0 to Y1, Z0 to Z1

  // F0 changes x0,y0,z0 to world X,Y,Z
  Mnj4x4Matrix F0;
  F0[0][0] = X0.x; F0[0][1] = X0.y; F0[0][2] = X0.z;
  F0[1][0] = Y0.x; F0[1][1] = Y0.y; F0[1][2] = Y0.z;
  F0[2][0] = Z0.x; F0[2][1] = Z0.y; F0[2][2] = Z0.z;
  F0[3][3] = 1.0;

  // F1 changes world X,Y,Z to x1,y1,z1
  Mnj4x4Matrix F1;
  F1[0][0] = X1.x; F1[0][1] = Y1.x; F1[0][2] = Z1.x;
  F1[1][0] = X1.y; F1[1][1] = Y1.y; F1[1][2] = Z1.y;
  F1[2][0] = X1.z; F1[2][1] = Y1.z; F1[2][2] = Z1.z;
  F1[3][3] = 1.0;

  *this = F1*F0;
}
/*
void Mnj4x4Matrix::Rotation( 
  const MnjPlane& plane0,
  const MnjPlane& plane1
  )
{
  Rotation( 
    plane0.origin, plane0.xaxis, plane0.yaxis, plane0.zaxis,
    plane1.origin, plane1.xaxis, plane1.yaxis, plane1.zaxis
    );
}
*/
////////////////////////////////////////////////////////////////////
void Mnj4x4Matrix::Rotation(   // (not strictly a rotation)
                            // transformation maps P0 to P1, P0+X0 to P1+X1, ...
  const MnjPoint<double>&   P0,  // initial frame center
  const MnjVector&  X0, // initial frame X
  const MnjVector&  Y0, // initial frame Y
  const MnjVector&  Z0, // initial frame Z
  const MnjPoint<double>&   P1,  // final frame center
  const MnjVector&  X1, // final frame X
  const MnjVector&  Y1, // final frame Y
  const MnjVector&  Z1  // final frame Z
  )
{
  // transformation maps P0 to P1, P0+X0 to P1+X1, ...

  // T0 translates point P0 to (0,0,0)
  Mnj4x4Matrix T0;
  T0.Translation( -P0.x, -P0.y, -P0.z );

  Mnj4x4Matrix R;
  R.Rotation(X0,Y0,Z0,X1,Y1,Z1);

  // T1 translates (0,0,0) to point o1
  Mnj4x4Matrix T1;
  T1.Translation( P1 );

  *this = T1*R*T0;
}
////////////////////////////////////////////////////////////////
double* Mnj4x4Matrix::operator[](int i)
{
  return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : NULL;
}

const double* Mnj4x4Matrix::operator[](int i) const
{
  return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : NULL;
}
//major 
void Mnj4x4Matrix::Translation( double x, double y, double z )
{
  Identity();
  m_xform[0][3] = x;
  m_xform[1][3] = y;
  m_xform[2][3] = z;
  m_xform[3][3] = 1.0;
}

void Mnj4x4Matrix::Translation( const MnjPoint<double>& v )
{
  Identity();
  m_xform[0][3] = v.x;
  m_xform[1][3] = v.y;
  m_xform[2][3] = v.z;
  m_xform[3][3] = 1.0;
}

void Mnj4x4Matrix::Translation( const MnjVector& v )
{
  Identity();
  m_xform[0][3] = v.x;
  m_xform[1][3] = v.y;
  m_xform[2][3] = v.z;
  m_xform[3][3] = 1.0;
}
MnjPoint<double> Mnj4x4Matrix::operator*( const MnjPoint<double>& p ) const
{
  const double x = p.x; // optimizer should put x,y,z in registers
  const double y = p.y;
  const double z = p.z;
  double xh[3], w;
  const double* m = &m_xform[0][0];
  xh[0] = m[ 0]*x + m[ 1]*y + m[ 2]*z + m[ 3];
  xh[1] = m[ 4]*x + m[ 5]*y + m[ 6]*z + m[ 7];
  xh[2] = m[ 8]*x + m[ 9]*y + m[10]*z + m[11];
  w     = m[12]*x + m[13]*y + m[14]*z + m[15];
  w = (w != 0.0) ? 1.0/w : 1.0;
  return MnjPoint<double>( w*xh[0], w*xh[1], w*xh[2] );
}

MnjVector Mnj4x4Matrix::operator*( const MnjVector& p ) const
{//mnj
  const double x = p.x; // optimizer should put x,y,z in registers
  const double y = p.y;
  const double z = p.z;
  double xh[3], w;
  const double* m = &m_xform[0][0];
  xh[0] = m[ 0]*x + m[ 1]*y + m[ 2]*z + m[ 3];
  xh[1] = m[ 4]*x + m[ 5]*y + m[ 6]*z + m[ 7];
  xh[2] = m[ 8]*x + m[ 9]*y + m[10]*z + m[11];
  w     = m[12]*x + m[13]*y + m[14]*z + m[15];
  w = (w != 0.0) ? 1.0/w : 1.0;
  return MnjVector( w*xh[0], w*xh[1], w*xh[2] );
}
Mnj4x4Matrix Mnj4x4Matrix::operator*( const Mnj4x4Matrix& rhs ) const
{
  double m[4][4];
  const double* p = &rhs.m_xform[0][0];

  m[0][0] = m_xform[0][0]*p[0] + m_xform[0][1]*p[4] + m_xform[0][2]*p[ 8] + m_xform[0][3]*p[12];
  m[0][1] = m_xform[0][0]*p[1] + m_xform[0][1]*p[5] + m_xform[0][2]*p[ 9] + m_xform[0][3]*p[13];
  m[0][2] = m_xform[0][0]*p[2] + m_xform[0][1]*p[6] + m_xform[0][2]*p[10] + m_xform[0][3]*p[14];
  m[0][3] = m_xform[0][0]*p[3] + m_xform[0][1]*p[7] + m_xform[0][2]*p[11] + m_xform[0][3]*p[15];

  m[1][0] = m_xform[1][0]*p[0] + m_xform[1][1]*p[4] + m_xform[1][2]*p[ 8] + m_xform[1][3]*p[12];
  m[1][1] = m_xform[1][0]*p[1] + m_xform[1][1]*p[5] + m_xform[1][2]*p[ 9] + m_xform[1][3]*p[13];
  m[1][2] = m_xform[1][0]*p[2] + m_xform[1][1]*p[6] + m_xform[1][2]*p[10] + m_xform[1][3]*p[14];
  m[1][3] = m_xform[1][0]*p[3] + m_xform[1][1]*p[7] + m_xform[1][2]*p[11] + m_xform[1][3]*p[15];

  m[2][0] = m_xform[2][0]*p[0] + m_xform[2][1]*p[4] + m_xform[2][2]*p[ 8] + m_xform[2][3]*p[12];
  m[2][1] = m_xform[2][0]*p[1] + m_xform[2][1]*p[5] + m_xform[2][2]*p[ 9] + m_xform[2][3]*p[13];
  m[2][2] = m_xform[2][0]*p[2] + m_xform[2][1]*p[6] + m_xform[2][2]*p[10] + m_xform[2][3]*p[14];
  m[2][3] = m_xform[2][0]*p[3] + m_xform[2][1]*p[7] + m_xform[2][2]*p[11] + m_xform[2][3]*p[15];

  m[3][0] = m_xform[3][0]*p[0] + m_xform[3][1]*p[4] + m_xform[3][2]*p[ 8] + m_xform[3][3]*p[12];
  m[3][1] = m_xform[3][0]*p[1] + m_xform[3][1]*p[5] + m_xform[3][2]*p[ 9] + m_xform[3][3]*p[13];
  m[3][2] = m_xform[3][0]*p[2] + m_xform[3][1]*p[6] + m_xform[3][2]*p[10] + m_xform[3][3]*p[14];
  m[3][3] = m_xform[3][0]*p[3] + m_xform[3][1]*p[7] + m_xform[3][2]*p[11] + m_xform[3][3]*p[15];

  return Mnj4x4Matrix(m);
}

Mnj4x4Matrix Mnj4x4Matrix::operator+( const Mnj4x4Matrix& rhs ) const
{
  double m[4][4];
  const double* p = &rhs.m_xform[0][0];

  m[0][0] = m_xform[0][0] + p[0];
  m[0][1] = m_xform[0][1] + p[1];
  m[0][2] = m_xform[0][2] + p[2];
  m[0][3] = m_xform[0][3] + p[3];

  m[1][0] = m_xform[1][0] + p[4];
  m[1][1] = m_xform[1][1] + p[5];
  m[1][2] = m_xform[1][2] + p[6];
  m[1][3] = m_xform[1][3] + p[7];

  m[2][0] = m_xform[2][0] + p[ 8];
  m[2][1] = m_xform[2][1] + p[ 9];
  m[2][2] = m_xform[2][2] + p[10];
  m[2][3] = m_xform[2][3] + p[11];

  m[3][0] = m_xform[3][0] + p[12];
  m[3][1] = m_xform[3][1] + p[13];
  m[3][2] = m_xform[3][2] + p[14];
  m[3][3] = m_xform[3][3] + p[15];

  return Mnj4x4Matrix(m);
}

Mnj4x4Matrix Mnj4x4Matrix::operator-( const Mnj4x4Matrix& rhs ) const
{
  double m[4][4];
  const double* p = &rhs.m_xform[0][0];

  m[0][0] = m_xform[0][0] - p[0];
  m[0][1] = m_xform[0][1] - p[1];
  m[0][2] = m_xform[0][2] - p[2];
  m[0][3] = m_xform[0][3] - p[3];

  m[1][0] = m_xform[1][0] - p[4];
  m[1][1] = m_xform[1][1] - p[5];
  m[1][2] = m_xform[1][2] - p[6];
  m[1][3] = m_xform[1][3] - p[7];

  m[2][0] = m_xform[2][0] - p[ 8];
  m[2][1] = m_xform[2][1] - p[ 9];
  m[2][2] = m_xform[2][2] - p[10];
  m[2][3] = m_xform[2][3] - p[11];

  m[3][0] = m_xform[3][0] - p[12];
  m[3][1] = m_xform[3][1] - p[13];
  m[3][2] = m_xform[3][2] - p[14];
  m[3][3] = m_xform[3][3] - p[15];

  return Mnj4x4Matrix(m);
}

	
bool Mnj4x4Matrix::ChangeBasis( 
  const MnjPlane& plane0, // initial plane
  const MnjPlane& plane1  // final plane
  )
{
  return ChangeBasis( 
    plane0.origin, plane0.xaxis, plane0.yaxis, plane0.zaxis,
    plane1.origin, plane1.xaxis, plane1.yaxis, plane1.zaxis
    );

}
	
bool Mnj4x4Matrix::ChangeBasis(
  const MnjPoint<double>&   P0,  // initial frame center
  const MnjVector&  X0, // initial frame X (X,Y,Z = arbitrary basis)
  const MnjVector&  Y0, // initial frame Y
  const MnjVector&  Z0, // initial frame Z
  const MnjPoint<double>&   P1,  // final frame center
  const MnjVector&  X1, // final frame X (X,Y,Z = arbitrary basis)
  const MnjVector&  Y1, // final frame Y
  const MnjVector&  Z1  // final frame Z
  )
{
  bool rc = false;
  // Q = P0 + a0*X0 + b0*Y0 + c0*Z0 = P1 + a1*X1 + b1*Y1 + c1*Z1
  // then this transform will map the point (a0,b0,c0) to (a1,b1,c1)

  Mnj4x4Matrix F0(P0,X0,Y0,Z0);		// Frame 0

  // T1 translates by -P1
  Mnj4x4Matrix T1;
  T1.Translation( -P1.x, -P1.y, -P1.z );
	
  Mnj4x4Matrix CB;
  //rc = CB.ChangeBasis(ON_xaxis, ON_yaxis, ON_zaxis,X1,Y1,Z1);
  //
  // ON_xaxis is OBSOLETE - use MnjPoint<double>::XAxis
  //rc = CB.ChangeBasis(MnjVector::XAxis, MnjVector::YAxis, MnjVector::ZAxis,X1,Y1,Z1);
  MnjVector XAxis(1,0,0);
  MnjVector YAxis(0,1,0);
  MnjVector ZAxis(0,0,1);
  rc = CB.ChangeBasis(XAxis, YAxis, ZAxis,X1,Y1,Z1);

  *this = CB*T1*F0;
  return rc;
}

bool Mnj4x4Matrix::ChangeBasis(
  const MnjVector&  X0, // initial frame X (X,Y,Z = arbitrary basis)
  const MnjVector&  Y0, // initial frame Y
  const MnjVector&  Z0, // initial frame Z
  const MnjVector&  X1, // final frame X (X,Y,Z = arbitrary basis)
  const MnjVector&  Y1, // final frame Y
  const MnjVector&  Z1  // final frame Z
  )
{
  // Q = a0*X0 + b0*Y0 + c0*Z0 = a1*X1 + b1*Y1 + c1*Z1
  // then this transform will map the point (a0,b0,c0) to (a1,b1,c1)

  Zero();
  m_xform[3][3] = 1.0;
  double a,b,c,d;
  a = X1*Y1;
  b = X1*Z1;
  c = Y1*Z1;
  double R[3][6] = {{X1*X1,      a,      b,       X1*X0, X1*Y0, X1*Z0},
                    {    a,  Y1*Y1,      c,       Y1*X0, Y1*Y0, Y1*Z0},
                    {    b,      c,  Z1*Z1,       Z1*X0, Z1*Y0, Z1*Z0}};
  //double R[3][6] = {{X1*X1,      a,      b,       X0*X1, X0*Y1, X0*Z1},
  //                  {    a,  Y1*Y1,      c,       Y0*X1, Y0*Y1, Y0*Z1},
  //                  {    b,      c,  Z1*Z1,       Z0*X1, Z0*Y1, Z0*Z1}};

  // row reduce R
  int i0 = (R[0][0] >= R[1][1]) ? 0 : 1;
  if ( R[2][2] > R[i0][i0] )
    i0 = 2;
  int i1 = (i0+1)%3;
  int i2 = (i1+1)%3;
  if ( R[i0][i0] == 0.0 )
    return false;
  d = 1.0/R[i0][i0];
  R[i0][0] *= d;
  R[i0][1] *= d;
  R[i0][2] *= d;
  R[i0][3] *= d;
  R[i0][4] *= d;
  R[i0][5] *= d;
  R[i0][i0] = 1.0;
  if ( R[i1][i0] != 0.0 ) {
    d = -R[i1][i0];
    R[i1][0] += d*R[i0][0];
    R[i1][1] += d*R[i0][1];
    R[i1][2] += d*R[i0][2];
    R[i1][3] += d*R[i0][3];
    R[i1][4] += d*R[i0][4];
    R[i1][5] += d*R[i0][5];
    R[i1][i0] = 0.0;
  }
  if ( R[i2][i0] != 0.0 ) {
    d = -R[i2][i0];
    R[i2][0] += d*R[i0][0];
    R[i2][1] += d*R[i0][1];
    R[i2][2] += d*R[i0][2];
    R[i2][3] += d*R[i0][3];
    R[i2][4] += d*R[i0][4];
    R[i2][5] += d*R[i0][5];
    R[i2][i0] = 0.0;
  }

  if ( fabs(R[i1][i1]) < fabs(R[i2][i2]) ) {
    int i = i1; i1 = i2; i2 = i;
  }
  if ( R[i1][i1] == 0.0 )
    return false;
  d = 1.0/R[i1][i1];
  R[i1][0] *= d;
  R[i1][1] *= d;
  R[i1][2] *= d;
  R[i1][3] *= d;
  R[i1][4] *= d;
  R[i1][5] *= d;
  R[i1][i1] = 1.0;
  if ( R[i0][i1] != 0.0 ) {
    d = -R[i0][i1];
    R[i0][0] += d*R[i1][0];
    R[i0][1] += d*R[i1][1];
    R[i0][2] += d*R[i1][2];
    R[i0][3] += d*R[i1][3];
    R[i0][4] += d*R[i1][4];
    R[i0][5] += d*R[i1][5];
    R[i0][i1] = 0.0;
  }
  if ( R[i2][i1] != 0.0 ) {
    d = -R[i2][i1];
    R[i2][0] += d*R[i1][0];
    R[i2][1] += d*R[i1][1];
    R[i2][2] += d*R[i1][2];
    R[i2][3] += d*R[i1][3];
    R[i2][4] += d*R[i1][4];
    R[i2][5] += d*R[i1][5];
    R[i2][i1] = 0.0;
  }

  if ( R[i2][i2] == 0.0 )
    return false;
  d = 1.0/R[i2][i2];
  R[i2][0] *= d;
  R[i2][1] *= d;
  R[i2][2] *= d;
  R[i2][3] *= d;
  R[i2][4] *= d;
  R[i2][5] *= d;
  R[i2][i2] = 1.0;
  if ( R[i0][i2] != 0.0 ) {
    d = -R[i0][i2];
    R[i0][0] += d*R[i2][0];
    R[i0][1] += d*R[i2][1];
    R[i0][2] += d*R[i2][2];
    R[i0][3] += d*R[i2][3];
    R[i0][4] += d*R[i2][4];
    R[i0][5] += d*R[i2][5];
    R[i0][i2] = 0.0;
  }
  if ( R[i1][i2] != 0.0 ) {
    d = -R[i1][i2];
    R[i1][0] += d*R[i2][0];
    R[i1][1] += d*R[i2][1];
    R[i1][2] += d*R[i2][2];
    R[i1][3] += d*R[i2][3];
    R[i1][4] += d*R[i2][4];
    R[i1][5] += d*R[i2][5];
    R[i1][i2] = 0.0;
  }

  m_xform[0][0] = R[0][3];
  m_xform[0][1] = R[0][4];
  m_xform[0][2] = R[0][5];

  m_xform[1][0] = R[1][3];
  m_xform[1][1] = R[1][4];
  m_xform[1][2] = R[1][5];

  m_xform[2][0] = R[2][3];
  m_xform[2][1] = R[2][4];
  m_xform[2][2] = R[2][5];

  return true;
}

void Mnj4x4Matrix::Identity()
{
  memset( m_xform, 0, sizeof(m_xform) );
  m_xform[0][0] = m_xform[1][1] = m_xform[2][2] = m_xform[3][3] = 1.0;
}
void Mnj4x4Matrix::Zero()
{
  memset( m_xform, 0, sizeof(m_xform) );
}
/*
bool Mnj4x4Matrix::ChangeBasis( 
  const MnjPlane& plane0, // initial plane
  const MnjPlane& plane1  // final plane
  )
{
     return ChangeBasis( 
    plane0.origin, plane0.xaxis, plane0.yaxis, plane0.zaxis,
    plane1.origin, plane1.xaxis, plane1.yaxis, plane1.zaxis
    );

}
*/