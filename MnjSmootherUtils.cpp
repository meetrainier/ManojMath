#include "MnjSmootherUtils.h"
#include "MnjArc.h"
#include "MnjLine.h"
#include <memory>
bool MnjSmootherUtils::IsConnected(vector<boost::shared_ptr<MnjSmoothableSegment>> &vec, 
                                  vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator &oit,
                               double &od//tbd
                               ) {
  int error = 0;
  bool flag = true;
  unsigned int i = 0;
  for(vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator it=vec.begin(); i < vec.size() -1 ; i++,it++) {
      vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator ittmp=it;
      ittmp++;
      (*it)->GetCommonPoint(*(ittmp),error);
      if(error<0 ){ 
          oit = it;
          flag = false;
          break;
      }
  }
  return flag;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
bool MnjSmootherUtils::IsConnected(vector<boost::shared_ptr<MnjSmoothableSegment>> &vec
                               ) {
  int error = 0;
  bool flag = true;
  unsigned int i = 0;
  for(vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator it=vec.begin(); i < vec.size() -1 ; i++,it++) {
      vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator ittmp=it;
      ittmp++;
      (*it)->GetCommonPoint(*(ittmp),error);
      if(error<0 ){ 
          flag = false;
          break;
      }
  }
  return flag;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
template <typename MnjSmoothableSegment, typename MnjSmoothableArc, typename MnjSmoothableLine>
bool MnjSmootherUtils<MnjSmoothableSegment, MnjSmoothableArc, MnjSmoothableLine>::IsConnected(vector<boost::shared_ptr<MnjSmoothableSegment>> &vec, 
                                 typename vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator &oit,
                               double &od//tbd
                               ) {
  int error = 0;
  bool flag = true;
  unsigned int i = 0;
  for(vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator it=vec.begin(); i < vec.size() -1 ; i++,it++) {
      vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator ittmp=it;
      ittmp++;
      (*it)->GetCommonPoint(*(ittmp),error);
      if(error<0 ){ 
          oit = it;
          flag = false;
          break;
      }
  }
  return flag;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
bool MnjSmootherUtils<MnjSmoothableSegment,MnjSmoothableLine,MnjSmoothableArc>::IsConnected(vec_shared_ptr_seg &vec
                               ) {
  int error = 0;
  bool flag = true;
  unsigned int i = 0;
  for(vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator it=vec.begin(); i < vec.size() -1 ; i++,it++) {
      vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator ittmp=it;
      ittmp++;
      (*it)->GetCommonPoint(*(ittmp),error);
      if(error<0 ){ 
          flag = false;
          break;
      }
  }
  return flag;
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

//template <typename MnjSmoothableSegment, typename MnjSmoothableArc, typename MnjSmoothableLine>
//MnjSmootherUtils<MnjSmoothableSegment, MnjSmoothableArc, MnjSmoothableLine>::ICSSegmentType 

 MnjSmootherUtils::SegmentType MnjSmootherUtils::GetType(const boost::shared_ptr<MnjSmoothableSegment>  icsSeg
                               ) {

  boost::shared_ptr<MnjSmoothableArc> icsarc = boost::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (icsSeg);
  boost::shared_ptr<MnjSmoothableLine> icsline = boost::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (icsSeg);
  
  if(icsarc){
         return SMOOTHABLE_SEG_ARC;
  }else if(icsline ){
         return SMOOTHABLE_SEG_LINE;
  }else {
        return SMOOTHABLE_SEG_UNKOWN;
  }
  ///////////////////////////////////////////////////////////////////////////

}
