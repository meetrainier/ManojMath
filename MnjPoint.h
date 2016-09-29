#pragma once
//copyright(c) 2009- 2016 Manoj Lnu 
/*
class Point {
public:
	Point() {
	}
	Point(float a, float b, float c) {
		x = a; y = b ; z = c;
	}
			float x, y, z;		// Point coordinates
} ;
*/
#include <iostream>
#include <vector>
#include <iostream>
class MnjVector;

using namespace std;

template <class T>    
class MnjPoint     
 {

	public:
		 double x,y,z;
		
		MnjPoint() {
			x = 0;
			y = 0;
			z = 0;
		}

		MnjPoint(T a, T b, T c) {
			x = a; y = b ; z = c;
		}
    
    /////////////////////////Here new stuff 
    void Set(T &a,T &b,T &c){
			x = a; y = b; z = c;
		}

		void SetX(T &a){
			x = a;
		}
		void SetY(T &a){
			y = a;
		}
		void SetZ(T &a){
			z = a;
		}

		/*
		MnjPoint<T> operator+(MnjVector &vec){
			return MnjPoint(x+vec.x,y+vec.y,z+vec.z); 
		}
		*/
		//MnjPoint<class T>& operator+(MnjVector &p);

		//major
    
    MnjPoint(const MnjVector& v);

    //MnjPoint();

    MnjPoint( const float* p );

    MnjPoint( const double* p );

//  MnjPoint(double xx,double yy,double zz);
    MnjPoint(const MnjPoint<double> &ip);
//MnjPoint operator*( const Mnj4x4Matrix& xform ) const;
    static const MnjPoint Origin;     // (0.0,0.0,0.0)
    static const MnjPoint UnsetPoint; //uses macros meant for unset values 

int MaximumCoordinateIndex() const;
MnjPoint<double>& operator=(const float* p);

MnjPoint<double>& operator=(const double* p);


MnjPoint<double>& operator=(const MnjVector& v);
MnjPoint& operator*=(double d);
//MnjPoint& operator*=(int d);

MnjPoint<double>& operator/=(double d);

MnjPoint& operator+=(const MnjPoint& p);

MnjPoint& operator+=(const MnjVector& v);

MnjPoint& operator-=(const MnjPoint& p);

MnjPoint& operator-=(const MnjVector& v);

MnjPoint operator*( int i ) const;
MnjPoint operator*( float f ) const;
MnjPoint operator*( double d ) const;
double operator*(const MnjPoint& h) const;
double operator*(const MnjVector& h) const;

MnjPoint operator/( int i ) const;

MnjPoint operator/( float f ) const;
MnjPoint operator+( const MnjPoint& p ) const;
MnjVector operator-( const MnjPoint& p ) const;

MnjPoint operator-( const MnjVector& v ) const;
bool operator==( const MnjPoint& p ) const;

bool operator!=( const MnjPoint& p ) const;

bool operator<=( const MnjPoint& p ) const;

bool operator>=( const MnjPoint& p ) const;

bool operator<( const MnjPoint& p ) const;

bool operator>( const MnjPoint& p ) const;

  double operator[](int i) const;

  double& operator[](int i);
  //operator double*();

  //operator const double*() const;
  double DistanceTo( const MnjPoint& p ) const;

  //int MaximumCoordinateIndex() const;

  double MaximumCoordinate() const;

  int MinimumCoordinateIndex() const;

  double MinimumCoordinate() const;

  void Zero();

		//MnjPoint<class T>& operator+(MnjVector &p);
#ifdef _DEBUG 
		void Print()const{
		   cout << x <<"\t" << y <<"\t"<< z << endl; 
	    }
#endif
		
		
};

template <class T> 
void print(MnjPoint<T> &point){
	cout << point.x << "\t" << point.y  <<"\t"<< point.z << endl;
}
template <class T> 
void PrintPointVector(std::vector<MnjPoint<T>> &pointVec){
	
	std::vector<MnjPoint>::iterator it;
	for (it = pointVec.begin(); it != pointVec.end(); it++  ) {
	  print(*it);
	}
}


/*
class MnjPoint {

	public:
		MnjPoint() {
		}
		MnjPoint(float a, float b, float c) {
			x = a; y = b ; z = c;
		}
		MnjPoint(double ix, double iy , double iz);

		MnjPoint& operator+(MnjPoint &p);
		float x, y, z;		// Point coordinates
		void Print(){
		   cout << x <<"\t" << y <<"\t"<< z << endl; 
	   }
} ;


MnjPoint::MnjPoint(double ix, double iy , double iz){
  x = ix; y = iy ; z = iz;
}

MnjPoint& MnjPoint::operator+(MnjPoint &p){
			  this->x = this->x + p.x;
			  this->y = this->y + p.y;
			  this->z = this->z + p.z;
			  return *this;
}
*/


/////////////////////////////////////////////////////////////////////////
