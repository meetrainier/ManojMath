#pragma once 
//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
//9/29/2016 : Manoj : Print is a const method now. 
#include <memory> 
#include "MnjPoint.h"
#include "Segment.h"
#include "GeomUtils.h"
#include "MnjDirection.h"
using namespace std; 
class ICSAttribute {
	// feel free to replace the data-members.
	//just a place holder
public:
    ICSAttribute(){
        mSegProp  = SEG_UNKNOWN;
    }
  int color;

  enum ICSSegProperty {SEG_SCRIBE,SEG_UNKNOWN} ;
  bool hasSpecialFeature;
  
  void SetSegProp(ICSSegProperty iprop){mSegProp=iprop;}
  ICSSegProperty GetSegProp(void){return mSegProp;}
  bool IsScribe(){
      return SEG_SCRIBE == GetSegProp();
  }

private:
  ICSSegProperty mSegProp;

};
////////////////////////////////////////////////////////////////////////////////////////////////////

class MnjSmoothableSegment:public Segment  {

public:
  typedef std::shared_ptr<MnjSmoothableSegment> shared_ptr;
	
	typedef vector<std::shared_ptr<MnjSmoothableSegment>> shared_ptr_vec;
	typedef vector<std::shared_ptr<MnjSmoothableSegment>>::iterator shared_ptr_vec_it;
    
	typedef list<std::shared_ptr<MnjSmoothableSegment>> shared_ptr_list;
	typedef list<std::shared_ptr<MnjSmoothableSegment>>::iterator shared_ptr_list_it;
  
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
    enum  CornerAttribute{
                       NEXT_TANGENT_NOT_NEEDED, // A corner was specified but the request was redundant. 
                                         //There was already c1 continuity at the corner im the forward direction
                       PREV_TANGENT_NOT_NEEDED, // A corner was specified but the request was redundant. 
                                         //There was already c1 continuity at the corner in the backward direction.
                       NEXT_PREV_TANGENT_NOT_NEEDED, // A corner was specified but the request was redundant. 
                                         //There was already c1 continuity at the corner in both directions.
                      
                      };

    enum ProcessingState{//valid for corner segment only , relevant for small segment case only
        NEXT_PROCESSED,//this segment has been processed in a next loop for merge, if it was needed
        PREV_PROCESSED,//It has been processed in a prev loop for merge, if it was needed
        PROCESSED, //this segment has been processed in both directions.
        UNPROCESSED
    };

    int SetICSAttribute(shared_ptr seg1,shared_ptr seg2);
    int MergeAndSetAttributes(shared_ptr iSeg1,shared_ptr iSeg2,
                                         MnjSmoothableSegment::SegmentChange iStatus);
    virtual std::shared_ptr<Segment> GetSegment(void)=0;
    ////////////////////////////////////////////////////////////////////
    bool  IsNextRelevant(void) {
        return !( NEXT_PREV_TANGENT_NOT_NEEDED == mCornerAttr || NEXT_TANGENT_NOT_NEEDED == mCornerAttr) ;
    }
    /////////////////////////////////////////////////////////////////////////
    bool  IsPrevRelevant(void) {
        return !( NEXT_PREV_TANGENT_NOT_NEEDED == mCornerAttr || PREV_TANGENT_NOT_NEEDED == mCornerAttr) ;
    }
    ///////////////////////////////////////////////////////////////////////
    bool IsRelevantCorner(void){
        return IsCorner() && (NEXT_PREV_TANGENT_NOT_NEEDED != mCornerAttr); 
    }
    ///////////////////////////////////////////////////////////////////////
    CornerAttribute  GetCornerAttribute(void) {
        return mCornerAttr;
    }
    ///////////////////////////////////////////////////////////////////
    bool IsTangent(const std::shared_ptr<MnjSmoothableSegment> iSeg);
     ///////////////////////////////////////////////////////////////////
	MnjSmoothableSegment(){
	 corner=0;
	 cornerRadius=0;
     mpstate = UNPROCESSED;
	}
   //Virtual Methods ///////////////////////////////////////////////////
	virtual void SetStartPoint(MnjPoint<double> &p){
     //throw error : not implemented;       
   }
   virtual void SetEndPoint(MnjPoint<double> &p){
     //throw error : not implemented;       
   }
   virtual double GetMergeParameter() const { //throw error : not implemented;       
     double d = GetCornerRadius();
	 return d;
   }
   virtual double GetCharacteristic() const { //throw error : not implemented;    
	   return 0;
   }
   /////////////////////////////////////////////////////////////////////
   /* mnj useless
   virtual void Set(const MnjSmoothableSegment &seg1,const MnjSmoothableSegment &seg2){
	   //throw error : not implemented;       

   }
   */
   virtual int Partition(const unsigned int &n, list<std::shared_ptr<MnjSmoothableSegment>> &ol) = 0;
   /////////////////////////////////////////////////////
   virtual MnjPoint<double> GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const=0;
   /////////////////////////////////////////////////////
   void SetICSAttribute(const ICSAttribute& iattr){
       mattr = iattr;
   }
   void GetICSAttribute(ICSAttribute& oattr)const{
	   oattr = mattr;
   }

   double GetCornerRadius()const{
     return cornerRadius;
   }
   
   bool IsCorner()const{
     return corner;
   }

   inline int SetCornerRadius(const double &r){
      int error = 0; 
      if(r>0.0 ){ 
        cornerRadius=r;
        SetCorner(true);
      } else { 
          error = -1;
      }

      return error ;
   }
   
   inline void SetCorner(const bool b){
     corner=b;
   }

   virtual int ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip){ return -1;}
    /////////////////////////////////////////////////////////////////////////////////
   virtual void Flip(void){};
   virtual MnjDirection TangentAtEnd(MnjPoint<double> &p)=0;
   //////////////////////////////////////////////////////////////////////////////////
   MnjPoint<double> GetCommonPoint(std::shared_ptr<MnjSmoothableSegment> seg2, int &oerror);
   /////////////////////////////////////////////////////////////
   int GetExtermeEnds(const std::shared_ptr<MnjSmoothableSegment> &iSeg, MnjPoint<double> &oex1,
                                                  MnjPoint<double> &oex2){
          int error = 0;
          MnjPoint<double> commonPoint = GetCommonPoint(iSeg,error);
          if(error>=0){
             oex1 = GetOtherEnd(commonPoint,error);
             if(error>=0){
                oex2 = iSeg->GetOtherEnd(commonPoint,error);
             }
          }
          return error;
   }
   //////////////////////////////////////////////////////////
   void SetStatus(SegmentChange iStatus){
        mstatus = iStatus;
    }

   void SetProcessingState (ProcessingState iState){
        mpstate = iState;
    }
   public :SegmentChange Status()const {
        return mstatus;
    }

    public :ProcessingState GetProcessingState()const {
        return mpstate;
    }

  

    void SetCornerAttribute(const CornerAttribute iAttr) {
        if(mCornerAttr==NEXT_TANGENT_NOT_NEEDED && iAttr == PREV_TANGENT_NOT_NEEDED){
            mCornerAttr = NEXT_PREV_TANGENT_NOT_NEEDED;
            return;
        }
        if(mCornerAttr==PREV_TANGENT_NOT_NEEDED && iAttr == NEXT_TANGENT_NOT_NEEDED){
            mCornerAttr = NEXT_PREV_TANGENT_NOT_NEEDED;
            return;
        }
        mCornerAttr = iAttr;
    }
    bool IsScribe(void);
    
    
  void SetSegProp(ICSAttribute::ICSSegProperty iprop){mattr.SetSegProp(iprop);}
#if _DEBUG
   virtual void Print(void)const=0;
#endif 
private: 
    CornerAttribute mCornerAttr; 
	ICSAttribute mattr;
	bool corner;
	double cornerRadius;
	int cornerflag;// 0: No analysis was made. The normal inout value
	               // 1: Indicates it is impossible to create and arc at this point with given radius and C1 continuity.   
	               //    Normally the value 1 will be assigned by CreateArcs() method. 
  protected:
    SegmentChange mstatus;
    ProcessingState mpstate;  
};