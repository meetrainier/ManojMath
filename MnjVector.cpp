#include <cmath>
#include "MnjVector.h"
#include "MnjDirection.h"

MnjVector::MnjVector(double a, double b, double c) {
			x = a; y = b ; z = c;
		}
MnjVector::MnjVector(const MnjPoint<double> &p) {
		    x = p.x; 
			y = p.y; 
			z = p.z;
		}

MnjVector::MnjVector( const MnjVector &p){
    x = p.x; 
			y = p.y; 
			z = p.z;

}
////////////////////////////////////////////////////////
bool MnjVector::IsObtuse(const MnjVector &p){
    MnjDirection dir(*this);
    return dir.IsObtuse(p);
}
////////////////////////////////////////////////////////
bool MnjVector::IsAcute(const MnjVector &p){
    MnjDirection dir(*this);
    return dir.IsAcute(p);
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

MnjVector MnjVector::operator+(const MnjVector &p){

	double x1 = this->x + p.x;
	double y1 = this->y + p.y;
	double z1 = this->z + p.z;
	return MnjVector(x1,y1,z1);

}
////////////////////////////////////////////////////////
MnjVector MnjVector::operator-(const MnjVector &p){

	double x1 = this->x - p.x;
	double y1 = this->y - p.y;
	double z1 = this->z - p.z;
	return MnjVector(x1,y1,z1);

}

MnjVector MnjVector::operator-(const MnjVector &p)const{//mnj

	double x1 = this->x - p.x;
	double y1 = this->y - p.y;
	double z1 = this->z - p.z;
	return MnjVector(x1,y1,z1);

}
//////////////////////////////////////////////////////
 MnjVector MnjVector::operator*(const double r) const{
		return MnjVector(r*x,r*y,r*z);
}

 MnjVector::MnjVector(const MnjPoint<double> &s,const MnjPoint<double> &e)
 {
		 x = e.x - s.x;
		 y = e.y - s.y;
		 z = e.z - s.z;
}

 double MnjVector::magnitude(void)const {
		   return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
		
		}

double MnjVector::DotProduct( const MnjVector &vec){
			double val;
			val = 0.0;
			val = x * vec.x +  y * vec.y +  z * vec.z;

			return val;
        }

MnjVector MnjVector::CrossProduct( const MnjVector &vec){
	      MnjVector temp;
	      temp.x = y*vec.z - z*vec.y;
	      temp.y = z*vec.x - x*vec.z;
	      temp.z = x*vec.y - y*vec.x;

	        return MnjVector(temp.x,temp.y,temp.z);
		}
//////////////////////////////////////////////////////
//////////////////////////////////major append after this line 
 ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////

 MnjVector::MnjVector(const MnjDirection &i){
	x = i.x;
	y = i.y;
	z = i.z;
  }
  const MnjVector& MnjVector::UnitVector(int index)
{
  static MnjVector o(0.0,0.0,0.0);
  static MnjVector x(1.0,0.0,0.0);
  static MnjVector y(0.0,1.0,0.0);
  static MnjVector z(0.0,0.0,1.0);
  switch(index)
  {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }
  return o;
}



MnjVector::MnjVector( const float* v )
{
  if (v) {
    x = (double)v[0]; y = (double)v[1]; z = (double)v[2];
  }
  else {
    x = y = z = 0.0;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////
MnjVector::MnjVector( const double* v )
{
  if (v) {
    x = v[0]; y = v[1]; z = v[2];
  }
  else {
    x = y = z = 0.0;
  }
}



  double MnjVector::operator[](int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

double& MnjVector::operator[](int i)
{
  double* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

  double MnjVector::operator*( const MnjVector& v ) const
{
  return (x*v.x + y*v.y + z*v.z);
}

  double MnjVector::LengthSquared() const
{
  return (x*x + y*y + z*z);
}


  double MnjVector::Length() const
{
  double len;
  double fx = fabs(x);
  double fy = fabs(y);
  double fz = fabs(z);
  if ( fy >= fx && fy >= fz ) {
    len = fx; fx = fy; fy = len;
  }
  else if ( fz >= fx && fz >= fy ) {
    len = fx; fx = fz; fz = len;
  }

  // 15 September 2003 Dale Lear
  //     For small denormalized doubles (positive but smaller
  //     than DBL_MIN), some compilers/FPUs set 1.0/fx to +INF.
  //     Without the FlowDBL_MIN test we end up with
  //     microscopic vectors that have infinte length!
  //
  //     This code is absolutely necessary.  It is a critical
  //     part of the bug fix for RR 11217.
  if ( fx > MNJ_DBL_MIN ) 
  {
    len = 1.0/fx;
    fy *= len;
    fz *= len;
    len = fx*sqrt(1.0 + fy*fy + fz*fz);
  }
  else if ( fx > 0.0 && MNJ_IS_FINITE(fx) )
    len = fx;
  else
    len = 0.0;

  return len;
}
  bool MnjVector::Unitize()
{
  // 15 September 2003 Dale Lear
  //     Added the FlowDBL_MIN test.  See MnjVector::Length()
  //     for details.
  bool rc = false;
  double d = Length();
  if ( d > MNJ_DBL_MIN )
  {
    d = 1.0/d;
    x *= d;
    y *= d;
    z *= d;
    rc = true;
  }
  else if ( d > 0.0 && MNJ_IS_FINITE(d) )
  {
    // This code is rarely used and can be slow.
    // It multiplies by 2^1023 in an attempt to 
    // normalize the coordinates.
    // If the renormalization works, then we're
    // ok.  If the renormalization fails, we
    // return false.
    MnjVector tmp;
    tmp.x = x*8.9884656743115795386465259539451e+307;
    tmp.y = y*8.9884656743115795386465259539451e+307;
    tmp.z = z*8.9884656743115795386465259539451e+307;
    d = tmp.Length();
    if ( d > MNJ_DBL_MIN )
    {
      d = 1.0/d;
      x = tmp.x*d;
      y = tmp.y*d;
      z = tmp.z*d;
      rc = true;
    }
    else
    {
      x = 0.0;
      y = 0.0;
      z = 0.0;
    }
  }
  else
  {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  return rc;
}
  /////////////////////////////////////////////////////////////////////////////
  bool MnjVector::PerpendicularTo( const MnjVector& v )
{
  //bool rc = false;
  int i, j, k; 
  double a, b;
  k = 2;
  if ( fabs(v.y) > fabs(v.x) ) {
    if ( fabs(v.z) > fabs(v.y) ) {
      // |v.z| > |v.y| > |v.x|
      i = 2;
      j = 1;
      k = 0;
      a = v.z;
      b = -v.y;
    }
    else if ( fabs(v.z) >= fabs(v.x) ){
      // |v.y| >= |v.z| >= |v.x|
      i = 1;
      j = 2;
      k = 0;
      a = v.y;
      b = -v.z;
    }
    else {
      // |v.y| > |v.x| > |v.z|
      i = 1;
      j = 0;
      k = 2;
      a = v.y;
      b = -v.x;
    }
  }
  else if ( fabs(v.z) > fabs(v.x) ) {
    // |v.z| > |v.x| >= |v.y|
    i = 2;
    j = 0;
    k = 1;
    a = v.z;
    b = -v.x;
  }
  else if ( fabs(v.z) > fabs(v.y) ) {
    // |v.x| >= |v.z| > |v.y|
    i = 0;
    j = 2;
    k = 1;
    a = v.x;
    b = -v.z;
  }
  else {
    // |v.x| >= |v.y| >= |v.z|
    i = 0;
    j = 1;
    k = 2;
    a = v.x;
    b = -v.y;
  }
  double* this_v = &x;
  this_v[i] = b;
  this_v[j] = a;
  this_v[k] = 0.0;
  return (a != 0.0) ? true : false;
}
MnjVector::operator double*()
{
  return &x;
}

MnjVector::operator const double*() const
{
  return &x;
}

MnjVector& MnjVector::operator=(const float* v)
{
  if ( v ) {
    x = (double)v[0];
    y = (double)v[1];
    z = (double)v[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

MnjVector& MnjVector::operator=(const double* v)
{
  if ( v ) {
    x = v[0];
    y = v[1];
    z = v[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}


MnjVector& MnjVector::operator=(const MnjPoint<double>& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
  return *this;
}



/*
MnjVector MnjVector::operator-() const
{
  return MnjVector(-x,-y,-z);
}

MnjVector& MnjVector::operator*=(double d)
{
  x *= d;
  y *= d;
  z *= d;
  return *this;
}

MnjVector& MnjVector::operator/=(double d)
{
  const double one_over_d = 1.0/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  return *this;
}

MnjVector& MnjVector::operator+=(const MnjVector& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

MnjVector& MnjVector::operator-=(const MnjVector& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}
*/
/*
MnjVector MnjVector::operator*( int i ) const
{
  double d = i;
  return MnjVector(x*d,y*d,z*d);
}
*/
/*
MnjVector MnjVector::operator*( float f ) const
{
  double d = f;
  return MnjVector(x*d,y*d,z*d);
}

*/
/*
MnjVector MnjVector::operator+( const Flow2dVector& v ) const
{
  return MnjVector(x+v.x,y+v.y,z);
}

Flow3dPoint MnjVector::operator+( const Flow2dPoint& p ) const
{
  return Flow3dPoint(x+p.x,y+p.y,z);
}

MnjVector MnjVector::operator-( const Flow2dVector& v ) const
{
  return MnjVector(x-v.x,y-v.y,z);
}

Flow3dPoint MnjVector::operator-( const Flow2dPoint& v ) const
{
  return Flow3dPoint(x-v.x,y-v.y,z);
}

MnjVector MnjVector::operator+( const Flow3fVector& v ) const
{
  return MnjVector(x+v.x,y+v.y,z+v.z);
}

Flow3dPoint MnjVector::operator+( const Flow3fPoint& p ) const
{
  return Flow3dPoint(x+p.x,y+p.y,z+p.z);
}

MnjVector MnjVector::operator-( const Flow3fVector& v ) const
{
  return MnjVector(x-v.x,y-v.y,z-v.z);
}

Flow3dPoint MnjVector::operator-( const Flow3fPoint& v ) const
{
  return Flow3dPoint(x-v.x,y-v.y,z-v.z);
}

MnjVector MnjVector::operator+( const Flow2fVector& v ) const
{
  return MnjVector(x+v.x,y+v.y,z);
}

Flow3dPoint MnjVector::operator+( const Flow2fPoint& p ) const
{
  return Flow3dPoint(x+p.x,y+p.y,z);
}
*/
/*
MnjVector MnjVector::operator-( const Flow2fVector& v ) const
{
  return MnjVector(x-v.x,y-v.y,z);
}

Flow3dPoint MnjVector::operator-( const Flow2fPoint& v ) const
{
  return Flow3dPoint(x-v.x,y-v.y,z);
}


double MnjVector::operator*(const Flow4dPoint& h) const
{
  return x*h.x + y*h.y + z*h.z;
}
*/
/*
bool MnjVector::operator==( const MnjVector& v ) const
{
  return (x==v.x&&y==v.y&&z==v.z)?true:false;
}

bool MnjVector::operator!=( const MnjVector& v ) const
{
  return (x!=v.x||y!=v.y||z!=v.z)?true:false;
}

bool MnjVector::operator<=( const MnjVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x)?((y<v.y)?true:(y==v.y&&z<=v.z)?true:false):false));
}

bool MnjVector::operator>=( const MnjVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x)?((y>v.y)?true:(y==v.y&&z>=v.z)?true:false):false));
}

bool MnjVector::operator<( const MnjVector& v ) const
{
  // dictionary order
  return ((x<v.x)?true:((x==v.x)?((y<v.y)?true:(y==v.y&&z<v.z)?true:false):false));
}

bool MnjVector::operator>( const MnjVector& v ) const
{
  // dictionary order
  return ((x>v.x)?true:((x==v.x)?((y>v.y)?true:(y==v.y&&z>v.z)?true:false):false));
}

int MnjVector::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? ((fabs(z)>fabs(y))?2:1) : ((fabs(z)>fabs(x))?2:0);
}

double MnjVector::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z);
  return c;
}

int MnjVector::MinimumCoordinateIndex() const
{
  return (fabs(y)<fabs(x)) ? ((fabs(z)<fabs(y))?2:1) : ((fabs(z)<fabs(x))?2:0);
}

double MnjVector::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y); if (fabs(z)<c) c=fabs(z);
  return c;
}

void MnjVector::Zero()
{
  x = y = z = 0.0;
}

void MnjVector::Reverse()
{
  x = -x;
  y = -y;
  z = -z;
}



double MnjVector::LengthAndUnitize()
{
  double d;
  double len = Length();
  if ( len > FLOW_DBL_MIN )
  {
    d = 1.0/len;
    x *= d;
    y *= d;
    z *= d;
  }
  else if ( len > 0.0 && FLOW_IS_FINITE(len) )
  {
    // This code is rarely used and can be slow.
    // It multiplies by 2^1023 in an attempt to 
    // normalize the coordinates.
    // If the renormalization works, then we're
    // ok.  If the renormalization fails, we
    // return false.
    MnjVector tmp;
    tmp.x = x*8.9884656743115795386465259539451e+307;
    tmp.y = y*8.9884656743115795386465259539451e+307;
    tmp.z = z*8.9884656743115795386465259539451e+307;
    d = tmp.Length();
    if ( d > FLOW_DBL_MIN )
    {
      d = 1.0/d;
      x = tmp.x*d;
      y = tmp.y*d;
      z = tmp.z*d;
    }
    else
    {
      len = 0.0;
      x = 0.0;
      y = 0.0;
      z = 0.0;
    }
  }
  else
  {
    len = 0.0;
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  return len;
}


bool MnjVector::IsTiny( double tiny_tol ) const
{
  return (fabs(x) <= tiny_tol && fabs(y) <= tiny_tol && fabs(z) <= tiny_tol );
}

bool MnjVector::IsZero() const
{
  return (x==0.0 && y==0.0 && z==0.0);
}

bool MnjVector::IsUnitVector() const
{
  return (x != FLOW_UNSET_VALUE && y != FLOW_UNSET_VALUE && z != FLOW_UNSET_VALUE && fabs(Length() - 1.0) <= FLOW_SQRT_EPSILON);
}
*/ 

const MnjVector MnjVector::ZeroVector(0.0,0.0,0.0);
const MnjVector MnjVector::XAxis(1.0,0.0,0.0);
const MnjVector MnjVector::YAxis(0.0,1.0,0.0);
const MnjVector MnjVector::ZAxis(0.0,0.0,1.0);
const MnjVector MnjVector::UnsetVector(MNJ_UNSET_VALUE,MNJ_UNSET_VALUE,MNJ_UNSET_VALUE);

////////////////////////////////////////////////////////////////
/*
void MnjVector::Rotate( 
      double angle,              // angle in radians
      const MnjVector& axis   // axis of rotation
      )
{
  Rotate( sin(angle), cos(angle), axis );
}

void MnjVector::Rotate( 
      double sin_angle,        // sin(angle)
      double cos_angle,        // cos(angle)
      const MnjVector& axis  // axis of rotation
      )
{
  //bool rc = false;
  FlowXform rot;
  rot.Rotation( sin_angle, cos_angle, axis, Floworigin );
  Transform(rot);
}
*/
/*

bool MnjVector::Decompose( // Computes a, b, c such that this vector = a*X + b*Y + c*Z
       //
       // If X,Y,Z is known to be an orthonormal frame,
       // then a = V*X, b = V*Y, c = V*Z will compute
       // the same result more quickly.
       const MnjVector& X,
       const MnjVector& Y,
       const MnjVector& Z,
       double* a,
       double* b,
       double* c
       ) const
{
  int rank;
  double pivot_ratio = 0.0;
  double row0[3], row1[3], row2[3];
  row0[0] = X*X;   row0[1] = X*Y;   row0[2] = X*Z;
  row1[0] = row0[1]; row1[1] = Y*Y;   row1[2] = Y*Z;
  row2[0] = row0[2]; row2[1] = row1[2]; row2[2] = Z*Z;
  rank = FlowSolve3x3( row0, row1, row2, 
                    (*this)*X, (*this)*Y, (*this)*Z,
                    a, b, c, &pivot_ratio );
  return (rank == 3) ? true : false;
}

int MnjVector::IsParallelTo( 
      // returns  1: this and other vectors are and parallel
      //         -1: this and other vectors are anti-parallel
      //          0: this and other vectors are not parallel
      //             or at least one of the vectors is zero
      const MnjVector& v,
      double angle_tolerance // (default=FlowDEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  int rc = 0;
  const double ll = Length()*v.Length();
  if ( ll > 0.0 ) {
    const double cos_angle = (x*v.x + y*v.y + z*v.z)/ll;
    const double cos_tol = cos(angle_tolerance);
    if ( cos_angle >= cos_tol )
      rc = 1;
    else if ( cos_angle <= -cos_tol )
      rc = -1;
  }
  return rc;
}
*/
/*
bool MnjVector::PerpendicularTo( const MnjVector& v )
{
  //bool rc = false;
  int i, j, k; 
  double a, b;
  k = 2;
  if ( fabs(v.y) > fabs(v.x) ) {
    if ( fabs(v.z) > fabs(v.y) ) {
      // |v.z| > |v.y| > |v.x|
      i = 2;
      j = 1;
      k = 0;
      a = v.z;
      b = -v.y;
    }
    else if ( fabs(v.z) >= fabs(v.x) ){
      // |v.y| >= |v.z| >= |v.x|
      i = 1;
      j = 2;
      k = 0;
      a = v.y;
      b = -v.z;
    }
    else {
      // |v.y| > |v.x| > |v.z|
      i = 1;
      j = 0;
      k = 2;
      a = v.y;
      b = -v.x;
    }
  }
  else if ( fabs(v.z) > fabs(v.x) ) {
    // |v.z| > |v.x| >= |v.y|
    i = 2;
    j = 0;
    k = 1;
    a = v.z;
    b = -v.x;
  }
  else if ( fabs(v.z) > fabs(v.y) ) {
    // |v.x| >= |v.z| > |v.y|
    i = 0;
    j = 2;
    k = 1;
    a = v.x;
    b = -v.z;
  }
  else {
    // |v.x| >= |v.y| >= |v.z|
    i = 0;
    j = 1;
    k = 2;
    a = v.x;
    b = -v.y;
  }
  double* this_v = &x;
  this_v[i] = b;
  this_v[j] = a;
  this_v[k] = 0.0;
  return (a != 0.0) ? true : false;
}

bool
MnjVector::PerpendicularTo( 
      const Flow3dPoint& P0, const Flow3dPoint& P1, const Flow3dPoint& P2
      )
{
  // Find a the unit normal to a triangle defined by 3 points
  MnjVector V0, V1, V2, N0, N1, N2;

  Zero();

  V0 = P2 - P1;
  V1 = P0 - P2;
  V2 = P1 - P0;

  N0 = FlowCrossProduct( V1, V2 );
  if ( !N0.Unitize() )
    return false;
  N1 = FlowCrossProduct( V2, V0 );
  if ( !N1.Unitize() )
    return false;
  N2 = FlowCrossProduct( V0, V1 );
  if ( !N2.Unitize() )
    return false;

  const double s0 = 1.0/V0.Length();
  const double s1 = 1.0/V1.Length();
  const double s2 = 1.0/V2.Length();

  // choose normal with smallest total error
  const double e0 = s0*fabs(FlowDotProduct(N0,V0)) + s1*fabs(FlowDotProduct(N0,V1)) + s2*fabs(FlowDotProduct(N0,V2));
  const double e1 = s0*fabs(FlowDotProduct(N1,V0)) + s1*fabs(FlowDotProduct(N1,V1)) + s2*fabs(FlowDotProduct(N1,V2));
  const double e2 = s0*fabs(FlowDotProduct(N2,V0)) + s1*fabs(FlowDotProduct(N2,V1)) + s2*fabs(FlowDotProduct(N2,V2));

  if ( e0 <= e1 ) {
    if ( e0 <= e2 ) {
      *this = N0;
    }
    else {
      *this = N2;
    }
  }
  else if (e1 <= e2) {
    *this = N1;
  }
  else {
    *this = N2;
  }
  
  return true;
}
*/
///////////////////////////////////////////////////////////////////////////
bool MnjVector::IsPerpendicularTo(
      // returns true:  this and other vectors are perpendicular
      //         false: this and other vectors are not perpendicular
      //                or at least one of the vectors is zero
      const MnjVector& v,
      double angle_tolerance // (default=FlowDEFAULT_ANGLE_TOLERANCE) radians
      ) const
{
  bool rc = false;
  const double ll = Length()*v.Length();
  if ( ll > 0.0 ) {
    if ( fabs((x*v.x + y*v.y + z*v.z)/ll) <= sin(angle_tolerance) )
      rc = true;
  }
  return rc;
}



/*#include "MnjVector.h"

MnjVector MnjVector::operator+(MnjVector &p){

	double x1 = this->x + p.x;
	double y1 = this->y + p.y;
	double z1 = this->z + p.z;
	return MnjVector(x1,y1,z1);

}
////////////////////////////////////////////////////////
MnjVector MnjVector::operator-(MnjVector &p){

	double x1 = this->x - p.x;
	double y1 = this->y - p.y;
	double z1 = this->z - p.z;
	return MnjVector(x1,y1,z1);

}
*/
//////////////////////////////////////////////////////
