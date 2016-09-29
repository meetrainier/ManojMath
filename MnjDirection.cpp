//copyright(c) 2009- 2016 Manoj Lnu 
#include "MnjDirection.h"
//#include "MnjDirection.h"
MnjDirection::MnjDirection(const MnjVector &v){
		double  m = v.magnitude();
		 x = v.x/m;
		 y = v.y/m;
		 z = v.z/m;
}

MnjVector MnjDirection::operator*(const double r) const{
		return MnjVector(r*x,r*y,r*z);
}

MnjDirection MnjDirection::CrossProduct( const MnjDirection &vec){
	      MnjVector temp;
	      temp.x = y*vec.z - z*vec.y;
	      temp.y = z*vec.x - x*vec.z;
	      temp.z = x*vec.y - y*vec.x;

	        return MnjDirection(temp.x ,temp.y ,temp.z );
		}
///////////////////////////////////////////////////////////////////////
 bool MnjDirection::IsObtuse(const MnjDirection &p){
     return this->DotProduct(p) < 0.0 && !(this->IsPerpendicularTo(p)); 
 }
////////////////////////////////////////////////////////
 bool MnjDirection::IsAcute(const MnjDirection &p){
     return ( (this->DotProduct(p) > 0.0  )  && 
              !(this->IsPerpendicularTo(p))
            ); 
 }
////////////////////////////////////////////////////////
 bool MnjDirection::IsPerpendicularTo(const MnjDirection &p){
     MnjVector vec(*this); 
     return vec.IsPerpendicularTo(p);
 }
 //////////////////////////////////////////////////////////////
double MnjDirection::DotProduct( const MnjDirection &vec){
			double val;
			val = 0.0;
			val = x * vec.x +  y * vec.y +  z * vec.z;

			return val;
  }
///////////////////////////////////////////////////////////////////////////
 MnjDirection MnjDirection::GetDirectionAlong(const MnjDirection &iDir){

		   if(DotProduct(iDir) > 0){
			   return MnjDirection(x,y,z);
		   }else{
			    return MnjDirection(-x,-y,-z);
		   }
}