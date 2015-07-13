#pragma once 
 
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <memory>

#include "MnjMathNamespace.h"

//#include <boost/shared_ptr.hpp>
//#include <boost/weak_ptr.hpp>

#include "MnjPoint.h" 

/*
#include "MnjLine.h" 
#include "MnjArc.h" 
#include "MnjSmoothableSegment.h"
*/

using namespace std;
using namespace MnjMath; 

class MnjVector;
class MnjArc;
class MnjLine;
class Segment;
class MnjSmoothableSegment;


template <class T> 						
void GetDistance(MnjPoint<T> &p1,
                 MnjPoint<T> &p2, 
							   double& distance);






/*
Returns distance between a point and line-segment(not the infinite line). 
If p can not be projected on the line segment the method fails and returns -1; 

returns:
-1 : method failed 
0 : method successful
Example1: 
p = -10,0,0 
or 
p = -10, 1, 0 
LineStart = 0,0,0
LineEnd = 10,0,0 
This will fail.

Example2: 
p = 0,5,0 LineStart = 0,0,0 LineEnd = 10,0,0 
Succesful. 
Returns 0;

*/
template <class T> 
int DistancePointLine( MnjPoint<T> *p, MnjPoint<T> *LineStart, 
	                     MnjPoint<T> *LineEnd, double &od );
class GeomUtils{

	class TestGeomUtils{
	public:

		static int Test();

		static int TestDistancePointInfiniteLine();
		static int TestDistancePointLine();

		//A wrapper of other test cases 

		static void TestGetExactArcCenterUsingRadius(void);
		static void TestGetExactArcCenterUsingRadius1(void);
		static void TestGetExactArcCenterUsingRadius2(void);
		static void TestGetExactArcCenterUsingRadius3(void);

		static int TestLineLineIntersect(void);
		static int TestLineLineIntersect1(void);
		static int TestLineLineIntersect2(void);
		static int TestLineLineIntersect3(void);
		static int TestLineLineIntersect4(void);

		static int TestProject();
		static int TestProject1(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
		static int TestProject2(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
		static int TestProject3(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
		static int TestProject4(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
			double tol = .001);
	};

public:
	/* Projects point p , on line segment defined by LineStart and LineEnd.
	*/
	static int Project(const dbl_3d_pt LineStart, const dbl_3d_pt LineEnd,
	                   const dbl_3d_pt &p, 
				                   dbl_3d_pt &pProjection, double tol = .001);
	/*
	  Role: Calculate the line segment PaPb that is the shortest route between
      two lines P1P2 and P3P4. Calculate also the values of mua and mub where
			Pa = P1 + mua (P2 - P1)
			Pb = P3 + mub (P4 - P3)
	 Return 0 if no solution or multiple solutions exist.
		 p1= start of line1;
		 p2= start of line2;
		 p3= start of line3;
		 p4= start of line4;
		 error: returns if the input line are parallel or do not intersect. 
	*/
	static int LineLineIntersect(
			dbl_3d_pt & p1,dbl_3d_pt & p2,
			dbl_3d_pt & p3,dbl_3d_pt & p4,
			dbl_3d_pt & pa,dbl_3d_pt & pb,
			double *mua, double *mub,const double  tol = .001 );
/*
	  Role: Calculate the intersection between line1 and line2; 
		 p1= start of line1;
		 p2= start of line2;
		 p3= start of line3;
		 p4= start of line4;
		 error: returns if the input line are parallel or do not intersect. 
	*/

	static int LineLineIntersect(
			dbl_3d_pt & p1,dbl_3d_pt & p2,dbl_3d_pt & p3,dbl_3d_pt & p4,
			dbl_3d_pt & pa,
			const double  tol = .001);
	/*
	static int LineLineIntersect(
			MnjPoint<double> & p1,MnjPoint<double> & p2,MnjPoint<double> & p3,MnjPoint<double> & p4,
			MnjPoint<double> & pa,
			const double  tol = .001);
			*/
	/**
	Gets distance between a point p and Line segment(defined by Linestart and LineSegment).
	*/

	static int DistancePointLine( const dbl_3d_pt &p, const dbl_3d_pt &LineStart, const dbl_3d_pt &LineEnd, double &od );
	static int DistancePointInfiniteLine( dbl_3d_pt &p, dbl_3d_pt &LineStart, dbl_3d_pt &LineEnd, double &od );
	//static void GetDistance(MnjPoint<double> &p1,
	//				          MnjPoint<double> &p2, 
	//					      double& distance); 
	static void GetDistance(const dbl_3d_pt &p1, const dbl_3d_pt &p2, 
							                  double& distance); 
  static double GetDistance(const dbl_3d_pt &p1, const dbl_3d_pt &p2);
  static void GetDistance(const double &x1, const double &y1, 
		                      const double &x2, const double &y2, 
				                        double& distance);

	static void GetDistance(const double &x1, const double &y1, 
		                      const double &z1, const double &x2, 
							            const double &y2, const double &z2,
				                        double& distance);

	static void FindNearest(const double &x, const double &y,
				                  const double &x1,const double &y1,
				                  const double &x2,const double &y2,
				                  double &near_x,  double &near_y);

	static void GetMidPoint(const double &x1, const double &y1, 
  					 const double &x2, const double &y2,
					 double &xmid, double &ymid);
	static void GetAngle(const double &x,       const double &y, 
				  const double &centerX, const double &centerY, 
				  double &angle);

	static void GetLineEquation(const double &x1,const double &y1,
						 const  double &x2,const double &y2, 
						 double &m, double &c, 
						 int &bisectorParallelToY );

	static void Translate(const dbl_3d_pt &p,
		                 const MnjVector &v,
						 dbl_3d_pt &pt );

  static double  DotProduct(const MnjVector &vec1, const MnjVector &vec2);

  static MnjVector CrossProduct(const MnjVector &vec1, const MnjVector &vec2);


    static int Intersect2dLineCircle(dbl_3d_pt line_from, // 2d line from point
                 dbl_3d_pt  line_to,
                 double r,
                 double tol,
                 double* t0,
                 double* t1
                 );
    static bool IsSame(const dbl_3d_pt &ip1,
		               const dbl_3d_pt &ip2);


      static int GetIntersectionOfCircles2D(
            dbl_3d_pt &center1,
            double radius1,
            dbl_3d_pt &center2,
            double radius2,
            dbl_3d_pt &P1,
            dbl_3d_pt &P2);

    static int GetIntersectionOfCircles(
            dbl_3d_pt &center1,
            double radius1,
            dbl_3d_pt &center2,
            double radius2,
            dbl_3d_pt &P1,
            dbl_3d_pt &P2);

    static int SolveSquareEquation(
            double a,
            double b,
            double c,
            vector<double> &result);
    static int Inv( const double* src, double dst[4][4], double* determinant, double* pivot );

    static void SwapRow( double matrix[4][4], int i0, int i1 );
    static void SwapCol( double matrix[4][4], int j0, int j1 );
    
    static void ScaleRow( double matrix[4][4], double c, int i );
    static void AddCxRow( double matrix[4][4], double c, int i0, int i1 );

    //find all points in vector pt_vec that are at distance r from ip 
   //static int GetPointsAtDistance(MnjPoint<double> &ip, double &d, 
     //            vector<vec_str &currentLine, int iLineNumber,shared_ptr<MnjPoint<double>>> &pt_vec,
       //          vector<shared_ptr<MnjPoint<double>>> &opt_vec);

   static int GetPointsAtDistance(dbl_3d_pt &ip, double &d,
	   vector<std::shared_ptr<dbl_3d_pt>> &pt_vec,
	   vector<std::shared_ptr<dbl_3d_pt>> &opt_vec);

   //BOOST_TO_STD_MIGRATION static int GetPointsAtGivenDistanceFromArc(MnjArc &ia,  const double &ir, 
   //                                                                 vector<shared_ptr<MnjPoint<double>>>  &ipt_vec,
   //                                                                 vector<shared_ptr<MnjPoint<double>>>  &opt_at_distance_r_from_arc_vec);

   static int GetPointsAtGivenDistanceFromArc(MnjArc &ia, const double &ir,
	   vector<shared_ptr<MnjPoint<double>>>  &ipt_vec,
	   vector<shared_ptr<MnjPoint<double>>>  &opt_at_distance_r_from_arc_vec);

   static int GetPointsThatProjectOnLineSegment(MnjLine &il,  
	   MnjMath::shared_ptr_vec_pt &ipt_vec,
	   MnjMath::shared_ptr_vec_pt &ocan_project_pt_vec);

   

   static list<shared_ptr<MnjSmoothableSegment>>::iterator NextIter( list<shared_ptr<MnjSmoothableSegment>>  &ilist,
                        list<shared_ptr<MnjSmoothableSegment>>::iterator it);

   static list<shared_ptr<MnjSmoothableSegment>>::iterator PrevIter( list<shared_ptr<MnjSmoothableSegment>>  &ilist,
                        list<shared_ptr<MnjSmoothableSegment>>::iterator it);

   static bool Circulable(list<shared_ptr<MnjSmoothableSegment>> &l);

   static int CreateArc(shared_ptr<Segment> &iSeg1, 
                        shared_ptr<Segment> &iSeg2, 
                        const double &ir,
	                    shared_ptr<MnjArc>  &arc);
  
   static int CreateArc(shared_ptr<MnjLine> &seg1, 
                         shared_ptr<MnjLine> &seg2, 
                         const double &r,
	                     shared_ptr<MnjArc>  &arc);

   static int CreateArc(shared_ptr<MnjLine> &seg1, 
                        shared_ptr<MnjArc> &seg2, 
                        const double &r,
	                    shared_ptr<MnjArc>  &arc);

   static int CreateArc(shared_ptr<MnjArc> &seg1, 
                        shared_ptr<MnjLine> &seg2, 
                        const double &r,
	                    shared_ptr<MnjArc>  &arc);

   static int CreateArc(shared_ptr<MnjArc> &seg1, 
                        shared_ptr<MnjArc> &seg2, 
                        const double &r,
	                    shared_ptr<MnjArc>  &arc);
   /*
   static void GetFarEndOfOtherLine(const shared_ptr<MnjLine> &l1,
	                                  const shared_ptr<MnjLine> &l2,
	                                       dbl_3d_pt  &oPoint
          );
   */
   static int GetCenter(
          shared_ptr<MnjLine> &l,
	        shared_ptr<MnjArc> &a,
	        const double &ir,
	        dbl_3d_pt &ocp
    );

   static int GetAPointTowardsArc(shared_ptr<MnjLine> &l,
	                                shared_ptr<MnjArc> &a,
                                  dbl_3d_pt &op) ;
  static void GetFarEndOfOtherLine( 
	           const shared_ptr<MnjLine> &l1,
	           const shared_ptr<MnjLine> &l2,
	                 dbl_3d_pt  &oPoint);

	  /*
	  Finds exact center of a circle,
	  given
	  1. Two points on the circle
	  2. Approx center of the circle.

	  Note: Two points on the circle, constrains the center to be along an infinite straight line.
	  The approximate center serves two purposes.
	  1. It further constrains the the infinite line to semi-infinite.
	  2. It gives approximate radius.

	  Two ways of calculating radius:
	  P1(x1,y1)
	  P2(x2,y2)
	  P(guessX,guessY)

	  First way:
	  P' = Projection of P on perpendicular bisector of P1P2
	  r = dist(P',P1);//or   r = dist(P',P2)

	  Second way:
	  d1=distance(P1,P);
	  d2=distance(P2,P);
	  r = (d1+d2)/2;
	  */
	  static void GetExactArcCenterUsingRadius(const double &x1, const double &y1,
		  const  double &x2, const double &y2,
		  const double &guessX, const double &guessY,//guessed center
		  double &xc, double &yc);

  private:
	  static void GetExactArcCenterUsingRadiusNOrientation(const double &x1, const double &y1,
		  const  double &x2, const double &y2,
		  const double &guessX, const double &guessY,//guessed center
		  const bool counterClock,
		  double &xc, double &yc);

	  static int Flip(const double &xc1, const double &yc1,
		  const double &xc2, const double &yc2,
		  double &xc, double &yc);


	  static void SelectCenter(const double &x1, const double &y1, const double &x2, const double &y2,
		  const double &xc1, const double &yc1, const double &xc2, const double &yc2,
		  const bool counterClock,
		  double &xc, double &yc);
	  /*
	  x1,y1 and x2,y2: input points
	  xc1,yc1, xc2,yc2: input,center of circles through x1,y1 and x2,y2. Both circle are of same radius.
	  counterClock: input
	  xc,yc: output , the center that will make less than PI angle when going from x1,y1 to x2,y2 in the sense
	  of varaible "counterClock".
	  */

	  static void SelectCenterCounterClockWise(const double &x1, const double &y1, const double &x2, const double &y2,
		  const double &xc1, const double &yc1,
		  const double &xc2, const double &yc2,
		  double &xc, double &yc);//out

	  static void GetExactArcCenter(const double &ix1, const double &iy1,
		  const double &ix2, const double &iy2,
		  const double &guessX, const double &guessY,//guessed center
		  double &xc, double &yc);

};

template <class T> 
int DistancePointInfiniteLine( MnjPoint<T> *p, MnjPoint<T>  *LineStart, MnjPoint<T>  *LineEnd, double &od );