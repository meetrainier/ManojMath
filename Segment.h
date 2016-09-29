//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
//2016/09/29: Manoj: Some member function were made const
#pragma once
//#include "icspath.h"
#include <vector>
#include <list>
#include <memory>

#include "MnjPoint.h"

using namespace std; 
/*
Exaansion note: 
Ideally a class SmoothableSegment should be derived from Segment. 
The data-member SegmentChange and CornerAttribute should be moved to the new  SmoothableSegemnt class.

*/
class Segment {

public:

  typedef shared_ptr<Segment> shared_ptr;// postponing change of this "typedef" to "using"  
  					//since no compilation facilityis currently available.
	
	using shared_ptr_vec  = vector<std::shared_ptr<Segment>> ;
        using shared_ptr_vec_it = vector<std::shared_ptr<Segment>>::iterator ;
    
	using shared_ptr_list = list<std::shared_ptr<Segment>> ;
	using shared_ptr_list_it = list<std::shared_ptr<Segment>>::iterator ;
  ///////////////////////////////////////////////////////////////////////////////////////////////
  enum  SegmentChange{UNKNOWN, //default value ( if constructor argument doesn't specify anything) 
                       ORIGINAL,//No change took place. 
                       MODIFIED,//A segment just before or after an inserted arc. 
                       MERGED,//only appears in small segments case, the segment came into existence by merging 
                              // two smaller segment
                       NEW,//a new segment came into existence, the segment must be after a segment marked as corner == true
                       MERGED_MODIFIED,//segment came into existence by merging  two smaller segments, later 
                                        //end points were modified. usually modification is required to satisfy tangent criterion. 
                       SKIPPED};        // It is not passible to insert arc at this point.
                                       // only a corner point segment can be assigned this value. 
   //////////////////////////////////////////////////////////////////////////////////////////
  enum  CornerAttribute{
                       NEXT_TANGENT_NOT_NEEDED, // A corner was specified but the request was redundant. 
                                         //There was already c1 continuity at the corner im the forward direction
                       PREV_TANGENT_NOT_NEEDED, // A corner was specified but the request was redundant. 
                                         //There was already c1 continuity at the corner in the backward direction.
                       NEXT_PREV_TANGENT_NOT_NEEDED, // A corner was specified but the request was redundant. 
                                         //There was already c1 continuity at the corner in both directions.
                      
                      };

    ///////////////////////////////////////////////////////////////////
  virtual void GetStartPoint(MnjPoint<double> &p) const=0 ;
  virtual void GetEndPoint(MnjPoint<double> &p)const=0 ;
  virtual void GetEnds(MnjPoint<double> &s,MnjPoint<double> &e)const=0 ;
  virtual double GetMaxDistance(MnjPoint<double> &p)const=0;// do we really need it?
  virtual  MnjPoint<double> Segment::GetCommonPoint(std::shared_ptr<Segment> seg2,int &oerror);
  virtual MnjPoint<double> GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const=0;
   //virtual SegmentType GetType()=0;

   //virtual bool IsSameGeometry(boost::shared_ptr<Segment> s,double &tol)=0;
#if _DEBUG
   virtual void Print(void)const=0;
#endif 
  // virtual void GetEdge(EDGE *&e)=0;
   bool operator<(Segment &s){
	   MnjPoint<double>  p1;
	   s.GetStartPoint(p1);
	   MnjPoint<double>  p;
	   GetStartPoint(p);
	   return p.x < p1.x;
   }

   bool operator<(Segment *s){
	   MnjPoint<double>  p1;
	   s->GetStartPoint(p1);
	   MnjPoint<double>  p;
	   GetStartPoint(p);
	   return p.x < p1.x;
   }

   bool operator==(Segment &s){
	   MnjPoint<double>  p1;
	   s.GetStartPoint(p1);
	   MnjPoint<double>  p;
	   GetStartPoint(p);
	   return (p.x == p1.x && p.y == p1.y  && p.z == p1.z );
   }

   bool operator==(Segment *s){
	   MnjPoint<double>  p1;
	   s->GetStartPoint(p1);
	   MnjPoint<double>  p;
	   GetStartPoint(p);
	   return (p.x == p1.x && p.y == p1.y  && p.z == p1.z );
   }
private: 
	int color;
	char *amassmn;
};




