////////////////////////////////////////////////////////////
///
//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
///     Subsystem : None
///     Author : Manoj Lnu
///     Date : 4/23/2012
///
///		
///
////////////////////////////////////////////////////////////
//29Sep 2016: Manoj: Some member function were made const
#include <iostream>
#include <exception>
#include <typeinfo> 
using namespace std;

//#include "Segment.h"
#include "MnjSmoothableArc.h"
#include "MnjPoint.h"
#include "GeomUtils.h"
#include "MnjSmoothableLine.h"

MnjSmoothableArc::MnjSmoothableArc(MnjPoint<double> &ip1, MnjPoint<double> &center,MnjPoint<double> &ip2
 //, ICSAttribute &iattr
 ){
	
	  marc.Set(ip1,center,ip2);
	 // SetICSAttribute(iattr);
	  SetStatus(MnjSmoothableSegment::UNKNOWN);

}
/////////////////////////////////////////////////////////////////////////////////////////////////
MnjSmoothableArc::MnjSmoothableArc(MnjArc &iarc//, ICSAttribute &iattr
 ){
	
	  marc = iarc;
	  //SetICSAttribute(iattr);
	  SetStatus(MnjSmoothableSegment::UNKNOWN);

}
/////////////////////////////////////////////////////////////////////////////////////////////////
MnjSmoothableArc::MnjSmoothableArc(const std::shared_ptr<MnjSmoothableArc> &iSeg1, 
                                   const std::shared_ptr<MnjSmoothableArc> &iSeg2,
                                   //ICSAttribute &iAttr,             
                                    MnjSmoothableSegment::SegmentChange iStatus){
  try {
    
   MnjArc tmpArc(iSeg1->GetArc(0),iSeg2->GetArc(0));
   marc = tmpArc;
  
  }catch(std::exception e) {
   
   throw e;
  
  }
	
  MergeAndSetAttributes(iSeg1,iSeg2,iStatus);
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////
MnjSmoothableArc::MnjSmoothableArc(const std::shared_ptr<MnjSmoothableLine> &iSeg1,
                                   const std::shared_ptr<MnjSmoothableArc> &iSeg2,
                         //ICSAttribute &iAttr,
                         MnjSmoothableSegment::SegmentChange iStatus){
    
    MnjArc tmpArc(iSeg1->GetLine(),iSeg2->GetArc(0));
	
	marc = tmpArc;
    MergeAndSetAttributes(iSeg1,iSeg2,iStatus);
    /*
    SetICSAttribute(iSeg1,iSeg2);

    SetCorner(iSeg1->IsCorner());
    SetCornerRadius (iSeg1->GetCornerRadius());
    SetStatus(iStatus);
    */
  }
/////////////////////////////////////////////////////////////
MnjSmoothableArc::MnjSmoothableArc(const std::shared_ptr<MnjSmoothableArc> &iSeg1,
                                   const std::shared_ptr<MnjSmoothableLine> &iSeg2,
                         //ICSAttribute &iAttr,
                         MnjSmoothableSegment::SegmentChange iStatus){
    
    MnjArc tmpArc(iSeg1->GetArc(0),iSeg2->GetLine());
	
	marc = tmpArc;
    MergeAndSetAttributes(iSeg1,iSeg2,iStatus);
    /*
    SetICSAttribute(iSeg1,iSeg2);

    SetCorner(iSeg1->IsCorner());
    SetCornerRadius (iSeg1->GetCornerRadius());
    SetStatus(iStatus);
    */
  }
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/*MnjSmoothableArc::MnjSmoothableArc(boost::shared_ptr<MnjICSLine> &iSeg1, boost::shared_ptr<MnjSmoothableArc> &iSeg2,
                         ICSAttribute &iAttr){

    MnjSmoothableArc tmpArc(iSeg1->GetLine(),iSeg2->GetArc());
	marc = tmpArc;
	SetICSAttribute(iAttr);
    SetCorner(iSeg1->IsCorner());
    SetCornerRadius (iSeg1->GetCornerRadius());
    SetStatus(MnjICSSegment::UNKNOWN);
}
*/
////////////////////////////////////////////////////////////////////////////////////////////
int MnjSmoothableArc::Set(MnjPoint<double> &s,MnjPoint<double> &c,MnjPoint<double> &e){
	//op = startPoint;
	return marc.Set(s,c,e);
}
////////////////////////////////////////////////////////////////////////////////////////////
 int MnjSmoothableArc::SetSmallerArc(MnjPoint<double> &e1,MnjPoint<double> &c,MnjPoint<double> &e2){
return marc.SetSmallerArc(e1,c,e2);
//mnj return 0;
 }

////////////////////////////////////////////////////////////////////////////////////////////
void MnjSmoothableArc::GetStartPoint(MnjPoint<double> &op)const{
	//op = startPoint;
	marc.GetStartPoint(op);
}

void MnjSmoothableArc::GetCenter(MnjPoint<double> &oc){
	//oc = centerPoint;
	marc.GetCenter(oc);
}
//////////////////////////////////////////////////////////////////////////
void MnjSmoothableArc::GetEnds(MnjPoint<double> &s, MnjPoint<double> &e)const {
	GetStartPoint(s);
	GetEndPoint(e); 
}

void MnjSmoothableArc::GetArc(MnjArc &oarc)const {
  oarc=marc;
}


void MnjSmoothableArc::GetEndPoint(MnjPoint<double> &op)const{
	//op = endPoint;
	marc.GetEndPoint(op);
}
void MnjSmoothableArc::SetStartPoint(MnjPoint<double> &p){
	//startPoints = p;
	marc.SetStartPoint(p);
}

void MnjSmoothableArc::SetCenter(MnjPoint<double> &p){
	//centerPoint = p;
	marc.SetCenter(p);
}

void MnjSmoothableArc::SetEndPoint(MnjPoint<double> &p){
	marc.SetEndPoint(p);
}


double MnjSmoothableArc::GetMaxDistance(MnjPoint<double> &p)const{
	return -1;//tbd
}

//void MnjSmoothableArc::GetNormalAtStartPoint(MnjLine &l){}

//void MnjSmoothableArc::GetNormalAtEndPoint(MnjLine &l){}
/////////////////////////////////////////////////////////////////////////////////////////
double MnjSmoothableArc::GetRadius(void){
	return marc.GetRadius();;
}
 /////////////////////////////////////////////////////////////////////////////////////////
#if _DEBUG 
	void MnjSmoothableArc::Print(void)const{
		marc.Print();
	}
#endif 

int MnjSmoothableArc::Intersect(MnjInfiniteLine &il, shared_ptr_vec_pt &opt_vec){
	return	marc.Intersect(il,opt_vec);
	
}
///////////////////////////////////////////////////////////////////////////////////

int MnjSmoothableArc::ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip){
      return marc.ResetThePoint(icornerPoint,ip);
}
 /////////////////////////////////////////////////////////////////////////////////
  void MnjSmoothableArc::Flip(void){
       marc.Flip();
}
 /////////////////////////////////////////////////////////////////////////////////
 double MnjSmoothableArc::GetCharacteristic() const { 
        return marc.GetLength();  
}
 ////////////////////////////////////////////////////////////////////////////////////////////////
 MnjPoint<double> MnjSmoothableArc::GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const{
     return marc.GetOtherEnd(ip,oerror);
     /*oerror = 0;
      if(GeomUtils::IsSame(startPoint,ip)){
          return MnjPoint<double>(endPoint);
      }
      else if(GeomUtils::IsSame(endPoint,ip)) {
          return MnjPoint<double>(startPoint);
      }else{
          oerror = -1;
          return MnjPoint<double>(endPoint);
      }
      */
  }
 //////////////////////////////////////////////////////////////////////////////////////////////////
 int MnjSmoothableArc::Project(MnjPoint<double> &ip,MnjPoint<double> &op) {
		
    int error =0;
    MnjArc arc = GetArc();
    error = arc.Project(ip,op);
    /*
    double r = arc.GetRadius();
    MnjPoint<double>  centerPoint = arc.GetCenter();
    double d = GeomUtils::GetDistance(ip,centerPoint);
    op = centerPoint + MnjDirection(centerPoint,ip)*r;
    if(!arc.IsPointOnArc(op) ) error = -1;
    */
    return error;
}
 ///////////////////////////////////////////////////////////////////////////////////////////////////
 std::shared_ptr<MnjArc> MnjSmoothableArc::GetArc(int dummy)const{
	   std::shared_ptr<MnjArc> a(new MnjArc(marc));
       return a;
}
 ///////////////////////////////////////////////////////////////////////////////////////////////////////
//int MnjSmoothableArc::Partition(const unsigned int &n, list<boost::shared_ptr<MnjSmoothableArc>> &ol){
int MnjSmoothableArc::Partition(const unsigned int &n, list<std::shared_ptr<MnjSmoothableSegment>> &ol){
    int error =0;
    list<std::shared_ptr<MnjArc>> arcList;
    marc.Partition(n, arcList);
    list<std::shared_ptr<MnjArc>>::iterator it=arcList.begin();
    
    ICSAttribute attr;
    GetICSAttribute(attr);
    
    for ( ;it!= arcList.end(); it++ ) {
        ol.push_back(std::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(**it)));//,attr)));
    }
    return error;
}
/////////////////////////////////////////////////////////
std::shared_ptr<Segment> MnjSmoothableArc::GetSegment(void){
    return GetArc(0);
}