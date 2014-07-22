#pragma once
//#include "MnjSmoothableSegment.h"
#include "MnjArc.h"
#include "MnjLine.h"
//#include "MnjSmoothableArc.h"
//#include "MnjSmoothableLine.h"
#include "MnjPoint.h" 
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "GeomUtils.h"
#include "MnjSmoother.h"
#include "MnjSmoothableSegment.h"
#include "MnjSmoothableLine.h"
#include "MnjSmootherUtils.h"

#define MAX_STR_SIZE 10000

//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
//template <class MnjSmoothableSegment, class MnjSmoothableLine, class MnjSmoothableArc>
class TestMnjSmoother {

public:
 
 typedef  boost::shared_ptr<MnjSmoothableSegment> shared_ptr_seg;
 //typedef typename vector<boost::shared_ptr<MnjSmoothableSegment>> vec_shared_ptr_seg;
 //typedef typename vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator vec_shared_ptr_seg_it;

 typedef  boost::shared_ptr<MnjSmoothableArc> shared_ptr_arc;
 typedef  boost::shared_ptr<MnjSmoothableLine> shared_ptr_line;
 
 //Call all other tests
  static int Test(void);
 //template <class MnjSmoothableSegment, class MnjSmoothableLine, class MnjSmoothableArc>


	static void TestLineLineOpen(void);
	static void TestLineLineClosed(void);
	static void TestLineLineOpenSmallSegments(void);
	static void TestLineLineClosedSmallSegments();
  
	static void TestLineArcOpen(void);
	static void TestLineArcClosedRedundant(void);
	static void TestLineArcClosed(void);
	static void TestLineArcOpenSmallSegments(void);
    static void TestLineArcClosedSmallSegmentsInputs(vector<shared_ptr_seg> &osegVec);
	static void TestLineArcClosedSmallSegments(void);

  static void TestArcLineOpen(void);
	//void TestArcLineClosed(void);//not needed
static 	void TestArcLineOpenSmallSegments(void);
static	void TestArcLineClosedSmallSegmentsInputs(vector<boost::shared_ptr<MnjSmoothableSegment>> &osegVec);
  static void TestArcLineClosedSmallSegments(void);
	
  static void TestArcArcOpen(void);
  static void TestArcArcClosed(void);
  static void TestArcArcOpenSmallSegments(void);
  static void TestArcArcClosedSmallSegments(void);
  
  //Utils

    static void CheckResults(boost::shared_ptr<MnjSmoothableArc> icsarc1, boost::shared_ptr<MnjSmoothableArc> icsarc2);
	   
    //template <typename MnjSmoothableSegment, typename MnjSmoothableArc, typename MnjSmoothableLine>
    static void Print(MnjPoint<double>&c,char str[]);
    
    //template <class  MnjSmoothableArc>
    //void Print(boost::shared_ptr<MnjSmoothableArc> &icsarc,char str[] );
//    typedef typename boost::shared_ptr<MnjSmoothableArc> shared_ptr_arc;
    static void Print(const boost::shared_ptr<MnjSmoothableLine>&icsline,char str[] );

    static void Print( boost::shared_ptr<MnjSmoothableArc>  &icsarc,char str[] ){
      
     MnjArc arc;
      if(icsarc){
        icsarc->GetArc(arc);
      }

      MnjPoint<double>s; 	
      MnjPoint<double>e; 
      
      arc.GetEnds(s,e);
      
      strncat_s(str,MAX_STR_SIZE,"Arc:\n",strlen("Arc:\n")+1);

      Print(s,str);
      MnjPoint<double>c; 
      arc.GetCenter(c);
      Print(c,str);
      Print(e,str);

    }

    void Print(const MnjLine::shared_ptr&icsline,char str[] ) ;
    //void Print(ICSAttribute &a,char str[]);

    static void Print(shared_ptr_seg &icsSeg,char str[]);

    static void GetString(vector<boost::shared_ptr<MnjSmoothableSegment>> icssegVec,char tmp[] );
    void IsNew(boost::shared_ptr<MnjSmoothableSegment> seg) ;
    void TestIsConnected(void);

};