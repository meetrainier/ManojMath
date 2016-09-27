#pragma once
/*
07/12/2012: Bugfix: MnjDirection cnstr that takes three double will behave correctly when magnitude is 0. 
09/27/2016: manoj : Increased use of "auto"

*/
#include "MnjVector.h"
#include "MnjPoint.h"

class MnjDirection { 
	public:
		 double x,y,z;
	//must normalize 
	 MnjDirection(){};

   	MnjDirection(const MnjPoint<double> &s,const MnjPoint<double> &e){
		auto x1= e.x - s.x;
		auto y1= e.y - s.y;
		auto z1= e.z - s.z;
		auto  m = sqrt(pow(x1,2)+pow(y1,2)+pow(z1,2));
		 x = x1/m;
		 y = y1/m;
		 z = z1/m;
		}

	MnjDirection(double x1, double y1, double z1){
	
    decltype(x1)  m = sqrt(pow(x1,2)+pow(y1,2)+pow(z1,2));
		if(0.0!=m){
		  x = x1/m;
		  y = y1/m;
		  z = z1/m;
		}else { 
      x= y = z = 0.0;
		}
	
  }

	 MnjDirection(const MnjVector &v);
	 MnjVector operator*(const double r) const;
	 
   void Set(const MnjPoint<double> &s,const MnjPoint<double> &e){
			
     auto x1 = e.x - s.x;
		 auto y1 = e.y - s.y;
		 auto z1 = e.z - s.z;
		 auto  m = sqrt(pow(x1,2)+pow(y1,2)+pow(z1,2));
		 
     x = x1/m;
		 y = y1/m;
		 z = z1/m;

		}

   ////////////////////////////////////////////////////////
   bool IsObtuse(const MnjDirection &p);
   ////////////////////////////////////////////////////////
   bool IsAcute(const MnjDirection &p);
   ////////////////////////////////////////////////////////
   bool IsPerpendicularTo(const MnjDirection &p);
	 ////////////////////////////////////////////////////////
	 inline double Angle(MnjDirection &dir){

	     MnjDirection Z=(*this).CrossProduct(dir);
	     MnjDirection Y=Z.CrossProduct(*this);
    
	     auto x = dir.DotProduct(*this);
	     auto y = dir.DotProduct(Y);
	     int factor = 1;
		   if(Z.z < 0 ) factor = -1; 
		   auto angle = atan2(y,x);
		   angle = factor*angle;
	     
       if(angle < 0 ) {
		     angle = angle + 2*M_PI;
	     }

	     return angle;
	  }
   
   ////////////////////////////////////////////////////////
    double DotProduct( const MnjDirection &vec);
   ////////////////////////////////////////////////////////
   MnjDirection CrossProduct( const MnjDirection &vec);
   ////////////////////////////////////////////////////////
   MnjDirection GetDirectionAlong(const MnjDirection &iDir);
   ////////////////////////////////////////////////////////
   MnjVector operator*(double r){
		 return MnjVector(r*x,r*y,r*z);
	}

};
