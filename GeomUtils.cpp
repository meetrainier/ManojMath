/**
Manoj 4/13/2012 Added 3d line-line intersection LineLineIntersect()
Manoj /10/2015 Migration from boost to std. Now using <memory> header 

*/

#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <vector>

#include "GeomUtils.h"
#include "MNJPoint.h" 
#include "MathConstant.h" 
#include "MnjVector.h"
#include "MnjLine.h"
#include "MnjArc.h"
#include "MnjCircle.h"

///

using namespace std;

int GeomUtils::Project(const dbl_3d_pt LineStart, 
                       const dbl_3d_pt LineEnd,
	                   const dbl_3d_pt &p, 
					         dbl_3d_pt &pProjection,double tol ){
   double LineMag;
   double U;
  //  MnjPoint<double> Intersection;
     
    GeomUtils::GetDistance( LineEnd, LineStart, LineMag );
 
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
int GeomUtils::LineLineIntersect(dbl_3d_pt & p1,dbl_3d_pt &p2,
								        dbl_3d_pt & p3,dbl_3d_pt & p4,
										dbl_3d_pt & pa,
										const double  tol)
{
	
	dbl_3d_pt pb;
	double a ,b;
	int flag = GeomUtils::LineLineIntersect(p1,p2,p3,p4,pa,pb,&a,&b,tol);
	
	if(flag){
		double d = 0;
		GeomUtils::GetDistance(pa,pb,d);
		if(d < tol ) 
			flag = 1;
		else 
			flag = 0;
	}
	
	return flag;
}

 int GeomUtils::LineLineIntersect(
   dbl_3d_pt & p1,dbl_3d_pt & p2,dbl_3d_pt & p3,dbl_3d_pt & p4,
   dbl_3d_pt & pa,dbl_3d_pt & pb,
   double *mua, double *mub,const double  tol  )
{
   dbl_3d_pt  p13,p43,p21;
   double d1343,d4321,d1321,d4343,d2121;
   double numer,denom;

   p13.x = p1.x - p3.x;
   p13.y = p1.y - p3.y;
   p13.z = p1.z - p3.z;
   p43.x = p4.x - p3.x;
   p43.y = p4.y - p3.y;
   p43.z = p4.z - p3.z;
   //if (ABS(p43.x) < EPS && ABS(p43.y) < EPS && ABS(p43.z) < EPS)
     // return(FALSE);

   if (fabs(p43.x) < tol && fabs(p43.y) < tol && fabs(p43.z) < tol)
       return 0;

   p21.x = p2.x - p1.x;
   p21.y = p2.y - p1.y;
   p21.z = p2.z - p1.z;
   if (fabs(p21.x) < tol && fabs(p21.y) < tol && fabs(p21.z) < tol)
      return 0;

   d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
   d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
   d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
   d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
   d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

   denom = d2121 * d4343 - d4321 * d4321;
   if (fabs(denom) < tol)
      return 0;
   numer = d1343 * d4321 - d1321 * d4343;

   *mua = numer / denom;
   *mub = (d1343 + d4321 * (*mua)) / d4343;

   pa.x = p1.x + *mua * p21.x;
   pa.y = p1.y + *mua * p21.y;
   pa.z = p1.z + *mua * p21.z;
   pb.x = p3.x + *mub * p43.x;
   pb.y = p3.y + *mub * p43.y;
   pb.z = p3.z + *mub * p43.z;

   return 1 ;
}

void GeomUtils::GetDistance(const dbl_3d_pt &p1,const dbl_3d_pt &p2, 
				 double& distance){
distance = sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2));
}


int GeomUtils::DistancePointInfiniteLine( dbl_3d_pt &p, dbl_3d_pt &LineStart, dbl_3d_pt &LineEnd, double &od )
 {
    double LineMag;
    double U;
    dbl_3d_pt  Intersection;
 
    GetDistance( LineEnd, LineStart, LineMag );
 
    U = ( ( ( p.x - LineStart.x ) * ( LineEnd.x - LineStart.x ) ) +
        ( ( p.y - LineStart.y ) * ( LineEnd.y - LineStart.y ) ) +
        ( ( p.z - LineStart.z ) * ( LineEnd.z - LineStart.z ) ) ) /
        ( LineMag * LineMag );
 
    Intersection.x = LineStart.x + U * ( LineEnd.x - LineStart.x );
    Intersection.y = LineStart.y + U * ( LineEnd.y - LineStart.y );
    Intersection.z = LineStart.z + U * ( LineEnd.z - LineStart.z );
 
    GetDistance( p, Intersection,od );
 
    return 0;
}

//TBD: when y1 == y2
template <class T>
void GetDistance(MnjPoint<T> &p1,MnjPoint<T> &p2, 
				 double& distance){
distance = sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2));
}

///////////////////////////////////////////////////////////////////////////////////////////////
void GetExactArcCenter(const double &x1,const double &y1,
					   const double &x2,const double &y2, 
		               const double &guessX, const double &guessY,//guessed center
		               double &xc, double &yc ){
						
//let us say: equation of bisector is y = mx + c
  int bisectorParallelToY = 0;
  double m=0;
  double c=0;
  
  GeomUtils::GetLineEquation(x1,y1,x2,y2,m,c, bisectorParallelToY );
  
  if( bisectorParallelToY )  {
    xc = (x1+x2)/2;
    yc = guessY;
  }else {
   xc = (guessX+m*guessY-c*m)/(1+m*m);//(guessX+guessY - c)/(1+m);
   yc = (m*m*guessY +  m*guessX + c)/(1+m*m); //m*(guessX + guessY -c)/(1+m) + c;
  }
}

////////////////////////////////////////////////////////////////////////////////////
void GeomUtils::GetDistance(const double &x1, const double &y1, const double &x2, const double &y2, 
				 double& distance){
distance = sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}
////////////////////////////////////////////////////////////////////////////////////
void GeomUtils::GetDistance(const double &x1, const double &y1, const double &z1,  
	                          const double &x2, const double &y2, const double &z2,
				                          double& distance){
  distance = sqrt(pow((x1-x2),2) + pow((y1-y2),2)+ pow((z1-z2),2));
}
////////////////////////////////////////////////////////////////////////////////////
double GeomUtils::GetDistance(const dbl_3d_pt &p1,const dbl_3d_pt &p2){
  return sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2));
}
/////////////////////////////////////////////////////////////////////////////////////
void GeomUtils::FindNearest(const double &x,const double &y,
				 const double &x1,const double &y1,
				 const double &x2,const double &y2,
			     double &near_x,double &near_y){
				
				double d1 = 0;
				GetDistance(x,y,x1,y1,d1);
			    
				double d2 = 0;
				GetDistance(x,y,x2,y2,d2);
				
				if(d1<d2){
					near_x = x1; near_y = y1;
				}else {
					near_x = x2; near_y = y2;
				}
}
////////////////////////////////////////////////////////////////////////////
void GeomUtils::GetMidPoint(const double &x1, const double &y1, 
  	                        const double &x2, const double &y2,
				            double &xmid, double &ymid){
					 xmid = (x1+x2)*0.5 ;
					 ymid = (y1+y2)*0.5 ;
}
//////////////////////////////////////////////////////////////////////////////
void GeomUtils::GetExactArcCenterUsingRadius(const double &x1, const double &y1,
								  const double &x2,     const double &y2, 
                                  const double &guessX, const double &guessY,//guessed center
		                          double &xc, double &yc ){
						
//let us say: equation of bisector is y = mx + c
  int bisectorParallelToY = 0;
  double m=0;
  double c=0;
  GeomUtils::GetLineEquation(x1,y1,x2,y2,m,c, bisectorParallelToY );
  //get approx radius
  double d1=0;
  GeomUtils::GetDistance(x1,y1,guessX,guessY,d1);
  double d2=0;
  GeomUtils::GetDistance(x2,y2,guessX,guessY,d2);
  double r = (d1+d2)*0.5; 
  
  //Get points at radius distance from (x1,y1) or (x2,y2)on the line
   double line_segment = 0;
   GeomUtils::GetDistance(x1,y1,x2,y2,line_segment);
   double l = line_segment/2;//half of line segment
   double b = sqrt(r*r-l*l);
  
   double xmid, ymid;
   GeomUtils::GetMidPoint(x1,y1,x2,y2,xmid,ymid);
   double xc1 = xmid + b/sqrt(1+m*m);
   double yc1 = m*xc1 + c;

   double xc2 = xmid - b/sqrt(1+m*m);
   double yc2 = m*xc2 + c;
   if( bisectorParallelToY ) {
	   xc1 = xmid;
	   yc1 = ymid +b;

	   xc2 = xmid;
	   yc2 = ymid -b;

   }

   GeomUtils::FindNearest(guessX,guessY,xc1,yc1,xc2,yc2,xc,yc);

}
//////////////////////////////////////////////////////////////////////////////////
void GeomUtils::GetExactArcCenterUsingRadiusNOrientation(const double &x1,const double &y1,
											  const  double &x2,const double &y2, 
		       const double &guessX, const double &guessY,//guessed center
			   const bool counterClock,
		             double &xc, double &yc ){
						
//let us say: equation of bisector is y = mx + c
  int bisectorParallelToY = 0;
  double m;
  double c;
  GeomUtils::GetLineEquation(x1,y1,x2,y2,m,c, bisectorParallelToY );
  //get approx radius
  double d1=0;
  GeomUtils::GetDistance(x1,y1,guessX,guessY,d1);
  double d2=0;
  GeomUtils::GetDistance(x2,y2,guessX,guessY,d2);
  double r = (d1+d2)*0.5; 
  
  //Get points at radius distance from (x1,y1) or (x2,y2)on the line
   double line_segment = 0;
   GeomUtils::GetDistance(x1,y1,x2,y2,line_segment);
   double l = line_segment/2;//half of line segment
   double b = sqrt(r*r-l*l);
  
   double xmid, ymid;
   GeomUtils::GetMidPoint(x1,y1,x2,y2,xmid,ymid);
   double xc1 = xmid + b/sqrt(1+m*m);
   double yc1 = m*xc1 + c;

   double xc2 = xmid - b/sqrt(1+m*m);
   double yc2 = m*xc2 + c;

   //FindNearest(guessX,guessY,xc1,yc1,xc2,yc2,xc,yc);
   SelectCenter(x1,y1,x2,y2,xc1,yc1,xc2,yc2,true,xc,yc);

  //if( bisectorParallelToY )  {

}
////////////////////////////////////////////////////////////////////////////////////////////////
void GeomUtils::SelectCenterCounterClockWise(const double &x1, const double &y1, 
	                              const double &x2, const double &y2, 
			                      const double &xc1,const double &yc1,
								  const double &xc2,const double &yc2, 
			                      double &xc, double &yc){

double a1=0;
GeomUtils::GetAngle(x1,y1,xc1,yc1,a1);

double a2=0;
GeomUtils::GetAngle(x2,y2,xc1,yc1,a2);

bool positveNLessThanPI = 0 < (a2-a1) && (a2-a1) < M_PI;
bool negativeNBteweenPIAnd2PI = 0 > (a2-a1) && fabs(a2-a1) > M_PI && fabs(a2-a1) < 2*M_PI ;
if( positveNLessThanPI || negativeNBteweenPIAnd2PI ){
	xc = xc1;
	yc = yc1;
}else {
 	xc = xc2;
	yc = yc2;
}
}
/////////////////////////////////////////////////////////////////////////////
int GeomUtils::Flip(const double &xc1, const double &yc1,
	         const double &xc2,const double &yc2, 
			 double &xc, double &yc){

		bool center1 = xc == xc1 && yc == yc1;
		if(center1) { xc = xc2 ; yc = yc2 ; return 0;}  
		bool center2 = xc == xc2 && yc == yc2;
		if(center2) { xc = xc1 ; yc = yc1 ; return 0;}
		return -1;

}

void GeomUtils::SelectCenter(const double &x1, const double &y1, const double &x2, const double &y2,
			 const double &xc1,const double &yc1,const double &xc2,const double &yc2, 
			 const bool counterClock,
			 double &xc, double &yc){

	SelectCenterCounterClockWise(x1,y1,x2,y2,xc1,yc1,xc2,yc2,xc,yc);
	if(!counterClock){ 
		int result = Flip(xc1,yc1,xc2,yc2,xc,yc);
		//assert(0==result);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GeomUtils::DistancePointLine( const dbl_3d_pt &p, const dbl_3d_pt &LineStart, const dbl_3d_pt &LineEnd, double &od )
 {
    double LineMag;
    double U;
    dbl_3d_pt Intersection;
 
    GetDistance( LineEnd, LineStart, LineMag );
 
    U = ( ( ( p.x - LineStart.x ) * ( LineEnd.x - LineStart.x ) ) +
        ( ( p.y - LineStart.y ) * ( LineEnd.y - LineStart.y ) ) +
        ( ( p.z - LineStart.z ) * ( LineEnd.z - LineStart.z ) ) ) /
        ( LineMag * LineMag );
 
    if( U < 0.0f || U > 1.0f )
        return -1;   // closest point does not fall within the line segment
 
    Intersection.x = LineStart.x + U * ( LineEnd.x - LineStart.x );
    Intersection.y = LineStart.y + U * ( LineEnd.y - LineStart.y );
    Intersection.z = LineStart.z + U * ( LineEnd.z - LineStart.z );
    GetDistance( p, Intersection,od );
 
    return 0;
}


template <class T>
int DistancePointLine( MnjPoint<T> *p, MnjPoint<T> *LineStart, MnjPoint<T> *LineEnd, double &od )
 {
    double LineMag;
    double U;
    MnjPoint<T> Intersection;
 
    GetDistance( *LineEnd, *LineStart, LineMag );
 
    U = ( ( ( p->x - LineStart->x ) * ( LineEnd->x - LineStart->x ) ) +
        ( ( p->y - LineStart->y ) * ( LineEnd->y - LineStart->y ) ) +
        ( ( p->z - LineStart->z ) * ( LineEnd->z - LineStart->z ) ) ) /
        ( LineMag * LineMag );
 
    if( U < 0.0f || U > 1.0f )
        return -1;   // closest point does not fall within the line segment
 
    Intersection.x = LineStart->x + U * ( LineEnd->x - LineStart->x );
    Intersection.y = LineStart->y + U * ( LineEnd->y - LineStart->y );
    Intersection.z = LineStart->z + U * ( LineEnd->z - LineStart->z );
 
    GetDistance( *p, Intersection,od );
 
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
int DistancePointInfiniteLine( MnjPoint<T> *p, MnjPoint<T> *LineStart, MnjPoint<T> *LineEnd, double &od )
 {
    double LineMag;
    double U;
    MnjPoint<T>  Intersection;
 
    GetDistance( *LineEnd, *LineStart, LineMag );
 
    U = ( ( ( p->x - LineStart->x ) * ( LineEnd->x - LineStart->x ) ) +
        ( ( p->y - LineStart->y ) * ( LineEnd->y - LineStart->y ) ) +
        ( ( p->z - LineStart->z ) * ( LineEnd->z - LineStart->z ) ) ) /
        ( LineMag * LineMag );
 
    Intersection.x = LineStart->x + U * ( LineEnd->x - LineStart->x );
    Intersection.y = LineStart->y + U * ( LineEnd->y - LineStart->y );
    Intersection.z = LineStart->z + U * ( LineEnd->z - LineStart->z );
 
    GetDistance<T>( *p, Intersection,od );
 
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////
void GeomUtils::GetAngle(const double &x,       const double &y, 
		      const double &centerX, const double &centerY, 
			  double &angle){
double local_x = x - centerY;
double local_y = y - centerY;
angle  = atan2(y,x);
if(angle< 0 ) angle = angle + 2*M_PI;
}
//void RangeBasedForLoop(void);
///////////////////////////////////////////////////////////
/*
int main(){
//cout << "sqrt =" << sqrt(-1.0) << endl;
 //RangeBasedForLoop();

	double input[4][6] = 
{
13.230647,3.480463,  13.229283,3.486164, 13.233900,3.315600,
13.229283,3.486164,  13.269149,3.488089, 13.233900,3.315600,
13.269149,3.488089,  13.294641,3.487344, 13.233900,3.315600,
13.294641,3.487344,  13.321649,3.482223, 13.233900,3.315600
};
//GetExactArcCenter(0,0,2,0,.88, 1,x ,y); 
for ( int i = 0; i < 4 ; i++ ){

	double x =0 , y = 0;
	//GetExactArcCenter(input[i][0],input[i][1],input[i][2],input[i][3],input[i][4],input[i][5],x,y);
	GetExactArcCenterUsingRadius(input[i][0],input[i][1],input[i][2],input[i][3],input[i][4],input[i][5],x,y);
	double r = 0;
	GetDistance(input[i][0],input[i][1],x,y,r);
	double l = 0;
	GetDistance(input[i][0],input[i][1],input[i][2],input[i][3],l);
	cout << "xs = " << input[i][0]<< " ys = " << input[i][1] << "\txe = " << input[i][2]<< " ye = " << input[i][3] << "\txc = " << input[i][4]<< " yc = " << input[i][5] << endl;
    cout << "adj_xc = " << x <<  " adj_yc = " << y << "\tr = " << r << "\tl = " << l << endl;
	cout << "ye - ys= " << input[i][3] - input[i][1] << endl;
}

}
*/
void GeomUtils::GetLineEquation(const double &x1,const double &y1,
				     const  double &x2,const double &y2, 
				     double &m, double &c, 
			         int &bisectorParallelToY )
{
	bisectorParallelToY = 0;
	if(y2!=y1){
		m = -(x2-x1)/(y2-y1);
	}
	else { 
		bisectorParallelToY = 1;
                cout << "Line parallel to X" << endl; 
		cout << "Bisector parallel to Y" << endl; 
	}
	c = (y1+y2)/2 -m*(x1+x2)/2;

}
///////////////////////////////////////////////////////////////////////////////////////////////
 int GeomUtils::Inv( const double* src, double dst[4][4], double* determinant, double* pivot )
{
  // returns rank (0, 1, 2, 3, or 4), inverse, and smallest pivot

	double M[4][4], I[4][4], x, c, d;
	int i, j, ix, jx;
  int col[4] = {0,1,2,3};
  int swapcount = 0;
  int rank = 0;

  *pivot = 0.0;
  *determinant = 0.0;

  memset( I, 0, sizeof(I) );
  I[0][0] = I[1][1] = I[2][2] = I[3][3] = 1.0;

  memcpy( M, src, sizeof(M) );

  // some loops unrolled for speed

  ix = jx = 0;
	x = fabs(M[0][0]);
  for ( i = 0; i < 4; i++ ) for ( j = 0; j < 4; j++ ) {
    if ( fabs(M[i][j]) > x ) {
      ix = i;
      jx = j;
      x = fabs(M[i][j]);
    }
  }
  *pivot = x;
  if ( ix != 0 ) {
    SwapRow( M, 0, ix );
    SwapRow( I, 0, ix );
    swapcount++;
  }
  if ( jx != 0 ) {
    SwapCol( M, 0, jx );
    col[0] = jx;
    swapcount++;
  }

  if ( x > 0.0 ) {
    rank++;

    c = d = 1.0/M[0][0];
    M[0][1] *= c; M[0][2] *= c; M[0][3] *= c;
    ScaleRow( I, c, 0 );

    x *=  MNJ_EPSILON;

	  if (fabs(M[1][0]) > x) {
		  c = -M[1][0];
      M[1][1] += c*M[0][1]; M[1][2] += c*M[0][2]; M[1][3] += c*M[0][3];
      AddCxRow( I, c, 0, 1 );
	  }
	  if (fabs(M[2][0]) >  x) {
		  c = -M[2][0];
      M[2][1] += c*M[0][1]; M[2][2] += c*M[0][2]; M[2][3] += c*M[0][3];
      AddCxRow( I, c, 0, 2 );
	  }
	  if (fabs(M[3][0]) >  x) {
		  c = -M[3][0];
      M[3][1] += c*M[0][1]; M[3][2] += c*M[0][2]; M[3][3] += c*M[0][3];
      AddCxRow( I, c, 0, 3 );
	  }

    ix = jx = 1;
	  x = fabs(M[1][1]);
    for ( i = 1; i < 4; i++ ) for ( j = 1; j < 4; j++ ) {
      if ( fabs(M[i][j]) > x ) {
        ix = i;
        jx = j;
        x = fabs(M[i][j]);
      }
    }
    if ( x < *pivot )
      *pivot = x;
    if ( ix != 1 ) {
      SwapRow( M, 1, ix );
      SwapRow( I, 1, ix );
      swapcount++;
    }
    if ( jx != 1 ) {
      SwapCol( M, 1, jx );
      col[1] = jx;
      swapcount++;
    }
    if ( x > 0.0 ) {
      rank++;

      c = 1.0/M[1][1];
      d *= c;
      M[1][2] *= c; M[1][3] *= c;
      ScaleRow( I, c, 1 );

      x *= MNJ_EPSILON;
      if (fabs(M[0][1]) >  x) {
        c = -M[0][1];
        M[0][2] += c*M[1][2]; M[0][3] += c*M[1][3];
        AddCxRow( I, c, 1, 0 );
      }
      if (fabs(M[2][1]) >  x) {
        c = -M[2][1];
        M[2][2] += c*M[1][2]; M[2][3] += c*M[1][3];
        AddCxRow( I, c, 1, 2 );
      }
      if (fabs(M[3][1]) >  x) {
        c = -M[3][1];
        M[3][2] += c*M[1][2]; M[3][3] += c*M[1][3];
        AddCxRow( I, c, 1, 3 );
      }

      ix = jx = 2;
	    x = fabs(M[2][2]);
      for ( i = 2; i < 4; i++ ) for ( j = 2; j < 4; j++ ) {
        if ( fabs(M[i][j]) > x ) {
          ix = i;
          jx = j;
          x = fabs(M[i][j]);
        }
      }
      if ( x < *pivot )
        *pivot = x;
      if ( ix != 2 ) {
        SwapRow( M, 2, ix );
        SwapRow( I, 2, ix );
        swapcount++;
      }
      if ( jx != 2 ) {
        SwapCol( M, 2, jx );
        col[2] = jx;
        swapcount++;
      }
      if ( x > 0.0 ) {
        rank++;

        c = 1.0/M[2][2];
        d *= c;
        M[2][3] *= c;
        ScaleRow( I, c, 2 );

        x *= MNJ_EPSILON;
        if (fabs(M[0][2]) >  x) {
          c = -M[0][2];
          M[0][3] += c*M[2][3];
          AddCxRow( I, c, 2, 0 );
        }
        if (fabs(M[1][2]) >  x) {
          c = -M[1][2];
          M[1][3] += c*M[2][3];
          AddCxRow( I, c, 2, 1 );
        }
        if (fabs(M[3][2]) >  x) {
          c = -M[3][2];
          M[3][3] += c*M[2][3];
          AddCxRow( I, c, 2, 3 );
        }

        x = fabs(M[3][3]);
        if ( x < *pivot )
          *pivot = x;

        if ( x > 0.0 ) {
          rank++;

          c = 1.0/M[3][3];
          d *= c;
          ScaleRow( I, c, 3 );

          x *= MNJ_EPSILON;
          if (fabs(M[0][3]) >  x) {
            AddCxRow( I, -M[0][3], 3, 0 );
          }
          if (fabs(M[1][3]) >  x) {
            AddCxRow( I, -M[1][3], 3, 1 );
          }
          if (fabs(M[2][3]) >  x) {
            AddCxRow( I, -M[2][3], 3, 2 );
          }

          *determinant = (swapcount%2) ? -d : d;
        }
      }
    }
  }

  if ( col[3] != 3 )
    SwapRow( I, 3, col[3] );
  if ( col[2] != 2 )
    SwapRow( I, 2, col[2] );
  if ( col[1] != 1 )
    SwapRow( I, 1, col[1] );
  if ( col[0] != 0 )
    SwapRow( I, 0, col[0] );

  memcpy( dst, I, sizeof(I) );
	return rank;
}

//For[][] is used for converting new coordinate to original coordinate
//Inv[][] is used for converting original coordinate to new coordinate
//ni,nj,nk is the z-axis for new coordinate represented by original coordinate;
//xi,xj,xk is the x-axis for new coordinate represented ny original coordinate;
/*inline void ICSOS::CreateTrans(float InvK[3][3], float ForK[3][3], float ni, float nj, float nk, float xi, float xj, float xk)
{
	float tmplength = sqrt(xi*xi+xj*xj+xk*xk);
	xi = xi/tmplength;
	xj = xj/tmplength;
	xk = xk/tmplength;
	tmplength = sqrt(ni*ni+nj*nj+nk*nk);
	ni = ni/tmplength;
	nj = nj/tmplength;
	nk = nk/tmplength;

//	xi = 1.0; xj = 0.0; xk = 0.0;
	ForK[0][0] = xi;
	ForK[1][0] = xj;
	ForK[2][0] = xk;

	ForK[0][1] = nj*xk - nk*xj;
	ForK[1][1] = -(ni*xk - nk*xi);
	ForK[2][1] = ni*xj - nj*xi;

	tmplength = sqrt(ForK[0][1]*ForK[0][1] + ForK[1][1]*ForK[1][1] + ForK[2][1]*ForK[2][1]);
	if( tmplength < 0.00001 )
	{
		xi = 1.0; xj = 0.0; xk = 0.0;
		ForK[0][1] = nj*xk - nk*xj;
		ForK[1][1] = -(ni*xk - nk*xi);
		ForK[2][1] = ni*xj - nj*xi;
		tmplength = sqrt(ForK[0][1]*ForK[0][1] + ForK[1][1]*ForK[1][1] + ForK[2][1]*ForK[2][1]);
		if( tmplength < 0.00001 )
		{
			xi = 0.0; xj = 1.0; xk = 0.0;
			ForK[0][1] = -(nj*xk - nk*xj);
			ForK[1][1] = (ni*xk - nk*xi);
			ForK[2][1] = -(ni*xj - nj*xi);
			tmplength = sqrt(ForK[0][1]*ForK[0][1] + ForK[1][1]*ForK[1][1] + ForK[2][1]*ForK[2][1]);
		}
	}

	
	ForK[0][1] = ForK[0][1]/tmplength;
	ForK[1][1] = ForK[1][1]/tmplength;
	ForK[2][1] = ForK[2][1]/tmplength;

	ForK[0][2] = ni;
	ForK[1][2] = nj;
	ForK[2][2] = nk;

	ForK[0][0] = -(nj*ForK[2][1] - nk*ForK[1][1]);
	ForK[1][0] = ni*ForK[2][1] - nk*ForK[0][1];
	ForK[2][0] = -(ni*ForK[1][1] - nj*ForK[0][1]);
//calculating inverse
	InvK[0][0] = ForK[1][1]*ForK[2][2] - ForK[1][2]*ForK[2][1];
	InvK[1][0] = -(ForK[1][0]*ForK[2][2] - ForK[1][2]*ForK[2][0]);
	InvK[2][0] = ForK[1][0]*ForK[2][1] - ForK[1][1]*ForK[2][0];

	InvK[0][1] = -(ForK[0][1]*ForK[2][2] - ForK[0][2]*ForK[2][1]);
	InvK[1][1] = ForK[0][0]*ForK[2][2] - ForK[0][2]*ForK[2][0];
	InvK[2][1] = -(ForK[0][0]*ForK[2][1] - ForK[0][1]*ForK[2][0]);

	InvK[0][2] = ForK[0][1]*ForK[1][2] - ForK[0][2]*ForK[1][1];
	InvK[1][2] = -(ForK[0][0]*ForK[1][2] - ForK[0][2]*ForK[1][0]);
	InvK[2][2] = ForK[0][0]*ForK[1][1] - ForK[0][1]*ForK[1][0];

	char msgline[100];
	sprintf(msgline,"%f %f %f\n%f %f %f\n%f %f %f",ForK[0][0], ForK[0][1], ForK[0][2],ForK[1][0], ForK[1][1], ForK[1][2],ForK[2][0], ForK[2][1], ForK[2][2]);
//	::MessageBox(NULL,msgline,"forward",MB_OK);
	sprintf(msgline,"%f %f %f\n%f %f %f\n%f %f %f",InvK[0][0], InvK[0][1], InvK[0][2],InvK[1][0], InvK[1][1], InvK[1][2],InvK[2][0], InvK[2][1], InvK[2][2]);
//	::MessageBox(NULL,msgline,"Inverse",MB_OK);
*/
void GeomUtils::Translate(const dbl_3d_pt &p,
		                  const MnjVector &v,
						  dbl_3d_pt &pt ){
			 pt.x = p.x+v.x; 
			 pt.y = p.y+v.y ; 
			 pt.z = p.z+v.z;
			return;
}
//////////////////////////////////////////////////////////////////////////
bool GeomUtils::IsSame(const dbl_3d_pt &ip1,
                       const dbl_3d_pt &ip2){
   double d = GeomUtils::GetDistance(ip1,ip2);
   return ( d < MNJ_ZERO_TOLERANCE);
}
///////////////////////////////////////////////////////////////////////////
int GeomUtils::Intersect2dLineCircle(dbl_3d_pt line_from, // 2d line from point
                 dbl_3d_pt  line_to,
                 double r,
                 double tol,
                 double* t0,
                 double* t1
                 )
{
  // returns 0 = line is degenerate
  // 1 = one intersection returned, 
  // 2 = 2 intersections returned
  // 3 = 1 closest point returned
  int xcnt = 0;
  //ON_BOOL32 bRev;
  bool bRev;
  double t, d, c, s, x, y, dx, dy;
  //ON_2dVector v;
  MnjVector v;

  if ( line_from.x*line_from.x + line_from.y*line_from.y > line_to.x*line_to.x + line_to.y*line_to.y )
  {
    v = line_from;
    line_from = line_to;
    //line_to = v;
    line_to.x = v.x;
    line_to.y = v.y;

	bRev = true;
  }
  else
    bRev = false;
  dx = line_to.x - line_from.x;
  dy = line_to.y - line_from.y;
  if ( fabs(dx) >= fabs(dy) )
  {
    if ( dx == 0.0 )
    {
      *t0 = 0.0;
      *t1 = 0.0;
      return 0;
    }
    else
    {
      d = dy/dx;
      d = fabs(dx)*sqrt(1.0+d*d);
    }
  }
  else
  {
    d = dx/dy;
    d = fabs(dy)*sqrt(1.0+d*d);
  }
  c = dx/d;
  s = dy/d;

  // change coordinates so line is horizontal
  x = line_from.x; 
  y = line_from.y;
  line_from.x = c*x + s*y;
  line_from.y = c*y - s*x;

  x = line_to.x; 
  y = line_to.y;
  line_to.x = c*x + s*y;
  line_to.y = c*y - s*x;



  dx = line_to.x - line_from.x; // should be length of line
  if ( dx == 0.0 )
  {
    *t0 = 0.0;
    *t1 = 0.0;
    return 0;
  }
  dy = line_to.y - line_from.y; // should be zero
  t = -line_from.x/dx;
  x = (1.0-t)*line_from.x + t*line_to.x;
  y = (1.0-t)*line_from.y + t*line_to.y;
  d = fabs(y);
  if ( d < r-tol )
  {
    // two intersection points
    d /= r;
    d = r*sqrt(1.0-d*d);
    x = -(d + line_from.x)/dx;
    y =  (d - line_from.x)/dx;
    if ( bRev )
    {
      x = 1.0-x;
      y = 1.0-y;
    }
    if (x<=y)
    {
      *t0 = x;
      *t1 = y;
    }
    else
    {
      *t0 = y;
      *t1 = x;
    }
    xcnt = ( x == y ) ? 1 : 2;
  }
  else if ( d > r+tol )
  {
    // closest point returned
    xcnt = 3;
    if ( bRev )
      t = 1.0-t;
    *t0 = t;
    *t1 = t;
  }
  else
  {
    // one intersection point returned
    xcnt = 1;
    if ( bRev )
      t = 1.0-t;
    *t0 = t;
    *t1 = t;
  }
  return xcnt;
}
double GeomUtils::DotProduct(const MnjVector &vec1, const MnjVector &vec2){
			double val;
			val = 0.0;
			val = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

			return val;
        }

MnjVector GeomUtils::CrossProduct(const MnjVector &vec1, const MnjVector &vec2)
{
	MnjVector temp;

	temp.x = vec1.y*vec2.z - vec1.z*vec2.y;
	temp.y = vec1.z*vec2.x - vec1.x*vec2.z;
	temp.z = vec1.x*vec2.y - vec1.y*vec2.x;

	return temp;
}

 ///////////////////////////////////////////////
 int GeomUtils::GetIntersectionOfCircles2D(
            dbl_3d_pt &center1,
            double radius1,
            dbl_3d_pt &center2,
            double radius2,
            dbl_3d_pt &P1,
            dbl_3d_pt &P2){
    const double Epsilon = .0001;
            //var result = Math.InfinitePointPair;
    double x1 = center1.x;
    double y1 = center1.y;
    double x2 = center2.x;
    double y2 = center2.y;

    double r3 = GeomUtils::GetDistance(center1,center2);
    if (r3 == 0)
    {
        return -1;
    }

    if (y1 == y2)
    {
        if (radius1 + radius2 > r3 + Epsilon
            && radius1 + r3 > radius2 + Epsilon
            && radius2 + r3 > radius1 + Epsilon
            && x1 != x2)
                {
                    double x3 = (pow(radius1,2) + pow(r3,2) - pow(radius2,2)) / (2 * r3);
                    double tsqr = sqrt((pow(radius1,2)- pow(x3,2)));
                    P1.x = x1 + (x2 - x1) * x3 / r3;
                    P1.y = y1 - tsqr;
                    P2.x = P1.x;
                    P2.y = y1 + tsqr;
                    if (x2 < x1)
                    {
                        double t = P1.y;
                        P1.y = P2.y;
                        P2.y = t;
                    }
                }
                else if (fabs(radius1 + radius2 - r3) <= Epsilon)
                {
                    P1.x = x1 + (x2 - x1)/fabs(x2-x1) * radius1;
                    P1.y = y1;
                    P2 = P1;
                }
                else if (fabs(radius1 + r3 - radius2) <= Epsilon
                    ||   fabs(r3 + radius2 - radius1) <= Epsilon)
                {
                    P1.x = x1 + (x2 - x1)/fabs(x2-x1) * (radius1 - radius2)/fabs(radius1 - radius2) * radius1;
                    P1.y = y1;
                    P2 = P1;
                }
                return 0;
            }

            if (fabs(radius1 + radius2 - r3) <= Epsilon)
            {
                r3 = radius1 / r3;
                P1.x = x1 + (x2 - x1) * r3;
                P1.y = y1 + (y2 - y1) * r3;
                P2 = P1;
                return 0;
            }

            if (fabs(radius1 + r3 - radius2) <= Epsilon
                || fabs(radius2 + r3 - radius1) <= Epsilon)
            {
                r3 = radius1 / r3 * (radius1 - radius2)/fabs(radius1 - radius2);
                P1.x = x1 + (x2 - x1) * r3;
                P1.y = y1 + (y2 - y1) * r3;
                P2 = P1;
                return 0;
            }

            double k = -(x2 - x1) / (y2 - y1);
            double b = ((radius1 - radius2) * (radius1 + radius2)
                    + (x2 - x1) * (x2 + x1)
                    + (y2 - y1) * (y2 + y1))
                / (2 * (y2 - y1));
            double ea = k * k + 1;
            double eb = 2 * (k * b - x1 - k * y1);
            double ec = pow(x1,2) + pow(b,2) - 2 * b * y1 + pow(y1,2) - pow(radius1,2);
            vector<double> roots ;
            SolveSquareEquation(ea, eb, ec,roots);
            if ( roots.size() != 2)
            {
                return -1;
            }
            P1.x = roots[0];
            P1.y = roots[0] * k + b;
            P2.x = roots[1];
            P2.y = roots[1] * k + b;

            if (y2 > y1)
            {
                dbl_3d_pt t = P1;
                P1 = P2;
                P2 = t;
            }

            return 0;
 }
////////////////////////////////////////////////////////////////////////////////
            void GeomUtils::SwapRow( double matrix[4][4], int i0, int i1 )
{
  double* p0;
  double* p1;
  double t;
  p0 = &matrix[i0][0];
  p1 = &matrix[i1][0];
  t = *p0; *p0++ = *p1; *p1++ = t;
  t = *p0; *p0++ = *p1; *p1++ = t;
  t = *p0; *p0++ = *p1; *p1++ = t;
  t = *p0; *p0   = *p1; *p1 = t;
}

void GeomUtils::SwapCol( double matrix[4][4], int j0, int j1 )
{
  double* p0;
  double* p1;
  double t;
  p0 = &matrix[0][j0];
  p1 = &matrix[0][j1];
  t = *p0; *p0 = *p1; *p1 = t;
  p0 += 4; p1 += 4;
  t = *p0; *p0 = *p1; *p1 = t;
  p0 += 4; p1 += 4;
  t = *p0; *p0 = *p1; *p1 = t;
  p0 += 4; p1 += 4;
  t = *p0; *p0 = *p1; *p1 = t;
}

 //////////////////////////////////////////////////////////////////////
 void GeomUtils::ScaleRow( double matrix[4][4], double c, int i )
{
  double* p = &matrix[i][0];
  *p++ *= c;
  *p++ *= c;
  *p++ *= c;
  *p   *= c;
}

void GeomUtils::AddCxRow( double matrix[4][4], double c, int i0, int i1 )
{
  const double* p0;
  double* p1;
  p0 = &matrix[i0][0];
  p1 = &matrix[i1][0];
  *p1++ += c* *p0++;
  *p1++ += c* *p0++;
  *p1++ += c* *p0++;
  *p1   += c* *p0;
}
///
 int GeomUtils::SolveSquareEquation(
            double a,
            double b,
            double c,
            vector<double> &result){
            
            int error = 0;
            double d = b * b - 4 * a * c;
            if (a == 0)
            {
                return -1;
            }

            if (d > 0)
            {
                d = sqrt(d);
                a *= 2;
                result.push_back((-b - d) / a);
                result.push_back((d - b) / a);
            }
            else if (d == 0)
            {
                result.push_back(-b / (2 * a));
            }
            return error;
 }
 /////////////////////////////////////////////////////////////////////
 void GeomUtils::GetFarEndOfOtherLine( 
	const std::shared_ptr<MnjLine> &l1,
	const std::shared_ptr<MnjLine> &l2,
	      dbl_3d_pt  &oPoint
){
		if(!l1 ||!l2) return;

		dbl_3d_pt p11;
		l1->GetStartPoint(p11);
		dbl_3d_pt p12;
		l1->GetEndPoint(p12);

		dbl_3d_pt p21;
		l2->GetStartPoint(p21);
		double d1= 0;
		GeomUtils::DistancePointInfiniteLine(p21,p11,p12,d1);

		dbl_3d_pt p22;
		l2->GetEndPoint(p22);
		double d2= 0;
		GeomUtils::DistancePointInfiniteLine(p22,p11,p12,d2);
		if(d2 < d1 ) 
			oPoint = p21;
		else
			oPoint = p22;
		if(fabs(d1-d2) <.0001)//debug break
		{
			;//cout  <<  the diffrence is too small. 
		}
}
 /////////////////////////////////////////////////////////////////////////////////////////////////////
int GeomUtils::CreateArc(shared_ptr<Segment> &isimpleSeg1, 
                         shared_ptr<Segment> &isimpleSeg2, 
                         const double &ir,
	                     std::shared_ptr<MnjArc>  &arc){
	int error = 0;
	if(!isimpleSeg1 || !isimpleSeg1 || !arc ) 
        return -1;
	
    shared_ptr<MnjArc> arc1 = std::dynamic_pointer_cast<MnjArc,Segment> (isimpleSeg1);
    shared_ptr<MnjLine> line1 = std::dynamic_pointer_cast<MnjLine,Segment> (isimpleSeg1);
	shared_ptr<MnjArc> arc2 = std::dynamic_pointer_cast<MnjArc,Segment> (isimpleSeg2);
    shared_ptr<MnjLine> line2 = std::dynamic_pointer_cast<MnjLine,Segment> (isimpleSeg2);
	
	if(line1 && line2){
	   error = CreateArc(line1,line2,ir,arc);
	}
    
    else if(line1 && arc2){
	   error = CreateArc(line1,arc2,ir,arc);
	}
	else if(arc1 && line2){
	   error = CreateArc(arc1,line2,ir,arc);
	}
    else if(arc1 && arc2){
	   error = CreateArc(arc1,arc2,ir,arc);
    }
    
    return error; 
}
///////////////////////////////////////////////////////////////////////////////
int GeomUtils::CreateArc(shared_ptr<MnjLine> &seg1, 
                         shared_ptr<MnjLine> &seg2, 
                         const double &r,
	                     shared_ptr<MnjArc>  &oarc){
	int error = 0;
     //input valdation 
	if(!seg1||!seg2)
		return -1; 
    if(0.0 == r) 
	   return -1;
	shared_ptr<MnjLine> parallel_seg1(new MnjLine());
	dbl_3d_pt  hintpoint1;
	GetFarEndOfOtherLine(seg1,seg2,hintpoint1);
	seg1->CreateParallelLine(r, hintpoint1, parallel_seg1);

	shared_ptr<MnjLine> parallel_seg2(new MnjLine());
	dbl_3d_pt  hintpoint2;
	GeomUtils::GetFarEndOfOtherLine(seg2,seg1,hintpoint2);
    seg2->CreateParallelLine(r, hintpoint2, parallel_seg2);
    
	if(parallel_seg1){
		dbl_3d_pt center;
		parallel_seg1->Intersect(*parallel_seg2,center);
		dbl_3d_pt  p1;
		if( -1 == seg1->Project(center,p1) )
			return error = -21;
		dbl_3d_pt p2;
		if( -1 == seg2->Project(center,p2) ) 
			return error = -22;
        //set the values into the segments
        dbl_3d_pt cornerPoint = seg1->GetCommonPoint(seg2,error);

        seg1->ResetThePoint(cornerPoint,p1);
        oarc->Set(p1,center,p2);
        seg2->ResetThePoint(cornerPoint,p2);

	}
   return 0;
  
}
///////////////////////////////////////////////////////////
int GeomUtils::CreateArc( 
	shared_ptr<MnjArc> &a,
	shared_ptr<MnjLine> &l,
  const double &r,
	shared_ptr<MnjArc> &oarc){
  
   return CreateArc(l,a, r, oarc);

}
/////////////////////////////////////////////////////////////
int GeomUtils::CreateArc( 
	shared_ptr<MnjLine> &l,
	shared_ptr<MnjArc> &a,
  const double &ir,
	shared_ptr<MnjArc> &oarc){
  
   dbl_3d_pt cp ;
   int error= GetCenter(l,a,ir,cp);
   if(error>=0){
        dbl_3d_pt pt_on_a;
        error = a->Project(cp,pt_on_a);
        if(error>=0){
            dbl_3d_pt pt_on_l;
            error = l->Project(cp,pt_on_l);
            if(error>=0){
                dbl_3d_pt cornerPoint = l->GetCommonPoint(a,error);
                l->ResetThePoint(cornerPoint,pt_on_l);
                a->ResetThePoint(cornerPoint,pt_on_a);
                oarc->SetSmallerArc(pt_on_a,cp,pt_on_l);
            }
       }
  }
  return error;
}
////////////////////////////////////////////////////////////////////////
int GeomUtils::GetCenter(
    shared_ptr<MnjLine> &l,
	shared_ptr<MnjArc> &a,
	const double &ir,
	dbl_3d_pt &ocp
    ){
        int error =0;
        //Create Circle 
        dbl_3d_pt commonPoint = l->GetCommonPoint(a,error);
        MnjDirection  tangent= a->TangentAtEnd(commonPoint);
        int factor = 1;
        dbl_3d_pt otherEndOfLine = l->GetOtherEnd(commonPoint,error);
        if(tangent.IsObtuse(MnjDirection(commonPoint,otherEndOfLine))) 
            factor = -1; 
         
        MnjCircle tmpCircle(a);
        double R = a->GetRadius();
        double tmpCicrleR = R+factor*ir;
        tmpCircle.SetRadius(tmpCicrleR);

        //Create Line
        dbl_3d_pt pTowardsArc;
        error = GetAPointTowardsArc(l,a,pTowardsArc); 
        shared_ptr<MnjLine> parallel_line;
        l->CreateParallelLine(ir,pTowardsArc,parallel_line);
        //Take Intersection
        MnjInfiniteLine inf_parallel_line(&(*parallel_line));
        shared_ptr_vec_pt pt_vec;
        tmpCircle.Intersect(inf_parallel_line,pt_vec);
        if(1==pt_vec.size()){ 
             ocp = *pt_vec[0]; 
             return 1;
        }else if (0==pt_vec.size()) {
            return -1;
        } 
        //Select valid Intersection point 
        //The (center point of new arc) point must qualify these conditions:
        // 1. It should project on line segment.
        // 2. the distance between the point and arc a == r

        shared_ptr_vec_pt can_project_pt_vec;
        GeomUtils::GetPointsThatProjectOnLineSegment(*l,  
                                                    pt_vec,
                                                    can_project_pt_vec);
        if(1==can_project_pt_vec.size()){ 
            ocp = *can_project_pt_vec[0]; 
            return 11;
        } else if (0==can_project_pt_vec.size()) {
            return -2;
        }
        //test that the point(s) are at distance r fron the circle. 
        shared_ptr_vec_pt pt_at_distance_r_from_arc_vec;
        GeomUtils::GetPointsAtGivenDistanceFromArc(*a,ir,  
                                                  can_project_pt_vec,
                                                  pt_at_distance_r_from_arc_vec);
        
        if(1==pt_at_distance_r_from_arc_vec.size()){ 
            ocp = *pt_at_distance_r_from_arc_vec[0]; 
            return 22;
        } else  {
            return -22;
        }
           return error;
}
//////////////////////////////////////////////////////////////////////////
int GeomUtils::GetAPointTowardsArc(shared_ptr<MnjLine> &l,
	                                         shared_ptr<MnjArc> &a,
                                             dbl_3d_pt &op) {
   int error = 0;
  
   dbl_3d_pt cornerPoint = l->GetCommonPoint(a,error);
   MnjDirection startTangent = a->TangentAtEnd(cornerPoint);
   op = cornerPoint + startTangent*10; 
   
   return error;
  }
//////////////////////////////////////////////////////////////////////////
 //mnj 7/23/12 
// This implemenatin uses new form of "for" loop 
//previous implementation commented.

int GeomUtils::CreateArc( 
	shared_ptr<MnjArc> &arc1,
	shared_ptr<MnjArc> &arc2,
    const double &r,
	shared_ptr<MnjArc> &oarc){

   int error = -2;//mnj
   if(!arc1||!arc2)
		return -1;
   
   MnjCircle circle1(arc1); 

   MnjCircle circle2(arc2); 

   shared_ptr_vec_pt pt_vec;
   //Increment the radii by r and Intersect
   //double r = a1->GetCornerRadius(); 

   double r1 = circle1.Radius();
   double locus_r1 = r1+r ;
   circle1.SetRadius(locus_r1);

   double r2 = circle2.Radius();
   double locus_r2 = r2+r ;
   circle2.SetRadius(locus_r2);
  
  circle1.Intersect( circle2,pt_vec);
  dbl_3d_pt c1 = circle1.Center();
  dbl_3d_pt c2 = circle2.Center();

  
  for( unsigned int i = 0; i <pt_vec.size() ; i++ ) {

       MnjLine l2(*(pt_vec[i]),c2);
       dbl_3d_pt p2 ;
       l2.GetPointOnLine(*(pt_vec[i]),r,p2);
       
       if(arc2->IsPointOnArc(p2)){
       
           MnjLine l1(*(pt_vec[i]),c1);
           dbl_3d_pt p1 ;
           l1.GetPointOnLine(*(pt_vec[i]),r,p1);
       
           if(arc1->IsPointOnArc(p1)){
               dbl_3d_pt cp = *(pt_vec[i]);
               oarc->SetSmallerArc(p1,cp,p2);
               dbl_3d_pt cornerPoint = arc1->GetCommonPoint(arc2,error);
               arc1->ResetThePoint(cornerPoint,p1);
               //oarc->Set(p1,cp,p2);
               arc2->ResetThePoint(cornerPoint,p2);
               error = 0;
               break;//tbd: what if both points qualify the criteria
           }
       
       }

   }

   return error;
}

/*void GeomUtils::GetFarEndOfOtherLine( 
	const boost::shared_ptr<MnjLine> &l1,
	const boost::shared_ptr<MnjLine> &l2,
	      MnjPoint<double>  &oPoint
){
		if(!l1 ||!l2) return;

		MnjPoint<double> p11;
		l1->GetStartPoint(p11);
		MnjPoint<double> p12;
		l1->GetEndPoint(p12);

		MnjPoint<double> p21;
		l2->GetStartPoint(p21);
		double d1= 0;
		GeomUtils::DistancePointInfiniteLine(p21,p11,p12,d1);

		MnjPoint<double> p22;
		l2->GetEndPoint(p22);
		double d2= 0;
		GeomUtils::DistancePointInfiniteLine(p22,p11,p12,d2);
		if(d2 < d1 ) 
			oPoint = p21;
		else
			oPoint = p22;
		if(fabs(d1-d2) <.0001)//debug break
		{
			;//cout  <<  the diffrence is too small. 
		}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
 int GeomUtils::GetPointsAtGivenDistanceFromArc(MnjArc &ia, 
                    const double &ir, 
                    shared_ptr_vec_pt  &ipt_vec,
                    shared_ptr_vec_pt  &opt_at_distance_r_from_arc_vec){
    int error = 0;
    if (ipt_vec.size() < 1 ) error = -1; 

      for (unsigned int i = 0 ; i < ipt_vec.size(); i++ ) {
        //double tmp=0;
        double tmpD = ia.Distance(*ipt_vec[i],error);
        if(fabs(tmpD-ir)<.0001){
            if(ia.PointProjectOnArc(*ipt_vec[i],error)){
               opt_at_distance_r_from_arc_vec.push_back(ipt_vec[i]);
            }
        }
    }
    return error;
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////
int GeomUtils::GetPointsThatProjectOnLineSegment(MnjLine &il,  
                                                 shared_ptr_vec_pt  &ipt_vec,
                                                 shared_ptr_vec_pt &ocan_project_pt_vec){

    int error = 0;
    if (ipt_vec.size() < 1 ) error = -1; 
    for (unsigned int i = 0 ; i < ipt_vec.size(); i++ ) {
        dbl_3d_pt tmpPoint;
        int tmpErr = il.Project(*ipt_vec[i],tmpPoint);
        if(tmpErr>=0){
            ocan_project_pt_vec.push_back(ipt_vec[i]);
        }
    }
    return error;

 }

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//CodeImp:make it a function template 
//Manoj 7/12/2012
list<shared_ptr<MnjSmoothableSegment>>::iterator GeomUtils::NextIter( list<shared_ptr<MnjSmoothableSegment>> &l,
                                                                       list<shared_ptr<MnjSmoothableSegment>>::iterator it){
       //if(Circulable(l))
       {

            if(l.end() == it) 
                return it = l.begin();
       
            it++;
       
            if(l.end() == it) 
                return it = l.begin();
            else 
                return it;
       }
       //else{
       //   return ++it;
       //}
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////
list<shared_ptr<MnjSmoothableSegment>>::iterator GeomUtils::PrevIter( list<shared_ptr<MnjSmoothableSegment>> &l,
                                                                       list<shared_ptr<MnjSmoothableSegment>>::iterator it){
  //if(Circulable(l))
  {
      if(l.begin() == it) 
           it = l.end();
       it--;
       return it;
  }
  //else{
     //  if(l.begin()!=it)
     //  return --it;
  //}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
