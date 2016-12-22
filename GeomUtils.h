//copyright(c) 2009- 2016 Manoj Lnu 
// 12/21/2016 : converted Project to a template method
#pragma once 
 
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <memory>

#include "MnjMathNamespace.h"


#include "MnjPoint.h" 

using namespace std;
using namespace MnjMath; 

class MnjVector;
class MnjArc;
class MnjLine;
class Segment;
class MnjSmoothableSegment;

/*
Get distance between two points.
*/
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

	

public:
		
	/*
  	  Role:Creates an arc between two adjacent line segments
  	  Input: two segments and a radius. The segments could be a line or a radius
    	*/
   	static int CreateArc(     shared_ptr<Segment> &iSeg1, 
                                  shared_ptr<Segment> &iSeg2, 
                            const double &ir,
	                          shared_ptr<MnjArc>  &arc);
  	/*
  	  Role:Creates an arc between two adjacent line segments
  	  Input: two lines and a radius
    	*/
   	static int CreateArc(      shared_ptr<MnjLine> &seg1, 
                                   shared_ptr<MnjLine> &seg2, 
                             const double &r,
	                           shared_ptr<MnjArc>  &arc);

        /*
  	  Role:  Creates an arc between two adjacent line segments
  	  Input: one line, one arc and a radius
    	*/
        static int CreateArc(      shared_ptr<MnjLine> &seg1, 
                                   shared_ptr<MnjArc> &seg2, 
                             const double &r,
	                           shared_ptr<MnjArc>  &arc);

   	/*
  	  Role:Creates an arc between two adjacent line segments
  	  Input:  one arc, one line and a radius
    	*/
    	static int CreateArc(      shared_ptr<MnjArc> &seg1, 
                                   shared_ptr<MnjLine> &seg2, 
                             const double &r,
	                           shared_ptr<MnjArc>  &arc);

   	/*
  	  Role:Creates an arc between two adjacent line segments
  	  Input: two arcs and a radius
    	*/
    	static int CreateArc(        shared_ptr<MnjArc> &seg1, 
                                     shared_ptr<MnjArc> &seg2, 
                               const double &r,
	                             shared_ptr<MnjArc>  &arc);
	
	/* 
	Projects point p, on line segment defined by LineStart and LineEnd.
  comments: cannot return auto , because soem uses are before the function is defined.
	*/


  //template<class T>
  //static int Project(T LineStart,  T LineEnd,
  //  const T &p,
  //  T &pProjection, double tol = .001);

      template<class T>
      static int Project(const T LineStart,
                         const T LineEnd,
      	                     const T &p, 
      					                   T &pProjection, double tol =.001){
         double LineMag;
         double U;
           
          GeomUtils::GetDistance<T>( LineEnd, LineStart, LineMag );
       
          U = ( ( ( p.x - LineStart.x ) * ( LineEnd.x - LineStart.x ) ) +
              ( ( p.y - LineStart.y ) * ( LineEnd.y - LineStart.y ) ) +
              ( ( p.z - LineStart.z ) * ( LineEnd.z - LineStart.z ) ) ) /
              ( LineMag * LineMag );
       
          if( U < 0.0f || U > 1.0f )
              return 0;   // closest point does not fall within the line segment
       
          pProjection.x = LineStart.x + U * ( LineEnd.x - LineStart.x );
          pProjection.y = LineStart.y + U * ( LineEnd.y - LineStart.y );
          pProjection.z = LineStart.z + U * ( LineEnd.z - LineStart.z );
      	return 1;
      }

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
	Gets distance between a point p and Line segment(defined by Linestart and LineEnd).
	*/

	static int DistancePointLine( const dbl_3d_pt &p, const dbl_3d_pt &LineStart, const dbl_3d_pt &LineEnd, double &od );
	/**
	Gets distance between a point p and and infinite Line segment(defined by Linestart and LineEnd).
	*/
	static int DistancePointInfiniteLine( dbl_3d_pt &p, dbl_3d_pt &LineStart, dbl_3d_pt &LineEnd, double &od );
 
 	/*
	Get distance between two points.
	*/
	//static void GetDistance(const dbl_3d_pt& p1, const dbl_3d_pt &p2, 
	//			      double&    distance); 

  template<class T>
  static void GetDistance(const T& p1, const T &p2,
    double&    distance); 

	/*
	Get distance between two points.
	*/
  	static double GetDistance(const dbl_3d_pt &p1, const dbl_3d_pt &p2);
  
	/*
	Get distance between two points.
	*/
  	static void GetDistance(const double &x1, const double &y1, 
		                const double &x2, const double &y2, 
				                        double& distance);
	/*
	Get distance between two 3d points.
	*/

	static void GetDistance(const double &x1, const double &y1, 
		                const double &z1, const double &x2, 
				const double &y2, const double &z2,
				                        double& distance);

        /*
         Finds which point is nearer to ix,iy 
          out of (ix1,iy1) and (ix2,iy2) 
        */
	static void FindNearest(const double &ix, const double &iy,
			        const double &ix1,const double &iy1,
				const double &ix2,const double &iy2,
				                  double &near_x,  double &near_y);
	/*
		find mid point of  between two 2d points.
	*/
	static void GetMidPoint(const double &x1, const double &y1, 
  				const double &x2, const double &y2,
					 double &xmid, double &ymid);
					 
	static void GetAngle(const double &x,       const double &y, 
			     const double &centerX, const double &centerY, 
				   double &angle);

        /*
          input:  Coordinates of two points
          output: Coefficient to define equation of line ( as in form y = mx+c )
         */
	static void GetLineEquation(const double &x1,const double &y1,
				   const  double &x2,const double &y2, 
						 double &m, double &c, 
						 int &bisectorParallelToY );

	/*
	  Translates a point along a given vector. 
	*/
	static void Translate(const dbl_3d_pt &p,
		              const MnjVector &v,
				    dbl_3d_pt &pt );

        /*
         finds dot product of two vectors. 
         */
  	static double  DotProduct(const MnjVector &vec1, const MnjVector &vec2);

	/*
         finds dot product of two vectors. 
         */
  	static MnjVector CrossProduct(const MnjVector &vec1, const MnjVector &vec2);

         /*
         Takes intersection between a circle (centered at origin) and a line (defined by two points).
         */
    	static int Intersect2dLineCircle(dbl_3d_pt line_from, // 2d line from point
                 dbl_3d_pt  line_to,
                 double r,
                 double tol,
                 double* t0,
                 double* t1
                 );
        /*
                  Compares that given points are same or not. 
        */
    	static bool IsSame(const dbl_3d_pt &ip1,
		           const dbl_3d_pt &ip2);

        /*
         Find inetrsection points between two circles. 
         */
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
     	/*
     	Solves a qudratic equation
      	*/
    	static int SolveSquareEquation(
            double a,
            double b,
            double c,
            vector<double> &result);
    	
    	static int Inv( const double* src, double dst[4][4], double* determinant, double* pivot );
    	
    	/*
    	Swaps two row of a matrix 
     	*/
    	static void SwapRow( double matrix[4][4], int i0, int i1 );
     	
     	/*
    	Swaps two columns of a matrix 
     	*/
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


   	static int GetCenter(shared_ptr<MnjLine> &l,
	                     shared_ptr<MnjArc> &a,
	                     const double &ir,
	                     dbl_3d_pt &ocp
                             );

   	static int GetAPointTowardsArc(shared_ptr<MnjLine> &l,
	                               shared_ptr<MnjArc> &a,
                                       dbl_3d_pt          &op) ;
                                       
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
		  
		  class TestGeomUtils{
	public:

		static int Test();
                  /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect1(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect2(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect3(void);
		 /*
                 Refer to the documentation of TestLineLineIntersect() 
                 */
		static int TestLineLineIntersect4(void);
                /*
                 Refer to the documentation of 
                 */
		static int TestDistancePointInfiniteLine();
		 /*
                 Refer to the documentation of DistancePointLine() 
                 */
		static int TestDistancePointLine();

		//A wrapper of other test cases 
                   /*
                 Refer to the documentation of GetExactArcCenterUsingRadius() 
                 */
		static void TestGetExactArcCenterUsingRadius(void);
		   /*
                 Refer to the documentation of 
                 */
		static void TestGetExactArcCenterUsingRadius1(void);
		static void TestGetExactArcCenterUsingRadius2(void);
		static void TestGetExactArcCenterUsingRadius3(void);

               
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

};

template <class T> 
int DistancePointInfiniteLine( MnjPoint<T> *p, MnjPoint<T>  *LineStart, MnjPoint<T>  *LineEnd, double &od );
