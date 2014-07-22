#ifdef __AAAAA
#include <vector>
//Local includes 
//#include "MnjSmoothableSegment.h"
#include "MnjArc.h"
#include "MnjLine.h"
#include "MnjPoint.h" 
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "GeomUtils.h"
////////////////////////////////////////////
#include <iostream>
#include <deque>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
//#include <boost/geometry/domains/gis/io/wkt/wkt.hpp>

#include <boost/foreach.hpp>
////////////////////////////////////////////////////////
using namespace std; 
using namespace boost; 

//tbd:
void GetSimplifiedSegments(vector<boost::shared_ptr<Segment>> segVec,
	     const double r,
	boost::shared_ptr<Segment> &seg1,
	boost::shared_ptr<Segment> &seg2 ){

		if( 2 == segVec.size() ) 
		seg1 = segVec[0];
		seg2 = segVec[1];
		/*
		if (seg1.GetLength() >  r ) {

		}
		*/
}

////////////////////////////////////////////////////////////////////////////
void CreateParallelLine( 
	boost::shared_ptr<MnjLine> &seg1,
	double r,
	const MnjPoint<double>  &hintpoint1,
	boost::shared_ptr<MnjLine> &seg2){
		

}
/*
///////////////////////////////////////////////////////////////////////////////
void GetFarEndOfOtherLine( 
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
		GeomUtils::DistancePointLine(p21,p11,p12,d1);

		MnjPoint<double> p22;
		l2->GetEndPoint(p22);
		double d2= 0;
		GeomUtils::DistancePointLine(p22,p11,p12,d2);
		if(d2 < d1 ) 
			oPoint = p21;
		else
			oPoint = p22;
}
*/
///////////////////////////////////////////////////////////////////////////////
void CreateArc( 
	boost::shared_ptr<MnjLine> &seg1,
	boost::shared_ptr<MnjLine> &seg2,
	double r, 
	boost::shared_ptr<MnjArc> &oarc){

	boost::shared_ptr<MnjLine> parallel_seg1(new MnjLine());
	MnjPoint<double>  hintpoint1;
	GetFarEndOfOtherLine(seg1,seg2,hintpoint1);
	seg1->CreateParallelLine(r, hintpoint1, parallel_seg1);

	boost::shared_ptr<MnjLine> parallel_seg2(new MnjLine());
	MnjPoint<double>  hintpoint2;
	GetFarEndOfOtherLine(seg2,seg1,hintpoint2);
	seg2->CreateParallelLine(r, hintpoint2, parallel_seg2);
    //CreateParallelLine(seg2,r, hintpoint2, parallel_seg2);
    
	if(parallel_seg1){
		MnjPoint<double> center;
		parallel_seg1->Intersect(*parallel_seg2,center);
		MnjPoint<double>  p1;
		seg1->Project(center,p1);
		MnjPoint<double> p2;
		seg2->Project(center,p2);
		oarc->Set(p1,center,p2);
	}

}

/*
1. Create Arc: 

Steps:
1. Get mid-point of the arc seg1 and seg2: m1,m2
2. Get l1 = the perpendicular bisector of   m1-m2 
3. Get p1 = perpendicular to tangent at m1
4. Get int_p1 = l1 and p1 intersection point
5. P21 = start point of seg2
   P22 = end point of seg2
   d21 = distance (P21,int_p1 );
   d22 = distance (P22,int_p1 );
6. r1 = distance (m1,int_p1 );
   if (r1 is in range [d22 , d21] ) 
    Get point pm2 on seg2 where distance (pm2,int_p1 ) == r1
	else 
	   go to setp5 and repeat similar steps switching roles seg1 and seg2
	   if(solution not found)
	      retrun error or return a non- tangent arc ?  
*/
/*
void CreateArc( 
	boost::shared_ptr<Arc> &seg1,
	boost::shared_ptr<Arc> &seg2,
	double r, 
	boost::shared_ptr<Arc> &oarc){

	boost::shared_ptr<MnjLine> parallel_seg1(new Line());
	MnjPoint<double>  hintpoint1;
	GetFarEndOfOtherLine(seg1,seg2,hintpoint1);
	seg1->CreateParallelLine(r, hintpoint1, parallel_seg1);

	boost::shared_ptr<MnjLine> parallel_seg2(new Line());
	MnjPoint<double>  hintpoint2;
	GetFarEndOfOtherLine(seg2,seg1,hintpoint2);
	seg2->CreateParallelLine(r, hintpoint2, parallel_seg2);
    //CreateParallelLine(seg2,r, hintpoint2, parallel_seg2);
    
	if(parallel_seg1){
		MnjPoint<double> center;
		parallel_seg1->Intersect(*parallel_seg2,center);
		MnjPoint<double>  p1;
		seg1->Project(center,p1);
		MnjPoint<double> p2;
		seg2->Project(center,p2);
		oarc->Set(p1,center,p2);
	}

}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
segVec: a sequence of arc and lines defining a curve/profile. Segment is base class for line and arc.   
index = Location of the segment in segVec that ends at the corner
r = desired radius
orc = output arc
*/
void CreateArc(vector<boost::shared_ptr<Segment>> segVec, 
			   unsigned int index, 
			   double r, 
	           boost::shared_ptr<Arc> &oarc){
	
	boost::shared_ptr<FlowSegment> simpleSeg1;
	boost::shared_ptr<FlowSegment> simpleSeg2;
	GetSimplifiedSegments(segVec,r, simpleSeg1,simpleSeg2); 
	
	boost::shared_ptr<MnjArc> arc1 = boost::dynamic_pointer_cast<MnjArc,FlowSegment> (segVec[index]);
    boost::shared_ptr<MnjLine> line1 = boost::dynamic_pointer_cast<MnjLine,FlowSegment> (segVec[index]);
	
	boost::shared_ptr<MnjArc> arc2 = boost::dynamic_pointer_cast<MnjArc,FlowSegment> (segVec[index+1]);
    boost::shared_ptr<MnjLine> line2 = boost::dynamic_pointer_cast<MnjLine,FlowSegment> (segVec[index+1]);
	
	
	CreateArc(line1,line2,r,oarc);

	//CreateArc(line1,arc2,r,oarc);
	//CreateArc(arc1,line1,r,oarc);
	//CreateArc(arc1,arc2,r,oarc);


}

//int LineLineIntersect(
  // MnjPoint<double> & p1,MnjPoint<double> & p2,MnjPoint<double> & p3,MnjPoint<double> & p4,MnjPoint<double> & pa,MnjPoint<double> & pb,
   //double *mua, double *mub);

///////////////////////////////////////////////////////////////////////////////////////////
/*
int main()
{
	vector<boost::shared_ptr<FlowSegment>> segVec;
	MnjPoint<double> x1(10,0,0);
	MnjPoint<double> y1(0,10,0);
	MnjPoint<double> o(0,0,0);
	boost::shared_ptr<MnjLine>  l1(new MnjLine(x1,o));
	boost::shared_ptr<MnjLine>  l2(new MnjLine(o,y1));

	unsigned int index =0; 
	
	double r=5;
	boost::shared_ptr<MnjArc> arc(new MnjArc());
	segVec.push_back(l1);
	segVec.push_back(l2);
	CreateArc(segVec, index, r,  arc);
	
	arc->Print();
	return 0;
}
*/


////////////////////////////////////////////////////////////////////////////////////////////
#endif
