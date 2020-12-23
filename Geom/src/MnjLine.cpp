/*
//copyright(c) 2009- 2016 Manoj Lnu 
7/12/2012 :Manoj : bug_fix, now, void CreateParallelLine( double r,const MnjPoint<double>  &p,boost::shared_ptr<MnjLine> &l) creates a new
                   smart pointer and returns it. 
29Sep 2016: Manoj : Some member function were made const
                   */
#include <cmath> 
#include <memory> 
#include "MnjOperators.h"
#include "MnjLine.h"
#include "MnjInfiniteLine.h" 
#include "MnjPoint.h"
#include "MnjDirection.h"
#include "MnjVector.h"
#include "Mnj4x4Matrix.h"
#include "GeomUtils.h"

using namespace std; 

MnjLine::MnjLine(MnjPoint<double> &s, MnjPoint<double> &e){
	startPoint = s;
	endPoint = e;
}
/////////////////////////////////////////////////////////
MnjLine::MnjLine(Segment &iSeg1, Segment &iSeg2){
	MnjPoint<double> startPoint;
	iSeg1.GetStartPoint(startPoint);
	SetStartPoint(startPoint);

	MnjPoint<double> endPoint;
	iSeg2.GetEndPoint(endPoint);
	SetEndPoint(endPoint);
}
////////////////////////////////////////////////////////
void MnjLine::Set(MnjPoint<double> &s,MnjPoint<double> &e){
	SetStartPoint(s);
	SetEndPoint(e);
}
///////////////////////////////////////////////////////////////
MnjLine::MnjLine(std::shared_ptr<Segment> &iSeg1, std::shared_ptr<Segment>& iSeg2){
  int error = 0;
  MnjPoint<double> commonPoint = iSeg1->GetCommonPoint(iSeg2,error);
  if(error>=0){
      MnjPoint<double> p1 = iSeg1->GetOtherEnd(commonPoint,error);
      if(error>=0){
          MnjPoint<double> p2 = iSeg2->GetOtherEnd(commonPoint,error);
          if(error>=0){
              SetStartPoint(p1);
              SetEndPoint(p2);
          }
      }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////
MnjLine::MnjLine(std::shared_ptr<MnjLine> &iSeg1, std::shared_ptr<MnjLine>& iSeg2){
  int error = 0;
  MnjPoint<double> commonPoint = iSeg1->GetCommonPoint(iSeg2,error);
  if(error>=0){
      MnjPoint<double> p1 = iSeg1->GetOtherEnd(commonPoint,error);
      if(error>=0){
          MnjPoint<double> p2 = iSeg2->GetOtherEnd(commonPoint,error);
          if(error>=0){
              SetStartPoint(p1);
              SetEndPoint(p2);
          }
      }
  }
}
////////////////////////////////////////////////////////
void MnjLine::SetStartPoint(MnjPoint<double> &p){
	startPoint = p;
}
///////////////////////////////////////////////////////
void MnjLine::SetEndPoint(MnjPoint<double> &p){
	endPoint = p;
}
//////////////////////////////////////////////////////////
double MnjLine::GetMaxDistance(MnjPoint<double> &p)const{
    double d = GetDistance(p);
	return d;
}
//////////////////////////////////////////////////////////
void MnjLine::GetStartPoint(MnjPoint<double> &op)const {
	op = startPoint;
}
/////////////////////////////////////////////////////////
void MnjLine::GetEndPoint(MnjPoint<double> &op)const{
	op = endPoint;
}
/////////////////////////////////////////////////////////
double MnjLine::GetDistance(MnjPoint<double> &p)const{
	MnjPoint<double> sp ;
	GetStartPoint(sp);
	MnjPoint<double> ep ;
	GetEndPoint(ep);
	double d;
	GeomUtils::DistancePointLine(p,sp,ep,d);
	return d;
}
//////////////////////////////////////////////////////////////////////////
int MnjLine::Intersect(MnjLine &line, MnjPoint<double> &pIntersection){
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
int MnjLine::Project(const MnjPoint<double> &p, MnjPoint<double> &pProjection,double tol ){
  double LineMag;
  double U;
  //  MnjPoint<double> Intersection;
     
	MnjPoint<double> LineStart, LineEnd;
	GetEnds(LineStart,LineEnd);
  GeomUtils::GetDistance( LineEnd, LineStart, LineMag );
	if( 0.0f == LineMag ) 
		return 0;
 
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
void MnjLine::GetEnds( 
	MnjPoint<double>  &s,
	MnjPoint<double>  &e
)const{
   GetStartPoint(s);
   GetEndPoint(e);

}
///////////////////////////////////////////////////
void MnjLine::CreateParallelLine( double r,
							   const MnjPoint<double>  &p,
	                           std::shared_ptr<MnjLine> &l){

   
   MnjInfiniteLine linf(this);	
   MnjPoint<double> projection;
   linf.Project(p,projection);
   MnjVector pVec(p);
   MnjVector projectionVec(projection);
   MnjVector  v = pVec - projectionVec;
   MnjDirection dir(v);
   
   MnjPoint<double> s1;
   MnjPoint<double> e1;
   GetEnds(s1,e1);
   MnjPoint<double> s;
   GeomUtils::Translate(s1,dir*r,s);
   //s1 + dir*r;
   MnjPoint<double> e ; 
   //e1 + dir*r ; 
   GeomUtils::Translate(e1,dir*r,e);
   //l->Set(s,e);
   std::shared_ptr<MnjLine> ltmp(new MnjLine(s,e));
   l = ltmp;
   
}
////////////////////////////////////////////////////////////////////////////////////
#if _DEBUG 
void MnjLine::Print(void)const{

  cout << "Line: ";
  cout << "\tstart: ";
  startPoint.Print();
  cout << "\tend: ";
  endPoint.Print();

}
#endif

void MnjLine::GetFarEndOfOtherLine( 
	const  shared_ptr &l1,
	const  shared_ptr &l2,
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
///////////////////////////////////////////////////////////////////////////////////
MnjPoint<double> MnjLine::GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const{

  oerror = 0;
  if(GeomUtils::IsSame(startPoint,ip)){
      return MnjPoint<double>(endPoint);
  }
  else if(GeomUtils::IsSame(endPoint,ip)) {
      return MnjPoint<double>(startPoint);
  }else{
      oerror = -1;
      return MnjPoint<double>(endPoint);
  }
      
}
////////////////////////////////////////////////////////////////////////////////////
int MnjLine::GetPointOnLine(const MnjPoint<double>  &eitherEnd,
                            const double &distance_from_arg1,
                                   MnjPoint<double> &opt_on_line)const {
		int error = 0;
		auto factor = distance_from_arg1/GetLength();
		if(factor > 1 || factor < 0){
			error = -2;
        }
		else{
            MnjPoint<double> otherEnd= GetOtherEnd(eitherEnd,error);
			MnjVector v = MnjVector(eitherEnd) + (MnjVector(otherEnd) - MnjVector(eitherEnd))*factor;
			opt_on_line.Set(v.x,v.y,v.z);
		}
		return error;
}
///////////////////////////////////////////////////////////////////////////////
MnjInfiniteLine MnjLine::GetPerpendicularBisector(const MnjPoint<double> &ipt_not_on_line,
                                                    int error){
 // tbd:return error when the point is not on line

  MnjPoint<double> m;
	GetMiddlePoint(m);
	MnjDirection dirAlongThisLine(startPoint,endPoint);
	
  MnjInfiniteLine thisLineAsInf(this);
  MnjPoint<double> projectedPt;
	thisLineAsInf.Project(ipt_not_on_line,projectedPt);
	
  MnjDirection dir(projectedPt,ipt_not_on_line);
	return MnjInfiniteLine(m,dir);
//tbd?	GetParallelLine();

}
///////////////////////////////////////////////////////////////////////////////
void MnjLine::GetPerpendicularAt(const MnjPoint<double> &ieitherEnd,
                                 const double &idistance_from_start,
                                       MnjInfiniteLine &operp_line){

  MnjPoint<double> p;
	GetPointOnLine(ieitherEnd,idistance_from_start,p);
	MnjInfiniteLine lInf;
	GetPerpendicularBisector(lInf);
	auto dir = lInf.GetDirection();
	operp_line.Set(p,dir);

}

//////////////////////////////////////////////////////////////////////////////////
int MnjLine::GetAPointNotOnLine(MnjPoint<double> &o_pt_not_on_line)const{

	MnjPoint<double> m  ;
	GetMiddlePoint(m);
	MnjDirection dirAlongThisLine(startPoint,endPoint);
	o_pt_not_on_line = m;
	
  auto tmpx = o_pt_not_on_line.x+GetLength()/10;
	o_pt_not_on_line.SetX(tmpx);
	MnjDirection tmpDir1(startPoint,o_pt_not_on_line);
	auto tmp1 = dirAlongThisLine.DotProduct(tmpDir1);

  if(tmp1!=0.0 && tmp1!=1.0){
		return 0;
	}else{
		
    auto tmpy = o_pt_not_on_line.y+GetLength()/10 ;
		o_pt_not_on_line.SetY(tmpy);
	  MnjDirection tmpDir2(startPoint,o_pt_not_on_line);
		auto tmp1 = dirAlongThisLine.DotProduct(tmpDir2);
		if(tmp1!=0.0 && tmp1!=1.0){
		  return 0;

	  }else {
		   return -1;
		}

	}

}
///////////////////////////////////////////////////////////////////
void MnjLine::GetPerpendicularBisector(MnjInfiniteLine &bisector){
	
  MnjPoint<double> m;
	GetMiddlePoint(m);
	MnjDirection dirAlongThisLine(startPoint,endPoint);
	
  MnjPoint<double> pt_not_on_line;
	int error = GetAPointNotOnLine(pt_not_on_line);
	
  MnjInfiniteLine thisLineAsInf(this);
  MnjPoint<double> projectedPt;
	thisLineAsInf.Project(pt_not_on_line,projectedPt);
	
  MnjDirection dir(projectedPt,pt_not_on_line);
	bisector.Set(m,dir);
  //tbd?	GetParallelLine();

}
/////////////////////////////////////////////////////////////////////////////////

bool MnjLine::Transform( const Mnj4x4Matrix& tr )
{
  startPoint = tr*startPoint;
  endPoint = tr*endPoint;
  return true;
}
/////////////////////////////////////////////////////////////////////////////////
MnjVector MnjLine::Direction() const
{
  return (endPoint-startPoint);
}
/////////////////////////////////////////////////////////////////////////////////
bool MnjLine::ClosestPointTo( const MnjPoint<double>& point, double *t ) const
{

  bool rc = false;
  if ( t ) {
    const MnjVector D = Direction();
    const double DoD = D.LengthSquared();
    if ( DoD > 0.0 ) {
      if ( point.DistanceTo(startPoint) <= point.DistanceTo(endPoint) ) {
        *t = ((point - startPoint)*D)/DoD;
      }
      else {
        *t = 1.0 + ((point - endPoint)*D)/DoD;
      }
      rc = true;
    }
    else {
      *t = 0.0;
    }
  }
  return rc;

}
//////////////////////////////////////////////////////////////////////////////////////////////////
MnjPoint<double> MnjLine::PointAt( double t ) const
{
  
  // 26 Feb 2003 Dale Lear
  //     Changed 
  //          return (1-t)*startPoint + t*endPoint;
  //     endPoint the following so that axis aligned lines will
  //     return exact answers for large values of t.  
  //     See RR 9683.
  const double s = 1.0-t;
  return  MnjPoint<double>( (startPoint.x == endPoint.x) ? startPoint.x : s*startPoint.x + t*endPoint.x,
                            (startPoint.y == endPoint.y) ? startPoint.y : s*startPoint.y + t*endPoint.y,
                            (startPoint.z == endPoint.z) ? startPoint.z : s*startPoint.z + t*endPoint.z 
                           );

}
//--------------------------------------------------------------------------------------------
void MnjLine::GetMiddlePoint(MnjPoint<double> &m)const{

  m.x = (startPoint.x+endPoint.x)/2;
	m.y = (startPoint.y+endPoint.y)/2;
	m.z = (startPoint.z+endPoint.z)/2;

}
//---------------------------------------------------------------------------------------------
MnjDirection MnjLine::GetPerpendicularDirection(const MnjPoint<double> &ipt_not_on_line,
                                                    int error){
 // tbd:return error when the point is not on line

  MnjPoint<double> m;
	GetMiddlePoint(m);
	MnjDirection dirAlongThisLine(startPoint,endPoint);
	
  MnjInfiniteLine thisLineAsInf(this);
  MnjPoint<double> projectedPt;
	thisLineAsInf.Project(ipt_not_on_line,projectedPt);
	
  return MnjDirection(projectedPt,ipt_not_on_line);
//tbd?	GetParallelLine();
}
/////////////////////////////////////////////////////////////////////////////////////////
 MnjInfiniteLine MnjLine::Normal(const MnjPoint<double> &ip,//a point on the line
                                 const MnjPoint<double> &iptToDefinePlane,//the normal to  line in 3d will be plane. A point input is necssary to define
                                                                    //an output line. The Point will be projected on the plane to create line.
                                       int              &error ){
    auto dir = GetPerpendicularDirection(iptToDefinePlane,error); 
    return   MnjInfiniteLine(ip,dir); 

 }
///////////////////////////////////////////////////////////////////////////////////////
int MnjLine::Partition(unsigned int n, list<std::shared_ptr<MnjLine>> &l){
    
  int error =0;
    
  if(n<=0 || l.size()> 0)
      error = -1;
  double num = n;

  if(!error){
      for(  double i = 0; i < num ; i++ ) {
          MnjPoint<double> stmp = startPoint + (endPoint -startPoint)*(i/n);
          MnjPoint<double> etmp = startPoint + (endPoint -startPoint)*((i+1)/n);
          std::shared_ptr<MnjLine> ltmp(new MnjLine(stmp,etmp));
          l.push_back(ltmp);
      }
  }
  return error;
}
///////////////////////////////////////////////////////////////////////////////
double MnjLine::GetLength(void) const{
	double d = 0;
	GeomUtils::GetDistance(startPoint,endPoint,d);
	return d;
}
///////////////////////////////////////////////////////////////////////////////
MnjPoint<double> MnjLine::StartPoint(void){  return MnjPoint<double>(startPoint); }
MnjPoint<double> MnjLine::EndPoint(void){  return MnjPoint<double>(endPoint); }
 ///////////////////////////////////////////////////////////////////////////////
  MnjDirection MnjLine::Tangent(void){
      return Direction();
	}
/*
 MnjInfiniteLine MnjLine::GetPerpendicularBisector(const MnjPoint<double> &ipt_not_on_line,
                                                    int error){
 // tbd:return error when the point is not on line

    MnjPoint<double> m;
	GetMiddlePoint(m);
	MnjDirection dirAlongThisLine(startPoint,endPoint);
	
    MnjInfiniteLine thisLineAsInf(this);
    MnjPoint<double> projectedPt;
	thisLineAsInf.Project(ipt_not_on_line,projectedPt);
	
    MnjDirection dir(projectedPt,ipt_not_on_line);
	return MnjInfiniteLine(m,dir);
//tbd?	GetParallelLine();
}
*/
 void MnjLine::Flip(void){
  MnjPoint<double> tmp = startPoint;
  startPoint  = endPoint;
  endPoint = tmp;
 }
 ///////////////////////////////////////////////////////////////////////////////
 int MnjLine::ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip){
  auto ds = GeomUtils::GetDistance(icornerPoint,startPoint);
  auto de = GeomUtils::GetDistance(icornerPoint,endPoint);
  if(ds<de){
      startPoint = ip;
  }
  else{
      endPoint = ip;
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////
MnjDirection MnjLine::TangentAtEnd(MnjPoint<double> &p){
  int oerror=0;
	MnjPoint<double> p2 = GetOtherEnd(p,oerror);
  return (p2-p);
}