//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
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

  
 
  //     Without the MNJ_DBL_MIN test we end up with
  //     microscopic vectors that have infinte length!
  //
  //     This code is absolutely necessary.  .
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

  //     Added the MNJ_DBL_MIN test.  See MnjVector::Length()
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


const MnjVector MnjVector::ZeroVector(0.0,0.0,0.0);
const MnjVector MnjVector::XAxis(1.0,0.0,0.0);
const MnjVector MnjVector::YAxis(0.0,1.0,0.0);
const MnjVector MnjVector::ZAxis(0.0,0.0,1.0);
const MnjVector MnjVector::UnsetVector(MNJ_UNSET_VALUE,MNJ_UNSET_VALUE,MNJ_UNSET_VALUE);

////////////////////////////////////////////////////////////////

/*
int MnjVector::IsParallelTo( 
      // returns  1: this and other vectors are and parallel
      //         -1: this and other vectors are anti-parallel
      //          0: this and other vectors are not parallel
      //             or at least one of the vectors is zero
      const MnjVector& v,
      double angle_tolerance 
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

  
*/
///////////////////////////////////////////////////////////////////////////
bool MnjVector::IsPerpendicularTo(
      // returns true:  this and other vectors are perpendicular
      //         false: this and other vectors are not perpendicular
      //                or at least one of the vectors is zero
      const MnjVector& v,
      double angle_tolerance 
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
