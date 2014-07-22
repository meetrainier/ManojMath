#pragma once
#include "MnjPoint.h"
#include "MnjSmoothableSegment.h"
#include "MnjLine.h"
#include "MnjArc.h"
#include "MnjSmoothableLine.h"
//class FlowICSLine;

class MnjSmoothableArc: public MnjSmoothableSegment {

public:
	MnjSmoothableArc() { SetStatus(MnjSmoothableSegment::UNKNOWN);} 
	//MnjSmoothableArc(FlowSegment &iSeg1, FlowSegment &iSeg2);
	//MnjSmoothableArc(FlowSegment *iSeg1, FlowSegment *iSeg2);
	MnjSmoothableArc(MnjPoint<double> &ip1, MnjPoint<double> &center,
                   MnjPoint<double> &ip2//,ICSAttribute &iattr 
               );
    
    MnjSmoothableArc(MnjArc &iarc );//, ICSAttribute &iattr);
    
    MnjSmoothableArc(const boost::shared_ptr<MnjSmoothableArc> &iSeg1, 
                     const boost::shared_ptr<MnjSmoothableArc> &iSeg2,
                //ICSAttribute &iAttr,
                MnjSmoothableSegment::SegmentChange iStatus);
    //////////////////////////////////////////////////////////////////////////////////////
    MnjSmoothableArc(const MnjSmoothableLine::shared_ptr&iSeg1, 
                     const boost::shared_ptr<MnjSmoothableArc> &iSeg2,
                         //ICSAttribute &iAttr,
                         MnjSmoothableSegment::SegmentChange iStatus);
    
    MnjSmoothableArc(const boost::shared_ptr<MnjSmoothableArc> &iSeg1, 
                     const MnjSmoothableLine::shared_ptr&iSeg2,
                         //ICSAttribute &iAttr,
                         MnjSmoothableSegment::SegmentChange iStatus);

     //MnjSmoothableArc(const boost::shared_ptr<MnjSmoothableArc> &iSeg1, const boost::shared_ptr<MnjSmoothableArc> &iSeg2,
       //                  ICSAttribute &iAttr,MnjSmoothableSegment::SegmentChange iStatus);
    /////////////////////Set attrbutes/////////////////////////////
    boost::shared_ptr<MnjArc> GetArc(int dummy)const;
    boost::shared_ptr<Segment> GetSegment(void);

    int Set(MnjPoint<double> &s,MnjPoint<double> &c,MnjPoint<double> &e);
    int SetSmallerArc(MnjPoint<double> &e1,MnjPoint<double> &c,MnjPoint<double> &e2);
	  void SetArc(MnjArc &a) {
		  marc = a;
	  }

	  void SetCenter(MnjPoint<double> &p);
    ///////////////////Get Attributes////////////////////////////
    void GetStartPoint(MnjPoint<double> &p)const;
    void GetEndPoint(MnjPoint<double> &p)const;
    void GetEnds(MnjPoint<double> &s, MnjPoint<double> &e)const;
    double GetMaxDistance(MnjPoint<double> &p);

    void Set(MnjPoint<double> &s,MnjPoint<double> &center,MnjPoint<double> &e,ICSAttribute &iattr){
       marc.Set(s,center,e); 
	   SetICSAttribute(iattr);
	}
    void GetArc(MnjArc &oarc)const ;
//    MnjArc GetArc(void)const{
  //     return  MnjArc(marc);
   // }
    MnjArc GetArc(void){
       return MnjArc(marc);
    }

	double GetRadius(void);
    double GetAngle(){ 
        return marc.GetAngle(); 
    }
	void GetCenter(MnjPoint<double> &c);
    
    //virtual methods////////////////////////////////////////////////////////
    virtual void SetStartPoint(MnjPoint<double> &p);
    virtual void SetEndPoint(MnjPoint<double> &p);
	virtual void Set(const MnjSmoothableSegment &seg1,const MnjSmoothableSegment &seg2){
	   //throw error : not implemented;       
    }	
    virtual double GetCharacteristic() const ;
    
    //Other oprations//////////////////////////////////////////////////////
	bool IsPointOnArc( MnjPoint<double> &ip){
	 return	marc.IsPointOnArc(ip);
	}
    int Intersect(MnjInfiniteLine &il, vector<boost::shared_ptr<MnjPoint<double>>> &opt_vec);

	MnjDirection Tangent(MnjPoint<double> &p){
	  return marc.Tangent(p); 
	}
    //////////////////////////////////////////////////////////////////////////////////////
    MnjDirection TangentAtEnd(MnjPoint<double> &p){
	  return marc.TangentAtEnd(p); 
	}

    virtual int ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip);
    /////////////////////////////////////////////////////////////////////////////////
    virtual void Flip(void);
    virtual MnjPoint<double> GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const;
    int Project(MnjPoint<double> &ip,MnjPoint<double> &op) ;
    int Partition(const unsigned int &n, list<boost::shared_ptr<MnjSmoothableSegment>> &ol);

#if _DEBUG 
	virtual void Print(void);
#endif

private:
	MnjArc marc;


};