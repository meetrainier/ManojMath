//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
#pragma once
//List
#include <memory>
#include <vector>
#include <map>
#include <list>
//boost

//Local 
//#include "Segment.h"
#include "MnjSmoothableSegment.h"
#include "MnjSmoothableArc.h"
#include "MnjSmoothableLine.h"

/*#define boost::shared_ptr<MnjSmoothableSegment> shared_ptr_seg;
#define vector<boost::shared_ptr<MnjSmoothableSegment>> vec_shared_ptr_seg;
#define vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator vec_shared_ptr_seg_it;

#define boost::shared_ptr<MnjSmoothableArc> shared_ptr_arc;
#define boost::shared_ptr<MnjSmoothableLine> shared_ptr_line;
*/
//template 
//<typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc >
class MnjSmootherUtils {


public:

  enum SegmentType{//returns which type of segment is stored
        SMOOTHABLE_SEG_LINE,//this segment is of type MnjSmoothableLine
        SMOOTHABLE_SEG_ARC,//this segment is of type MnjSmoothableArc
        SMOOTHABLE_SEG_UNKOWN
    };
  /*

 */

//static void GetAttributeWithLowestValues(vector<boost::shared_ptr<MnjSmoothableSegment>> &icsSegVec, ICSAttribute &oa);
static bool IsConnected(vector<std::shared_ptr<MnjSmoothableSegment>>   &vec, 
                        vector<std::shared_ptr<MnjSmoothableSegment>>::iterator &oit,
                               double &od);//od tbd

static  bool IsConnected(vector<std::shared_ptr<MnjSmoothableSegment>>  &vec) ;
static SegmentType GetType(const std::shared_ptr<MnjSmoothableSegment> icsSeg) ;

};
