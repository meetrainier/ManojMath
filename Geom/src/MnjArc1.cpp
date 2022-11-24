#ifdef __AAAAAA
#include <vector>
//Local includes 
#include "Segment.h"
#include "Arc.h"
#include "MnjLine.h"
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
///////////////////////////////////////////////////////////////////////////////
void CreateArc( 
	boost::shared_ptr<Line> &seg1,
	boost::shared_ptr<Line> &seg2,
	double r, 
	boost::shared_ptr<Arc> &oarc){

	boost::shared_ptr<Line> parallel_seg1(new Line());
	MnjPoint<double>  hintpoint1;
	GetFarEndOfOtherLine(seg1,seg2,hintpoint1);
	seg1->CreateParallelLine(r, hintpoint1, parallel_seg1);

	boost::shared_ptr<Line> parallel_seg2(new Line());
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

	boost::shared_ptr<Line> parallel_seg1(new Line());
	MnjPoint<double>  hintpoint1;
	GetFarEndOfOtherLine(seg1,seg2,hintpoint1);
	seg1->CreateParallelLine(r, hintpoint1, parallel_seg1);

	boost::shared_ptr<Line> parallel_seg2(new Line());
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
	
	boost::shared_ptr<Segment> simpleSeg1;
	boost::shared_ptr<Segment> simpleSeg2;
	GetSimplifiedSegments(segVec,r, simpleSeg1,simpleSeg2); 
	
	boost::shared_ptr<Arc> arc1 = boost::dynamic_pointer_cast<Arc,Segment> (segVec[index]);
    boost::shared_ptr<Line> line1 = boost::dynamic_pointer_cast<Line,Segment> (segVec[index]);
	
	boost::shared_ptr<Arc> arc2 = boost::dynamic_pointer_cast<Arc,Segment> (segVec[index+1]);
    boost::shared_ptr<Line> line2 = boost::dynamic_pointer_cast<Line,Segment> (segVec[index+1]);
	
	
	CreateArc(line1,line2,r,oarc);

	//CreateArc(line1,arc2,r,oarc);
	//CreateArc(arc1,line1,r,oarc);
	//CreateArc(arc1,arc2,r,oarc);


}

//int LineLineIntersect(
  // MnjPoint<double> & p1,MnjPoint<double> & p2,MnjPoint<double> & p3,MnjPoint<double> & p4,MnjPoint<double> & pa,MnjPoint<double> & pb,
   //double *mua, double *mub);

///////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	vector<boost::shared_ptr<Segment>> segVec;
	MnjPoint<double> x1(10,0,0);
	MnjPoint<double> y1(0,10,0);
	MnjPoint<double> o(0,0,0);
	boost::shared_ptr<Line>  l1(new Line(x1,o));
	boost::shared_ptr<Line>  l2(new Line(o,y1));

	unsigned int index =0; 
	
	double r=5;
	boost::shared_ptr<Arc> arc(new Arc());
	segVec.push_back(l1);
	segVec.push_back(l2);
	CreateArc(segVec, index, r,  arc);
	
	arc->Print();
	return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////

/*
int main()
{
    typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;

    polygon green, blue;

    boost::geometry::read_wkt(
        "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
            "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))", green);

    boost::geometry::read_wkt(
        "POLYGON((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5))", blue);

    std::deque<polygon> output;
    boost::geometry::intersection(green, blue, output);

    int i = 0;
    std::cout << "green && blue:" << std::endl;
    BOOST_FOREACH(polygon const& p, output)
    {
        std::cout << i++ << ": " << boost::geometry::area(p) << std::endl;
    }

    
    return 0;
}
*/
#endif 
