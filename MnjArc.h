#pragma once
//copyright(c) 2009- 2016 Manoj Lnu 
//9/29/2016 : Manoj : some set... functions take const arg now. 
#include <vector>
#include <list>
#include <memory>
//#include <boost/shared_ptr.hpp>

#include "MnjPoint.h"
#include "Segment.h"
#include "MnjLine.h"
#include "MnjInfiniteLine.h"

//class MnjLine;
//class MnjInfiniteLine;
using namespace std;

class MnjArc: public Segment {

public:
  
  using shared_ptr = std::shared_ptr<MnjArc> ;
	
	using shared_ptr_vec = vector<std::shared_ptr<MnjArc>> ;
	using shared_ptr_vec_it = vector<std::shared_ptr<MnjArc>>::iterator ;
    
	using shared_ptr_list = list<std::shared_ptr<MnjArc>> ;
	using shared_ptr_list_it = list<std::shared_ptr<MnjArc>>::iterator ;

	MnjArc() { } 
	//MnjArc(const Segment &iSeg1, const Segment &iSeg2);
	//MnjArc(const Segment *iSeg1, const Segment *iSeg2);

	MnjArc(const MnjPoint<double> &ip1, const MnjPoint<double> &center, const MnjPoint<double> &ip2);
  MnjArc(const shared_ptr &iSeg1, const shared_ptr& iSeg2);
///////////////////////////////////////////////////////////////////////////////////////////////////////
  MnjArc(const std::shared_ptr<MnjLine> &iSeg1, const shared_ptr& iSeg2);
/////////////////////////////////////////////////////
  MnjArc(const shared_ptr &iSeg1, const MnjLine::shared_ptr& iSeg2);
//	SegmentType GetType(){ return ARC;}

	void GetStartPoint(MnjPoint<double> &p)const;
  void GetEndPoint(MnjPoint<double> &p)const;
	
	/*void Set(MnjPoint<double> &s,MnjPoint<double> &center,MnjPoint<double> &e){
		SetStartPoint(s);
		SetCenter(center);
		SetEndPoint(e);
	}
  */
  void SetStartPoint(const MnjPoint<double> &ip);
  void SetEndPoint(const MnjPoint<double> &ip);
	
	double GetRadius(void) const;
	
  void GetCenter(MnjPoint<double> &c) const;
  MnjPoint<double> GetCenter(void) const;

	void SetCenter(const MnjPoint<double> &p);
	
  //virtual void GetNormalAtStartPoint(MnjLine &l);
  //virtual void GetNormalAtEndPoint(MnjLine &l);
	
  //gets maximum distance between a point and a arc segment
	virtual double GetMaxDistance(MnjPoint<double> &p) const;
  
  //virtual bool IsSameGeometry(Segment *s,double &tol);
#ifdef _DEBUG
	virtual void Print(void) const;
#endif 

  int CreateSmallestArc(shared_ptr_vec_pt &pt_vec,MnjArc &oa);
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  
  int Intersect(MnjInfiniteLine &il, shared_ptr_vec_pt &opt_vec);
  
  bool IsPointOnArc(const MnjPoint<double> &p)const;
  int  ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip);
  
  /////////////////////////////////////////////////////////////////////////////////
  void Flip(void);
  
  int  SetSmallerArc(MnjPoint<double> &e1,MnjPoint<double> &c,MnjPoint<double> &e2);
  
  //////////////////////////////////////////////////////////////////////////////////
  MnjPoint<double> GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const;
  
  int Set(MnjPoint<double> &s,MnjPoint<double> &center,MnjPoint<double> &e);
  MnjDirection Tangent(MnjPoint<double> &ip);
  ///////////////////////////////////////////////////////////////////////////
  MnjDirection TangentAtEnd(MnjPoint<double> &ip);

  MnjPoint<double> GetPointAtAngle(const double &itheta);
  double Distance(MnjPoint<double> &ip,int &oerror);
  bool PointProjectOnArc(MnjPoint<double> &ip,MnjPoint<double> &op,int &oerror);
  bool PointProjectOnArc(MnjPoint<double> &ip,int &oerror);
  /////////////////////////////////////////////////////////////////////////////////
  int Partition(const unsigned int &n, list<std::shared_ptr<MnjArc>> &ol);
  /////////////////////////////////////////////////////////////////////////////////
  int Project(MnjPoint<double> &ip,MnjPoint<double> &op);
  //////////////////////////////////////////////////////////////////////////////////
  double GetLength()const;
  double GetAngle()const;
 
  ///gets the angle subtended at center by startPoint and ip 
	double GetAngle(const MnjPoint<double> &ip)const;
  ////////////////////////////////////////////////////////////
	inline MnjDirection GetXAxis(void)const;
	///////////////////////////////////////////////////////////
	inline MnjDirection GetYAxis(void)const;
	///////////////////////////////////////////////////////////
	inline MnjDirection GetZAxis(void)const;

  void GetEnds(MnjPoint<double> &s, MnjPoint<double> &e)const;

private: 

	MnjPoint<double> startPoint;
	MnjPoint<double> endPoint;
	MnjPoint<double> centerPoint;
};
