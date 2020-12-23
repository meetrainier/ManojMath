////////////////////////////////////////////////////////////
///
//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
///     Project : Insert arc among a sequence of segments(lines/arcs).
///     Subsystem : None
///     Author : Manoj Lnu
///     Date : 4/23/2012
///
///		All rights reserved.
///
////////////////////////////////////////////////////////////
#include "MnjSmoothableSegment.h"
#include "MnjSmootherUtils.h"

bool MnjSmoothableSegment::IsTangent(const shared_ptr iSeg){
        int error = 0;
        bool flag = false;
        MnjPoint<double> p = GetCommonPoint(iSeg,error);
        if(error>=0){
            MnjDirection thisTangent = TangentAtEnd(p);
            MnjDirection thatTangent = iSeg->TangentAtEnd(p);
            double dotP = GeomUtils::DotProduct(thisTangent,thatTangent);
            if(fabs(dotP+1.00)<.0001) 
                flag = true;
        }
        return flag;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////
MnjPoint<double> MnjSmoothableSegment::GetCommonPoint(shared_ptr seg2,int &oerror)
 { //tbd : just call MnjSegment verson of it
      MnjPoint<double> s1,e1,s2,e2;
      GetEnds(s1,e1);
      seg2->GetEnds(s2,e2);
      if(   GeomUtils::IsSame(s1,s2) || GeomUtils::IsSame(s1,e2) ) {
        return MnjPoint<double>(s1); 
      }
      else if ( GeomUtils::IsSame(e1,s2) || GeomUtils::IsSame(e1,e2) ) {
        return MnjPoint<double>(e1); 
      }else {
        oerror = -1;
     }
     return MnjPoint<double>();
  }
 /////////////////////////////////////////////////////////////////////////////////////////
/*
int MnjSmoothableSegment::SetSmoothableAttribute(shared_ptr iSeg1,shared_ptr iSeg2){
         int error = 0;
        //SmoothableAttribute attr;
        vector< shared_ptr > icsSegVec;
	    icsSegVec.push_back(iSeg1);
	    icsSegVec.push_back(iSeg2);
	   
        MnjSmootherUtils::GetAttributeWithLowestValues(icsSegVec,mattr);
        SmoothableAttribute::SmoothableSegProperty prop = SmoothableAttribute::SEG_UNKNOWN;
        if(IsScribe() && iSeg2->IsScribe()){
            prop = SmoothableAttribute::SEG_SCRIBE;
        }
        mattr.SetSegProp(prop);
        return error;
}
*/
//////////////////////////////////////////////////////////////////////////////////////////
bool MnjSmoothableSegment::IsScribe(void){
    return mattr.IsScribe();
}

int MnjSmoothableSegment::MergeAndSetAttributes(shared_ptr iSeg1,shared_ptr iSeg2,
                                         MnjSmoothableSegment::SegmentChange iStatus){
    int error =0;
    //mnj SetSmoothableAttribute(iSeg1,iSeg2);

    //SetCorner(iSeg1->IsCorner());
    SetCornerRadius (iSeg1->GetCornerRadius());
    SetStatus(iStatus);
    return error;
}