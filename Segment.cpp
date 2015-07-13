#include <memory>
#include "Segment.h"   
#include "GeomUtils.h"   
using namespace std; 

MnjPoint<double> Segment::GetCommonPoint(std::shared_ptr<Segment> seg2,int &oerror){
      MnjPoint<double> s1,e1,s2,e2;
      GetEnds(s1,e1);
      seg2->GetEnds(s2,e2);
      if(   GeomUtils::IsSame(s1,s2) || GeomUtils::IsSame(s1,e2) ) {
        return MnjPoint<double>(s1); 
      }
      else if ( GeomUtils::IsSame(e1,s2) || GeomUtils::IsSame(e1,e2) ) {
        return MnjPoint<double>(e1); 
      }else {
        oerror = -1;
     }
     return MnjPoint<double>();
  }