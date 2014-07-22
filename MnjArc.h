#pragma once
#include <vector>
#include <list>

#include <boost/shared_ptr.hpp>

#include "MnjPoint.h"
#include "Segment.h"
#include "MnjLine.h"
#include "MnjInfiniteLine.h"

//class MnjLine;
//class MnjInfiniteLine;

class MnjArc: public Segment {
public:
  typedef boost::shared_ptr<MnjArc> shared_ptr;
	
	typedef vector<boost::shared_ptr<MnjArc>> shared_ptr_vec;
	typedef vector<boost::shared_ptr<MnjArc>>::iterator shared_ptr_vec_it;
    
	typedef list<boost::shared_ptr<MnjArc>> shared_ptr_list;
	typedef list<boost::shared_ptr<MnjArc>>::iterator shared_ptr_list_it;

	MnjArc() { } 
	MnjArc(Segment &iSeg1, Segment &iSeg2);
	MnjArc(Segment *iSeg1, Segment *iSeg2);

	MnjArc(const MnjPoint<double> &ip1, const MnjPoint<double> &center, const MnjPoint<double> &ip2);
  MnjArc(shared_ptr &iSeg1, shared_ptr& iSeg2);
///////////////////////////////////////////////////////////////////////////////////////////////////////
  MnjArc(boost::shared_ptr<MnjLine> &iSeg1, shared_ptr& iSeg2);
/////////////////////////////////////////////////////
  MnjArc(shared_ptr &iSeg1, MnjLine::shared_ptr& iSeg2);
//	SegmentType GetType(){ return ARC;}

	void GetStartPoint(MnjPoint<double> &p)const;
  void GetEndPoint(MnjPoint<double> &p)const;
	
	/*void Set(MnjPoint<double> &s,MnjPoint<double> &center,MnjPoint<double> &e){
		SetStartPoint(s);
		SetCenter(center);
		SetEndPoint(e);
	}
  */
	void SetStartPoint(MnjPoint<double> &p);
  void SetEndPoint(MnjPoint<double> &p);
	
	double GetRadius(void) const;
	
  void GetCenter(MnjPoint<double> &c);
  MnjPoint<double> GetCenter(void)const;

	void SetCenter(MnjPoint<double> &p);
	
  //virtual void GetNormalAtStartPoint(MnjLine &l);
  //virtual void GetNormalAtEndPoint(MnjLine &l);
	
  //gets maximum distance between a point and a arc segment
	virtual double GetMaxDistance(MnjPoint<double> &p);
  
  //virtual bool IsSameGeometry(Segment *s,double &tol);
	virtual void Print(void);

  int CreateSmallestArc(vector<boost::shared_ptr<MnjPoint<double>>> &pt_vec,MnjArc &oa);
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  
  int Intersect(MnjInfiniteLine &il, vector<boost::shared_ptr<MnjPoint<double>>> &opt_vec);
  ////////////////////////////////////////////////////////////////////////////////////////
  
  bool IsPointOnArc(MnjPoint<double> &p)const;
  //////////////////////////////////////////////////////////////////////////////////////////
  int ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip);
  
  /////////////////////////////////////////////////////////////////////////////////
  void Flip(void);
  
  int SetSmallerArc(MnjPoint<double> &e1,MnjPoint<double> &c,MnjPoint<double> &e2);
  
  //////////////////////////////////////////////////////////////////////////////////
  MnjPoint<double> GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const;
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  int Set(MnjPoint<double> &s,MnjPoint<double> &center,MnjPoint<double> &e);
///////////////////////////////////////////////////////////////////////////////////////////
MnjDirection Tangent(MnjPoint<double> &ip);
///////////////////////////////////////////////////////////////////////////
MnjDirection TangentAtEnd(MnjPoint<double> &ip);

MnjPoint<double> GetPointAtAngle(const double &itheta);
//////////////////////////////////////////////////////////////////////
double Distance(MnjPoint<double> &ip,int &oerror);
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool PointProjectOnArc(MnjPoint<double> &ip,MnjPoint<double> &op,int &oerror);
////////////////////////////////////////////////////////////////////////////////////////////////////
 bool PointProjectOnArc(MnjPoint<double> &ip,int &oerror);
/////////////////////////////////////////////////////////////////////////////////////////////////////
 int Partition(const unsigned int &n, list<boost::shared_ptr<MnjArc>> &ol);
 /////////////////////////////////////////////////////////////////////////////////
 int Project(MnjPoint<double> &ip,MnjPoint<double> &op);
 //////////////////////////////////////////////////////////////////////////////////
 double GetLength()const;
 double GetAngle()const;
 
 ///gets the angle subtended at center by startPoint and ip 
	double GetAngle(MnjPoint<double> &ip)const;
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