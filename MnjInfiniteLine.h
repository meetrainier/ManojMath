#pragma once

#include "Segment.h" 
#include "MnjPoint.h"
#include "MnjLine.h"
#include "MnjDirection.h"
class MnjLine;
class MnjInfiniteLine {

public:
  MnjInfiniteLine(){}
  //MnjInfiniteLine(Segment &iSeg1, Segment &iSeg2);
	MnjInfiniteLine(const MnjPoint<double> &s, const MnjPoint<double> &e);
	
  //MnjInfiniteLine(const MnjLine &l);
	MnjInfiniteLine( MnjLine *const l);

  MnjInfiniteLine(const MnjPoint<double> &ip,MnjDirection &iDir);

  MnjDirection GetDirection(void)const;
	void GetEnds( MnjPoint<double>  &s, MnjPoint<double>  &e)const;
	//void GetStartPoint(MnjPoint<double> &p)const;
	//void GetEndPoint(MnjPoint<double> &p)const;

	void GetPoint(MnjPoint<double> &op)const; 
  void GetDirection(MnjDirection &odir)const;

	void GetAnyTwoPointsOnLine(MnjPoint<double> &op1,MnjPoint<double> &op2)const;
	int Intersect(MnjInfiniteLine &line, MnjPoint<double> &pIntersection);
	
	//SegmentType GetType(){ return SegmentType::LINE;}

	// returns 0 when the two lines do not intersect 
	//int Intersect(MnjInfiniteLine &line, MnjPoint<double> &pIntersection);
	// returns 0 when the point is on line or will be projected beyond  
	int Project(const MnjPoint<double> &pIntersection, MnjPoint<double> &pProjection,double tol = .001);
  void Set(const MnjPoint<double> &ip,MnjDirection &iDir);
  int GetExtermeEnds(MnjPoint<double> &oe1,MnjPoint<double> &oe2);

#if _DEBUG 
	virtual void Print(void);
#endif 

private: 
	MnjPoint<double> mPoint;
	MnjDirection mDir;
 
};