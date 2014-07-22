//
//#include <iostream>
#include <functional>
//#include <type_transform> //not in VS 10
#include "TestMnjSmoother.h"
#include "MnjSmoothableSegment.h"
#include "MnjSmoothableLine.h"
#include "MnjSmoothableArc.h"
#include "TestMnjSmoother.h"

#include "MnjLine.h"
//class MnjSmoothableLine;

 //////////////////////////////////////////////////////////////////////////////////
  // This function will obtain a reference to the parameter 'r' and increment it.
void f (int &r) { r++; }
// Template function.
template<class F, class P> void g (F f, P t) { f(t); }
int WrapperReference()
{
int i = 0 ;
g (f, i) ; // 'g<void (int &r), int>' is instantiated
// then 'i' will not be modified.
std::cout << i << std::endl; // Output -> 0
g (f, std::ref(i)); // 'g<void(int &r),reference_wrapper<int>>' is instantiated
// then 'i' will be modified.
std::cout << i << std::endl; // Output -> 1
return 0;
}
///////////////////////////////////////////////////////////////////////
class TestMnjLine {

public:
 void TestDeafultConstructor(){

  MnjLine l;
 }
 /*
 	MnjLine(){ }
  MnjLine(const MnjLine &l){ 
         startPoint = l.startPoint;
         endPoint = l.endPoint;
  }

  MnjLine(Segment &iSeg1, Segment &iSeg2);
	MnjLine(MnjPoint<double> &s,MnjPoint<double> &e);
//	SegmentType GetType(){ return SegmentType::LINE;}

	void Set(MnjPoint<double> &s,MnjPoint<double> &e);
	void GetStartPoint(MnjPoint<double> &p)const;
  */

};
///////////////////////////////////////////////////////
int main(int argc, char *argv[]){
   //TestMnjLine testLine;

  //TestMnjSmoother<MnjSmoothableSegment,MnjSmoothableLine,MnjSmoothableArc> test;
  TestMnjSmoother test;
  test.Test();


  WrapperReference();
}
