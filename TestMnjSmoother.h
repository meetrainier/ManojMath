#pragma once
//Manoj : 21May 2016: Replaced typedesf by using 
//#include "MnjSmoothableSegment.h"
#include <memory> 
#include "MnjArc.h"
#include "MnjLine.h"
//#include "MnjSmoothableArc.h"
//#include "MnjSmoothableLine.h"
#include "MnjPoint.h" 
#include "GeomUtils.h"
#include "MnjSmoother.h"
#include "MnjSmoothableSegment.h"
#include "MnjSmoothableLine.h"
#include "MnjSmootherUtils.h"

#define MAX_STR_SIZE 10000


class TestMnjSmoother {

public:
 using shared_ptr_seg     = std::shared_ptr<MnjSmoothableSegment> shared_ptr_seg;
 using vec_shared_ptr_seg = vector<std::shared_ptr<MnjSmoothableSegment>> vec_shared_ptr_seg;

 using  shared_ptr_arc = std::shared_ptr<MnjSmoothableArc> ;
 using  shared_ptr_line = std::shared_ptr<MnjSmoothableLine> ;
 
 /*
 typedef  std::shared_ptr<MnjSmoothableSegment> shared_ptr_seg;
 typedef vector<std::shared_ptr<MnjSmoothableSegment>> vec_shared_ptr_seg;

 typedef  std::shared_ptr<MnjSmoothableArc> shared_ptr_arc;
 typedef  std::shared_ptr<MnjSmoothableLine> shared_ptr_line;
 */
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
static	void TestArcLineClosedSmallSegmentsInputs(vec_shared_ptr_seg &osegVec);
  static void TestArcLineClosedSmallSegments(void);
	
  static void TestArcArcOpen(void);
  static void TestArcArcClosed(void);
  static void TestArcArcOpenSmallSegments(void);
  static void TestArcArcClosedSmallSegments(void);
  
  //Utils

    static void CheckResults(shared_ptr_arc icsarc1, shared_ptr_arc icsarc2);
	   
    //template <typename MnjSmoothableSegment, typename MnjSmoothableArc, typename MnjSmoothableLine>
    static void Print(MnjPoint<double>&c,char str[]);
    
    //template <class  MnjSmoothableArc>
    //void Print(boost::shared_ptr<MnjSmoothableArc> &icsarc,char str[] );
//    typedef typename boost::shared_ptr<MnjSmoothableArc> shared_ptr_arc;
    static void Print(const shared_ptr_line&icsline,char str[] );

    static void Print( shared_ptr_arc  &icsarc,char str[] ){
      
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

#if _DEBUG
    void Print(const MnjLine::shared_ptr&icsline,char str[] ) ;
    //void Print(ICSAttribute &a,char str[]);

    static void Print(shared_ptr_seg &icsSeg,char str[]);
	 //GetString is print method really today 
    static void GetString(vec_shared_ptr_seg icssegVec,char tmp[] );
#endif
	void IsNew(shared_ptr_seg seg);
    void TestIsConnected(void);

};
