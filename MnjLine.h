#pragma once
//21May 2016: Manoj : Replaced typedefs by using 
//29Sep 2016: Manoj : Some member function made const

#include <vector>
#include <list>
#include <memory>

#include "Segment.h" 
#include "MnjPoint.h"
//#include "MnjInfiniteLine.h"
//#include "MnjDirection.h"
#include "GeomUtils.h"
#include "MnjPlane.h"
//#include "Mnj4x4Matrix.h"


class MnjInfiniteLine;
class Mnj4x4Matrix;
//class MnjPlane;
class MnjDirection;

using namespace std;


class MnjLine: public Segment {

public:
  using shared_ptr = std::shared_ptr<MnjLine> ;
	
  using shared_ptr_vec = vector<std::shared_ptr<MnjLine>> ;
  using shared_ptr_vec_it = vector<std::shared_ptr<MnjLine>>::iterator ;
    
  using shared_ptr_list = list<std::shared_ptr<MnjLine>> ;
  using shared_ptr_list_it = list<std::shared_ptr<MnjLine>>::iterator ;
/*
    typedef std::shared_ptr<MnjLine> shared_ptr;
	
	typedef vector<std::shared_ptr<MnjLine>> shared_ptr_vec;
	typedef vector<std::shared_ptr<MnjLine>>::iterator shared_ptr_vec_it;
    
	typedef list<std::shared_ptr<MnjLine>> shared_ptr_list;
	typedef list<std::shared_ptr<MnjLine>>::iterator shared_ptr_list_it;
*/
	MnjLine(){ }

	MnjLine(const MnjLine &l){ 
         startPoint = l.startPoint;
         endPoint = l.endPoint;
  }

  MnjLine(Segment &iSeg1, Segment &iSeg2);
  MnjLine(MnjPoint<double> &s,MnjPoint<double> &e);
  MnjLine(Segment::shared_ptr &iSeg1, Segment::shared_ptr& iSeg2);
  MnjLine(shared_ptr &iSeg1, shared_ptr& iSeg2);

//	SegmentType GetType(){ return SegmentType::LINE;}

	void Set(MnjPoint<double> &s,MnjPoint<double> &e);
	void GetStartPoint(MnjPoint<double> &p)const;
  void GetEndPoint(MnjPoint<double> &p)const;

	void SetStartPoint(MnjPoint<double> &p);
  void SetEndPoint(MnjPoint<double> &p);
	
  //gets maximum distance between a point and a line segment
	virtual double GetMaxDistance(MnjPoint<double> &p) const override;
	
  //virtual void GetNormalAtStartPoint(MnjLine &l) ;
  //virtual void GetNormalAtEndPoint(MnjLine &l);

  virtual MnjPoint<double> GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const;

  //virtual bool IsSameGeometry(Segment *s,double &tol);
	//////////////////////////////////////////////////////////////////
  double GetDistance(MnjPoint<double> &p)const;
  
  //////////////////////////////////////////////////////////////////
  double GetLength(void) const;
	// returns 0 when the two lines do not intersect 

	int Intersect(MnjLine &line, MnjPoint<double> &pIntersection);
	// returns 0 when the point is on line or will be projected beyond  
	
  int Project(const MnjPoint<double> &pIntersection, MnjPoint<double> &pProjection,double tol = .001);
	MnjInfiniteLine GetPerpendicularBisector(const MnjPoint<double> &ipt_not_on_line,
                                                    int error);
 
  void GetEnds( 
	      MnjPoint<double>  &p,
	      MnjPoint<double>  &e)const;

	void CreateParallelLine( double r,
						         	     const MnjPoint<double>  &p,
						               shared_ptr &l);

	void GetFarEndOfOtherLine( 
	const shared_ptr &l1,
	const shared_ptr &l2,
	      MnjPoint<double>  &oPoint
	);

   MnjDirection TangentAtEnd(MnjPoint<double> &p);

   int GetPointOnLine(const MnjPoint<double>  &eitherEnd, 
                      const double &distance_from_arg1,
                            MnjPoint<double> &opt_on_line)const;
//////////////////////////////////////////////////////////////////////////////////
  void GetPerpendicularAt(const MnjPoint<double> &ieitherEnd,
                          const double &idistance_from_start,
                              MnjInfiniteLine &operp_line);
/////////////////////////////////////////////////////////////////////////////////

  bool Transform( const Mnj4x4Matrix& tr );
  MnjPoint<double> StartPoint(void);
  MnjPoint<double> EndPoint(void);
  MnjVector Direction() const;
//////////////////////////////////////////////
  bool ClosestPointTo( const MnjPoint<double>& point, double *t ) const;
//////////////////////////////////////////////////////////////////////////////////////////////////
  MnjPoint<double> PointAt( double t ) const;
/////////////////////////////////////////////////////////////////////////////////////////
  MnjInfiniteLine Normal(const MnjPoint<double> &ip,//a point on the line
                           const MnjPoint<double> &iptToDefinePlane,//the normal to  line in 3d will be plane. A point input is necssary to define
                                                                    //an output line. The Point will be projected on the plane to create line.
                           int &error );
 ///////////////////////////////////////////////////////////////////////////////////////
 MnjPlane Normal(const MnjPoint<double> &ip,//a point on the line
                           int error );
 ///////////////////////////////////////////////////////////////////////////////////////
 int Partition(unsigned int n, list<shared_ptr> &l);

 MnjDirection GetPerpendicularDirection(const MnjPoint<double> &ipt_not_on_line,
                                                    int error);
 void GetMiddlePoint(MnjPoint<double> &m)const;

 int GetAPointNotOnLine(MnjPoint<double> &o_pt_not_on_line)const;
 void GetPerpendicularBisector(MnjInfiniteLine &bisector);
 MnjDirection Tangent(void);
 int ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip);


 void Flip(void);
#if _DEBUG 
	virtual void Print(void)const;
#endif 

private: 
	MnjPoint<double> startPoint;
	MnjPoint<double> endPoint;
 
};
