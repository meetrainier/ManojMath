//copyright(c) 2009- 2016 Manoj Lnu 
#include "MNJPoint.h" 
#include "MnjVector.h"
template <>
MnjPoint<double>::MnjPoint(const MnjVector& v)
{
    x=v.x;
    y=v.y;
    z=v.z;
}
/*
MnjPoint<double>::MnjPoint( const float* p )
{
  if (p) {
    x = (double)p[0]; y = (double)p[1]; z = (double)p[2];
  }
  else {
    x = y = z = 0.0;
  }
}
*/

MnjPoint<double>::MnjPoint( const double* p )
{
  if (p) {
    x = p[0]; y = p[1]; z = p[2];
  }
  else {
    x = y = z = 0.0;
  }
}

MnjPoint<double>::MnjPoint(double xx,double yy,double zz)
{x=xx;y=yy;z=zz;}
/////////////////////////////////////////////////////////////////
template<>
MnjPoint<double>::MnjPoint(const MnjPoint<double> &ip){
	x = ip.x;
	y = ip.y;
	z = ip.z;
}
//operators 
MnjPoint<double>& MnjPoint<double>::operator=(const float* p)
{
  if ( p ) {
    x = (double)p[0];
    y = (double)p[1];
    z = (double)p[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

MnjPoint<double>& MnjPoint<double>::operator=(const double* p)
{
  if ( p ) {
    x = p[0];
    y = p[1];
    z = p[2];
  }
  else {
    x = y = z = 0.0;
  }
  return *this;
}

MnjPoint<double>& MnjPoint<double>::operator=(const MnjVector& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

MnjPoint<double>& MnjPoint<double>::operator*=( double d)
{
  x *= d;
  y *= d;
  z *= d;
  return *this;
}

MnjPoint<double>& MnjPoint<double>::operator/=(double d)
{
  const double one_over_d = 1.0/d;
  x *= one_over_d;
  y *= one_over_d;
  z *= one_over_d;
  return *this;
}

MnjPoint<class T>& MnjPoint<T>::operator+=(const MnjPoint<T>& p)
{
  x += p.x;
  y += p.y;
  z += p.z;
  return *this;
}

MnjPoint<class T>& MnjPoint<class T >::operator+=(const MnjVector& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

MnjPoint<double>& MnjPoint<double>::operator-=(const MnjPoint<double>& p)
{
  x -= p.x;
  y -= p.y;
  z -= p.z;
  return *this;
}

MnjPoint<double>& MnjPoint<double>::operator-=(const MnjVector& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

MnjPoint<double> MnjPoint<double>::operator*( int i ) const
{
  double d = i;
  return MnjPoint<double>(x*d,y*d,z*d);
}

MnjPoint<double> MnjPoint<double>::operator*( float f ) const
{
  double d = f;
  return MnjPoint<double>(x*d,y*d,z*d);
}

MnjPoint<double> MnjPoint<double>::operator*( double d ) const
{
  return MnjPoint<double>(x*d,y*d,z*d);
}

MnjPoint<double> MnjPoint<double>::operator/( int i ) const
{
  const double one_over_d = 1.0/((double)i);
  return MnjPoint<double>(x*one_over_d,y*one_over_d,z*one_over_d);
}
///////////////////////////////////////////////////////
MnjPoint<double> MnjPoint<double>::operator/( float f ) const
{
  const double one_over_d = 1.0/((double)f);
  return MnjPoint<double>(x*one_over_d,y*one_over_d,z*one_over_d);
}
///////////////////////////////////////////////////////////////////
MnjPoint<double> MnjPoint<double>::operator+( const MnjPoint<double>& p ) const
{
  return MnjPoint<double>(x+p.x,y+p.y,z+p.z);
}
////////////////////////////////////////////////////////////////////
MnjVector MnjPoint<double>::operator-( const MnjPoint<double>& p ) const
{
  return MnjVector(x-p.x,y-p.y,z-p.z);
}

/*
MnjPoint<double> MnjPoint::operator-( const MnjVector& v ) const
{
  return MnjPoint<double>(x-v.x,y-v.y,z-v.z);
}
*/
bool MnjPoint<double>::operator==( const MnjPoint<double>& p ) const
{
  return (x==p.x&&y==p.y&&z==p.z)?true:false;
}

bool MnjPoint<double>::operator!=( const MnjPoint<double>& p ) const
{
  return (x!=p.x||y!=p.y||z!=p.z)?true:false;
}

bool MnjPoint<double>::operator<=( const MnjPoint<double>& p ) const
{
  // dictionary order
  return ((x<p.x)?true:((x==p.x)?((y<p.y)?true:(y==p.y&&z<=p.z)?true:false):false));
}

bool MnjPoint<double>::operator>=( const MnjPoint<double>& p ) const
{
  // dictionary order
  return ((x>p.x)?true:((x==p.x)?((y>p.y)?true:(y==p.y&&z>=p.z)?true:false):false));
}

bool MnjPoint<double>::operator<( const MnjPoint<double>& p ) const
{
  // dictionary order
  return ((x<p.x)?true:((x==p.x)?((y<p.y)?true:(y==p.y&&z<p.z)?true:false):false));
}

bool MnjPoint<double>::operator>( const MnjPoint<double>& p ) const
{
  // dictionary order
  return ((x>p.x)?true:((x==p.x)?((y>p.y)?true:(y==p.y&&z>p.z)?true:false):false));
}

double MnjPoint<double>::operator[](int i) const
{
  return ( (i<=0)?x:((i>=2)?z:y) );
}

double& MnjPoint<double>::operator[](int i)
{
  double* pd = (i<=0)? &x : ( (i>=2) ?  &z : &y);
  return *pd;
}

double MnjPoint<double>::DistanceTo( const MnjPoint<double>& p ) const
{
  return (p - *this).Length();
}

int MnjPoint<double>::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? ((fabs(z)>fabs(y))?2:1) : ((fabs(z)>fabs(x))?2:0);
}

double MnjPoint<double>::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z);
  return c;
}

int MnjPoint<double>::MinimumCoordinateIndex() const
{
  return (fabs(y)<fabs(x)) ? ((fabs(z)<fabs(y))?2:1) : ((fabs(z)<fabs(x))?2:0);
}

double MnjPoint<double>::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y); if (fabs(z)<c) c=fabs(z);
  return c;
}

void MnjPoint<double>::Zero()
{
  x = y = z = 0.0;
}


double MnjPoint<double>::operator*(const MnjPoint<double>& h) const
{
  return x*h.x + y*h.y + z*h.z;
}

/*
MnjPoint<double> MnjPoint<double>::operator/( double d ) const
{
  const double one_over_d = 1.0/d;
  return MnjPoint<double>(x*one_over_d,y*one_over_d,z*one_over_d);
}
*/

/*
MnjPoint<double> MnjPoint<double>::operator+( const MnjVector& v ) const
{
  return MnjPoint<double>(x+v.x,y+v.y,z+v.z);
}
*/

/*
MnjPoint<double> MnjPoint<double>::operator+( const ON_2dPoint& p ) const
{
  return MnjPoint<double>(x+p.x,y+p.y,z);
}

MnjPoint<double> MnjPoint<double>::operator+( const ON_2dVector& v ) const
{
  return MnjPoint<double>(x+v.x,y+v.y,z);
}
*/
/*
MnjVector MnjPoint<double>::operator-( const ON_2dPoint& p ) const
{
  return MnjVector(x-p.x,y-p.y,z);
}

MnjPoint<double> MnjPoint<double>::operator-( const ON_2dVector& v ) const
{
  return MnjPoint<double>(x-v.x,y-v.y,z);
}

MnjPoint<double> MnjPoint<double>::operator+( const ON_3fPoint& p ) const
{
  return MnjPoint<double>(x+p.x,y+p.y,z+p.z);
}

MnjPoint<double> MnjPoint<double>::operator+( const ON_3fVector& v ) const
{
  return MnjPoint<double>(x+v.x,y+v.y,z+v.z);
}

MnjVector MnjPoint<double>::operator-( const ON_3fPoint& p ) const
{
  return MnjVector(x-p.x,y-p.y,z-p.z);
}

MnjPoint<double> MnjPoint<double>::operator-( const ON_3fVector& v ) const
{
  return MnjPoint<double>(x-v.x,y-v.y,z-v.z);
}

MnjPoint<double> MnjPoint<double>::operator+( const ON_2fPoint& p ) const
{
  return MnjPoint<double>(x+p.x,y+p.y,z);
}

MnjPoint<double> MnjPoint<double>::operator+( const ON_2fVector& v ) const
{
  return MnjPoint<double>(x+v.x,y+v.y,z);
}

MnjVector MnjPoint<double>::operator-( const ON_2fPoint& p ) const
{
  return MnjVector(x-p.x,y-p.y,z);
}

MnjPoint<double> MnjPoint<double>::operator-( const ON_2fVector& v ) const
{
  return MnjPoint<double>(x-v.x,y-v.y,z);
}
*/


/*
double MnjPoint<double>::operator*(const ON_4dPoint& h) const
{
  return x*h.x + y*h.y + z*h.z + h.w;
}
*/

/*
double MnjPoint<double>::operator*(const MnjVector& h) const
{
  return x*h.x + y*h.y + z*h.z;
}
*/
/*MnjPoint<double> MnjPoint<double>::operator*( const Mnj4x4Matrix& xform ) const
{
  const double px = x; // optimizer should put px,py,pz in registers
  const double py = y;
  const double pz = z;
  double hx[3], w;
  const double* m = &xform.m_xform[0][0];
  hx[0] = m[0]*px + m[4]*py + m[ 8]*pz + m[12];
  hx[1] = m[1]*px + m[5]*py + m[ 9]*pz + m[13];
  hx[2] = m[2]*px + m[6]*py + m[10]*pz + m[14];
  w     = m[3]*px + m[7]*py + m[11]*pz + m[15];
  w = (w != 0.0) ? 1.0/w : 1.0;
  return MnjPoint<double>( w*hx[0], w*hx[1], w*hx[2] );
}
*/
/*	void MnjPoint<double>::Rotate( 
      double angle,               // angle in radians
      const MnjVector& axis,  // axis of rotation
      const MnjPoint<double>& center  // center of rotation
      )
{
  Rotate( sin(angle), cos(angle), axis, center );
}
*/
/*
void MnjPoint<double>::Rotate( s
      double sin_angle,           // sin(angle)
      double cos_angle,           // cos(angle)
      const MnjVector& axis,  // axis of rotation
      const MnjPoint<double>& center  // center of rotation
      )
{
  Mnj4x4Matrix rot;
  rot.Rotation( sin_angle, cos_angle, axis, center );
  Transform(rot);
}
*/


//////////////////////////////////////////////////////////////////////


