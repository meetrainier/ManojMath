#pragma once 
#include <iostream>
#include "MnjPoint.h"
#include "MnjVector.h"
#include "MathConstant.h"

using namespace std;
class MnjVector;
class MnjDirection;

class MnjVector {

public:
		double x,y,z;
        
  static const MnjVector ZeroVector;  // (0.0,0.0,0.0)
  static const MnjVector XAxis;       // (1.0,0.0,0.0)
  static const MnjVector YAxis;       // (0.0,1.0,0.0)
  static const MnjVector ZAxis;       // (0.0,0.0,1.0)
  static const MnjVector UnsetVector; // (MNJ_UNSET_VALUE,MNJ_UNSET_VALUE,MNJ_UNSET_VALUE)
		MnjVector() {}

	    MnjVector( const MnjPoint<double> &p); 

        MnjVector( const MnjVector &p); 
		MnjVector(double a, double b, double c); 
		
		MnjVector(const MnjPoint<double> &s,const MnjPoint<double> &e);
        MnjVector(const MnjDirection &i);
	
#if  _DEBUG 
		void Print(){
		   cout << x <<"\t" << y <<"\t"<< z << endl; 
	    }
#endif 

		double magnitude(void)const;

        MnjVector operator+(const MnjVector &p);
		MnjVector operator-(const MnjVector &p);
		MnjVector operator*(const double r) const;

     	 double DotProduct( const MnjVector &vec);
        /*{
			double val;
			val = 0.0;
			val = x * vec.x +  y * vec.y +  z * vec.z;

			return val;
        }*/

		 MnjVector CrossProduct( const MnjVector &vec);/*{
	      MnjVector temp;
	      temp.x = y*vec.z - z*vec.y;
	      temp.y = z*vec.x - x*vec.z;
	      temp.z = x*vec.y - y*vec.x;

	        return MnjVector(temp.x,temp.y,temp.z);
		}
        */
		//major append
        static const MnjVector& UnitVector(
    int // index
    );

  // use implicit destructor, copy constructor
//  MnjVector();                     // x,y,z not initialized
//  MnjVector(double x,double y,double z);
  //MnjVector(const ON_2dVector& );  // from 2d vector
  //MnjVector(const ON_2dPoint& );   // from 2d point
  MnjVector(const double*);        // from double[3] array

  //MnjVector(const ON_2fVector& );  // from 2f vector
  //MnjVector(const ON_3fVector& );  // from 3f vector
  //MnjVector(const ON_2fPoint& );   // from 2f point
  //MnjVector(const ON_3fPoint& );   // from 3f point
  MnjVector(const float*);         // from float[3] array

//  MnjVector(MnjDirection &i);
  // (double*) conversion operators
  operator double*();
  operator const double*() const;

  // use implicit operator=(const MnjVector&)
  //MnjVector& operator=(const ON_2dVector&);
  //MnjVector& operator=(const ON_2dPoint&);
  MnjVector& operator=(const MnjPoint<double>&);
  MnjVector& operator=(const double*); // vector = double[3] support
  
  //MnjVector& operator=(const ON_2fVector&);
  //MnjVector& operator=(const ON_3fVector&);
  //MnjVector& operator=(const ON_2fPoint&);
  //MnjVector& operator=(const ON_3fPoint&);
  MnjVector& operator=(const float*);  // vector = float[3] support

  MnjVector  operator-() const;

  MnjVector& operator*=(double);
  MnjVector& operator/=(double);
  MnjVector& operator+=(const MnjVector&);
  MnjVector& operator-=(const MnjVector&);
  // DO NOT ADD ANY MORE overrides of += or -=

  double operator*(const MnjVector&) const; // inner (dot) product
  double operator*(const MnjPoint<double>&) const; // inner (dot) product
  //double operator*(const ON_3fVector&) const; // inner (dot) product

 // MnjVector  operator*(int) const;
  MnjVector  operator/(int) const;
  MnjVector  operator*(float) const;
  MnjVector  operator/(float) const;
  MnjVector  operator/(double) const;

  MnjVector  operator+(const MnjVector&) const;
  MnjPoint<double>   operator+(const MnjPoint<double>&) const;
  MnjVector  operator-(const MnjVector&) const;
  MnjPoint<double>   operator-(const MnjPoint<double>&) const;
  //MnjVector  operator+(const ON_2dVector&) const;
  //MnjPoint   operator+(const ON_2dPoint&) const;
  //MnjVector  operator-(const ON_2dVector&) const;
  //MnjPoint   operator-(const ON_2dPoint&) const;

  //MnjVector  operator+(const ON_3fVector&) const;
  //MnjPoint   operator+(const ON_3fPoint&) const;
  //MnjVector  operator-(const ON_3fVector&) const;
  //MnjPoint   operator-(const ON_3fPoint&) const;
  //MnjVector  operator+(const ON_2fVector&) const;
  //MnjPoint   operator+(const ON_2fPoint&) const;
  //MnjVector  operator-(const ON_2fVector&) const;
  //MnjPoint   operator-(const ON_2fPoint&) const;

  //double operator*(const ON_4dPoint&) const;
  //MnjVector operator*(const Mnj4x4Matrix&) const;

  bool operator==(const MnjVector&) const;
  bool operator!=(const MnjVector&) const;

  // dictionary order comparisons
  bool operator<=(const MnjVector&) const;
  bool operator>=(const MnjVector&) const;
  bool operator<(const MnjVector&) const;
  bool operator>(const MnjVector&) const;

  // index operators mimic double[3] behavior
  double& operator[](int);
  double operator[](int) const;

 
  //Returns:
   // False if any coordinate is infinte, a nan, or MNJ_UNSET_VALUE.
  bool IsValid() const;

  //Returns:
    //True if every coordinate is MNJ_UNSET_VALUE.
 
  bool IsUnsetVector() const;

  // set 3d vector value
  void Set(double x,double y,double z);

  int MaximumCoordinateIndex() const;
  double MaximumCoordinate() const; // absolute value of maximum coordinate

  int MinimumCoordinateIndex() const;
  double MinimumCoordinate() const; // absolute value of minimum coordinate

  double LengthSquared() const;
  double Length() const;

  bool Decompose( // Computes a, b, c such that this vector = a*X + b*Y + c*Z
         // Returns false if unable to solve for a,b,c.  This happens
         // when X,Y,Z is not really a basis.
         //
         // If X,Y,Z is known to be an orthonormal frame,
         // then a = V*X, b = V*Y, c = V*Z will compute
         // the same result more quickly.
         const MnjVector&, // X
         const MnjVector&, // Y
         const MnjVector&, // Z
         double*, // a
         double*, // b
         double*  // c
         ) const;

  int IsParallelTo( 
        // returns  1: this and other vectors are parallel
        //         -1: this and other vectors are anti-parallel
        //          0: this and other vectors are not parallel
        //             or at least one of the vectors is zero
        const MnjVector& other,                           // other vector     
        double angle_tolerance = MNJ_DEFAULT_ANGLE_TOLERANCE // optional angle tolerance (radians)
        ) const;

  bool IsPerpendicularTo(
        // returns true:  this and other vectors are perpendicular
        //         false: this and other vectors are not perpendicular
        //                or at least one of the vectors is zero
        const MnjVector& other,                           // other vector     
        double angle_tolerance = MNJ_DEFAULT_ANGLE_TOLERANCE // optional angle tolerance (radians)
        ) const;

  double Fuzz( double tolerance = MNJ_ZERO_TOLERANCE ) const; // tolerance to use when comparing 3d vectors

  void Zero(); // set all coordinates to zero;
  void Reverse(); // negate all coordinates
  bool Unitize();  // returns false if vector has zero length
  double LengthAndUnitize(); // unitizes and returns initial length

  // Description:
  //   Test a vector to see if it is very short
  //
  // Parameters:
  //   tiny_tol - [in] (default = ON_ZERO_TOLERANCE) a nonzero
  //              value used as the coordinate zero tolerance.
  //
  // Returns:
  //   ( fabs(x) <= tiny_tol && fabs(y) <= tiny_tol && fabs(z) <= tiny_tol )
  //
  bool IsTiny(
         double tiny_tol = MNJ_ZERO_TOLERANCE // tiny_tol
         ) const;

  // Returns:
  //   true if vector is the zero vector.
  bool IsZero() const;

  // Returns:
  //   true if vector is valid and has length 1.
  bool IsUnitVector() const;

  // set this vector to be perpendicular to another vector
  bool PerpendicularTo( // Result is not unitized. 
                        // returns false if input vector is zero
        const MnjVector& 
        );

  // set this vector to be perpendicular to a plane defined by 3 points
  bool PerpendicularTo(
               // about 3 times slower than
               //    MnjVector N = FlowCrossProduct(P1-P0,P2-P0); 
               //    N.Unitize();
               // returns false if points are coincident or colinear
         const MnjPoint<double>&, const MnjPoint<double>&, const MnjPoint<double>& 
         );

  // These transform the vector in place. The transformation matrix acts on
  // the left of the vector; i.e., result = transformation*vector
  //void Transform( 
   //     const Mnj4x4Matrix& // can use Mnj4x4Matrix here
    //    );

  void Rotate( 
        double angle,           // angle in radians
        const MnjVector& axis // axis of rotation
        );

  void Rotate( 
        double sin_angle,        // sin(angle)
        double cos_angle,        // cos(angle)
        const MnjVector& axis  // axis of rotation
        );
 
  bool IsObtuse(const MnjVector &p);
////////////////////////////////////////////////////////
  bool IsAcute(const MnjVector &p);
////////////////////////////////////////////////////////

};


/*
#include <iostream>
#include "MnjPoint.h"

using namespace std;

class MnjVector {

public:
		double x,y,z;
		
		MnjVector() {
		}

		MnjVector(double a, double b, double c) {
			x = a; y = b ; z = c;
		}

		MnjVector(const MnjPoint<double> &p) {
		    x = p.x; 
			y = p.y; 
			z = p.z;
		}
#if  _DEBUG 
		void Print(){
		   cout << x <<"\t" << y <<"\t"<< z << endl; 
	    }
#endif 

		double magnitude(void){
		   return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
		
		}
		MnjVector operator+(MnjVector &p);
		MnjVector operator-(MnjVector &p);
		
		
};
*/
