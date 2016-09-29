//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
//2016/09/29: Manoj: Some member function were made const
#include "MnjSmoothableLine.h"
#include "MnjLine.h"
#include "MnjInfiniteLine.h" 
#include "MnjPoint.h"
#include "MnjDirection.h"
#include "MnjVector.h"
#include "GeomUtils.h"
#include <cmath> 

MnjSmoothableLine::MnjSmoothableLine(MnjPoint<double> &s, MnjPoint<double> &e){//,ICSAttribute& iattr){
	mline.Set(s,e);
	//SetICSAttribute(iattr);
    mstatus =MnjSmoothableSegment::UNKNOWN;
}
/////////////////////////////////////////////////////////////////
MnjSmoothableLine::MnjSmoothableLine(MnjLine &l, ICSAttribute& iattr){
	mline = l;
	SetICSAttribute(iattr);
    mstatus =MnjSmoothableSegment::UNKNOWN;
}
////////////////////////////////////////////////////////////////
/*
MnjSmoothableLine::MnjSmoothableLine(MnjSegment &iSeg1, MnjSegment &iSeg2){
	MnjPoint<double> startPoint;
	iSeg1.GetStartPoint(startPoint);
	SetStartPoint(startPoint);

	MnjPoint<double> endPoint;
	iSeg2.GetEndPoint(endPoint);
	SetEndPoint(endPoint);
}
*/
/////////////////////////////////////////////////////////////
/*
MnjSmoothableLine::MnjSmoothableLine(boost::shared_ptr<MnjSmoothableSegment> &iSeg1, boost::shared_ptr<MnjSmoothableSegment> &iSeg2,ICSAttribute &iattr){
    int error = 0;
    MnjPoint<double> commonPoint = GetCommonPoint(iSeg2,error);
    if(error>=0){
      MnjPoint<double> startPoint = iSeg1->GetOtherEnd(commonPoint,error);
      if(error>=0){
	    SetStartPoint(startPoint);

	    MnjPoint<double> endPoint;
	    iSeg2->GetEndPoint(endPoint);
	    SetEndPoint(endPoint);
	    SetICSAttribute(iattr);
      }
    }
}
*/
/////////////////////////////////////////////////////////////
MnjSmoothableLine::MnjSmoothableLine(shared_ptr&iSeg1, shared_ptr&iSeg2,
                         ICSAttribute &iAttr){

  MnjLine tmpLine(iSeg1->GetLine(),iSeg2->GetLine());
	mline = tmpLine;
	SetICSAttribute(iAttr);
    //mnj SetCorner(iSeg1->IsCorner());
    SetCornerRadius (iSeg1->GetCornerRadius());
    SetStatus(MnjSmoothableSegment::UNKNOWN);
}
/////////////////////////////////////////////////////////////
MnjSmoothableLine::MnjSmoothableLine(shared_ptr&iSeg1, shared_ptr&iSeg2,
                         //ICSAttribute &iAttr,
                         MnjSmoothableSegment::SegmentChange iStatus){
    
    MnjLine tmpLine(iSeg1->GetLine(),iSeg2->GetLine());
	mline = tmpLine;

	MergeAndSetAttributes(iSeg1,iSeg2,iStatus);

  }
////////////////////////////////////////////////////////
void MnjSmoothableLine::Set(MnjPoint<double> &s,MnjPoint<double> &e){
	SetStartPoint(s);
	SetEndPoint(e);
}


////////////////////////////////////////////////////////
void MnjSmoothableLine::SetStartPoint(MnjPoint<double> &p){
	mline.SetStartPoint(p);
}

void MnjSmoothableLine::SetEndPoint(MnjPoint<double> &p){
	//endPoint = p;
	mline.SetEndPoint(p);
}

double MnjSmoothableLine::GetMaxDistance(MnjPoint<double> &p)const{
  double d = GetDistance(p);
	return d;
}

void MnjSmoothableLine::GetStartPoint(MnjPoint<double> &op)const {
	//op = startPoint;
	 mline.GetStartPoint(op);
}

void MnjSmoothableLine::GetEndPoint(MnjPoint<double> &op)const{
	//op = endPoint;
	mline.GetEndPoint(op);
}
/*
void MnjSmoothableLine::GetNormalAtStartPoint(MnjLine &l){

}

void MnjSmoothableLine::GetNormalAtEndPoint(MnjLine &l){

}
*/
double MnjSmoothableLine::GetDistance(MnjPoint<double> &p)const{
	MnjPoint<double> sp ;
	GetStartPoint(sp);
	MnjPoint<double> ep ;
	GetEndPoint(ep);
	double d;
	GeomUtils::DistancePointLine(p,sp,ep,d);
	return d;
}
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
int MnjSmoothableLine::Intersect(MnjLine &line, MnjPoint<double> &pIntersection){
	MnjPoint<double> sp1,ep1;
	GetStartPoint(sp1);
	GetEndPoint(ep1);

	MnjPoint<double> sp2,ep2;
	line.GetStartPoint(sp2);
	line.GetEndPoint(ep2);
	int flag = GeomUtils::LineLineIntersect(sp1,ep1,sp2,ep2,pIntersection);
	return flag;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MnjSmoothableLine::Project(const MnjPoint<double> &p, MnjPoint<double> &pProjection,double tol ){
   double LineMag;
    double U;
  //  MnjPoint<double> Intersection;
     
	MnjPoint<double> LineStart, LineEnd;
	GetEnds(LineStart,LineEnd);
    GeomUtils::GetDistance( LineEnd, LineStart, LineMag );
	if( 0.0f == LineMag ) 
		return -1;
 
    U = ( ( ( p.x - LineStart.x ) * ( LineEnd.x - LineStart.x ) ) +
        ( ( p.y - LineStart.y ) * ( LineEnd.y - LineStart.y ) ) +
        ( ( p.z - LineStart.z ) * ( LineEnd.z - LineStart.z ) ) ) /
        ( LineMag * LineMag );
 
    if( U < 0.0f || U > 1.0f )
        return -1;   // closest point does not fall within the line segment
 
    pProjection.x = LineStart.x + U * ( LineEnd.x - LineStart.x );
    pProjection.y = LineStart.y + U * ( LineEnd.y - LineStart.y );
    pProjection.z = LineStart.z + U * ( LineEnd.z - LineStart.z );
	return 1;
}
////////////////////////////////////////////////////////////////
void MnjSmoothableLine::GetEnds( 
	MnjPoint<double>  &s,
	MnjPoint<double>  &e
)const{
   GetStartPoint(s);
   GetEndPoint(e);

}
///////////////////////////////////////////////////
void MnjSmoothableLine::CreateParallelLine( double r,
							   const MnjPoint<double>  &p,
	                           std::shared_ptr<MnjLine> &l){

   mline.CreateParallelLine(r,p,l);
}
/////////////////////////////////////////////////////////////////////////////////
int MnjSmoothableLine::ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip){
    return mline.ResetThePoint(icornerPoint,ip);

}
/////////////////////////////////////////////////////////////////////////////////////
void MnjSmoothableLine::Flip(void){
     mline.Flip();
}

////////////////////////////////////////////////////////////////////////////////////
#if _DEBUG 
void MnjSmoothableLine::Print(void)const{
/*cout << "MnjLine: ";
cout << "\tstart: ";
	startPoint.Print();
cout << "\tend: ";
	endPoint.Print();
*/
	mline.Print();
}
#endif

void MnjSmoothableLine::Set(const MnjSmoothableSegment &seg1,
		             const MnjSmoothableSegment &seg2){
	   MnjPoint<double> s;
	   seg1.GetStartPoint(s);
	   MnjPoint<double> e;
	   seg2.GetEndPoint(e);
	   Set(s,e);
    }
/////////////////////////////////////////////////////////////////////
std::shared_ptr<MnjLine> MnjSmoothableLine::GetLine(void)const{
	    std::shared_ptr<MnjLine> l(new MnjLine(mline));
		return  l;
}
////////////////////////////////////////////////////////////////////
MnjPoint<double> MnjSmoothableLine::GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const{
    return mline.GetOtherEnd(ip,oerror);
}
///////////////////////////////////////////////////////////////////////////
//int MnjSmoothableLine::Partition(const unsigned int &n, list<boost::shared_ptr<MnjSmoothableLine>> &ol){
int MnjSmoothableLine::Partition(const unsigned int &n, list<std::shared_ptr<MnjSmoothableSegment>> &ol){
    int error =0;
    list<std::shared_ptr<MnjLine>> lineList;
    mline.Partition(n, lineList);
    list<std::shared_ptr<MnjLine>>::iterator it = lineList.begin();
    
    ICSAttribute attr;
    GetICSAttribute(attr);
    
    for ( ;it!= lineList.end(); it++ ) {
        ol.push_back(std::shared_ptr<MnjSmoothableLine>(new MnjSmoothableLine(**it,attr)));
    }
    return error;
}
/////////////////////////////////////////////////////////////////////
std::shared_ptr<Segment> MnjSmoothableLine::GetSegment(void){
    return GetLine();
}