#pragma once
//copyright(c) 2009- 2016 Manoj Lnu 
#include "MnjArc.h"
#include "MnjPoint.h" 
#include "MnjInfiniteLine.h"
//standard
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


//void GetPointOnCircle(double &r,std::vector<double> &angleVec, std::vector<MnjPoint> &pointVec);
template <class T>  
void GetPointOnCircle(double &r,std::vector<double> &angleVec, std::vector<MnjPoint<T>> &pointVec);
/*
If the point in pointVec was (0,0,0 ), it will transform to the coordinate of the point  
*/
template <class T>
void MoveCoordinates(MnjPoint<T> &point, std::vector<MnjPoint<T>> &pointVec, std::vector<MnjPoint<T>> &opointVec);


/*

class MnjCircle{
public:
	MnjCircle(MnjArc &arc);
    void GetCenter(MnjPoint<double> &oc)const;
	void Intersect(const MnjInfiniteLine &l,MnjPoint<double> op1,MnjPoint<double> op2)const{}
private:
	MnjPoint<double> mcenter;
	double r;
};
*/
#pragma once
#include <memory> 
#include "MnjArc.h"
#include "MnjPoint.h"
#include "MnjPlane.h"
#include "MnjLine.h"
#include "MnjVector.h"
#include "MnjOperators.h"
#include "GeomUtils.h" 
#include "MnjInfiniteLine.h"

using namespace std; 

class  MnjCircle
{
public:
	
	MnjCircle( const MnjArc& a );
    MnjCircle( const shared_ptr<MnjArc> a );
    MnjCircle( const MnjPlane& p, double r );
    bool Create( const MnjPlane& p, double r );

    void SetRadius(double &r);
    double Radius() const;
    const MnjPoint<double>& Center() const;
    MnjPoint<double> PointAt( double t ) const;

	  // circle is in the plane with center at plane.m_origin.
	MnjPoint<double> ClosestPointTo( const MnjPoint<double>& point ) const;
//////////////////////////////////////////////////////////////////////////////
	int Intersect(MnjInfiniteLine &il, shared_ptr_vec_pt &opt_vec);
        
int Intersect(
      const MnjLine& line, 
      double* line_t0,
      MnjPoint<double>& circle_point0,
      double* line_t1,
      MnjPoint<double>& circle_point1
      );

   int Intersect(MnjCircle &ic, shared_ptr_vec_pt &opt_vec);
   MnjPlane Plane(){
       return MnjPlane(mplane);
   }

   MnjVector GetXAxis(){
       return MnjVector(mplane.xaxis);
   }

   MnjVector GetYAxis(){
       return MnjVector(mplane.yaxis);
   }
   MnjVector GetZAxis(){
       return MnjVector(mplane.zaxis);
   }
	//////////////////////////////////////////////////////////////////////////////
  MnjPlane   mplane;  
  double     mradius;   // radius

};