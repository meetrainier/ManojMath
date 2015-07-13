#pragma once
#include <memory> 
#include "MnjSmoothableSegment.h"
#include "MnjPoint.h"
#include "MnjInfiniteLine.h"
 
class MnjSmoothableLine: public MnjSmoothableSegment {
public:
  typedef std::shared_ptr<MnjSmoothableLine> shared_ptr;
	
	typedef vector<std::shared_ptr<MnjSmoothableLine>> shared_ptr_vec;
	typedef vector<std::shared_ptr<MnjSmoothableLine>>::iterator shared_ptr_vec_it;
    
	typedef list<std::shared_ptr<MnjSmoothableLine>> shared_ptr_list;
	typedef list<std::shared_ptr<MnjSmoothableLine>>::iterator shared_ptr_list_it;

  MnjSmoothableLine(){mstatus =MnjSmoothableSegment::UNKNOWN;}
  MnjSmoothableLine(MnjPoint<double> &s, MnjPoint<double> &e );//,ICSAttribute &attr);
  MnjSmoothableLine(MnjLine &l, ICSAttribute& iattr);

  //MnjSmoothableLine(boost::shared_ptr<MnjSmoothableLine> &iICSSeg1, boost::shared_ptr<MnjSmoothableLine> &iSeg2, ICSAttribute &attr);
  MnjSmoothableLine(shared_ptr &iICSSeg1, shared_ptr &iSeg2, ICSAttribute &attr);
  
  MnjSmoothableLine(shared_ptr &iICSSeg1, shared_ptr &iSeg2,
                 //ICSAttribute &attr,
                 MnjSmoothableSegment::SegmentChange iStatus);
    //MnjSmoothableLine(MnjPoint<double> &s, MnjPoint<double> &e);

	void Set(MnjPoint<double> &s, MnjPoint<double> &e);

	void GetStartPoint(MnjPoint<double> &p)const;
  void GetEndPoint(MnjPoint<double> &p)const;
	
	virtual void SetStartPoint(MnjPoint<double> &p);
  virtual void SetEndPoint(MnjPoint<double> &p);
  virtual double GetCharacteristic() const {return mline.GetLength();  }

	virtual void Set(const MnjSmoothableSegment &seg1,
		               const MnjSmoothableSegment &seg2);


	virtual void Flip(void);
  virtual MnjPoint<double> GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const;

	//gets maximum distance between a point and a line segment
	virtual double GetMaxDistance(MnjPoint<double> &p);
	
  MnjDirection TangentAtEnd(MnjPoint<double> &p){
	  return mline.TangentAtEnd(p); 
	}

  std::shared_ptr<MnjLine> GetLine(void)const;
  
  std::shared_ptr<Segment> GetSegment(void);
	double GetDistance(MnjPoint<double> &p);

	// returns 0 when the two lines do not intersect 
	int Intersect(MnjLine &line, MnjPoint<double> &pIntersection);
	
	// returns -1 when the point is on line or will be projected beyond  
	int Project(const MnjPoint<double> &pIntersection, MnjPoint<double> &pProjection,double tol = .001);
	void GetEnds( MnjPoint<double>  &p, MnjPoint<double>  &e)const;

	void CreateParallelLine( double r,
					                 const MnjPoint<double>  &p,
							             std::shared_ptr<MnjLine> &l);

	int GetPointOnLine(const MnjPoint<double>  &eitherEnd,
                     const double &distance_from_the_arg1,
                           MnjPoint<double> &opt_on_line)const {
		return mline.GetPointOnLine(eitherEnd,distance_from_the_arg1,opt_on_line);
	}

	void GetPerpendicularAt(const MnjPoint<double>  &ieitherEnd,
                          const double &idistance_from_start,
                                MnjInfiniteLine &operp_line){
		mline.GetPerpendicularAt(ieitherEnd,idistance_from_start,operp_line);
	}
    virtual int ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip);
    /////////////////////////////////////////////////////////////////////////////////
    int Partition(const unsigned int &n, list<std::shared_ptr<MnjSmoothableSegment>> &ol);
#if _DEBUG 
	virtual void Print(void);
#endif 
private: 
	//MnjPoint<double> startPoint;
	//MnjPoint<double> endPoint;
     MnjLine mline;
};