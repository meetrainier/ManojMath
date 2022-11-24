//
//copyright(c) 2009- 2016 Manoj Lnu 
//#include <iostream>
#include <functional>
//#include <bits/stdc++.h>
#include <queue>
#include "TestGeomUtils.h"
//#include "GeomUtils.h"
#include "TestMnjSmoother.h"
#include "MnjSmoothableSegment.h"
#include "MnjSmoothableLine.h"
#include "MnjSmoothableArc.h"
#include "TestMnjSmoother.h"
#include "MnjSudoku.h"
#include "MnjLine.h"
#include "boostGeometryExample.h"

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
using vecI = std::vector<int>;
void print(vecI vec)
{
  for (auto& x : vec)
    cout << x << " ";
  cout << std::endl;
}

void ShowPriorityQueueWorksOnVectorOfInts()
{
  vecI a{ 0, 1, 2};
  vecI b{ -1, 1, 2 };
  vecI c{ 1, 1, 2 };

  std::priority_queue < vecI, std::vector<vecI>,  std::greater<vecI >> pq;
  pq.push(a);
  pq.push(b);
  pq.push(c);

  auto a1 = pq.top();
  print(a1);
  pq.pop();

  auto b1 = pq.top();
  print(b1);
  pq.pop();

  auto c1 = pq.top();
  print(c1);
}

///////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  ShowPriorityQueueWorksOnVectorOfInts();
  using iPair = std::pair<int, int>;
  std::vector<std::pair<int, iPair >> v;
  v.push_back({ 1,{1,1} });
  v.push_back({ 0, { 1,1 } });
  std::sort(begin(v),end(v));
  for (auto& x : v)
    cout << x.first << " " << std::endl;
   //PointsInPolygon();
  //TestMnjLine testLine;

  //TestMnjSmoother<MnjSmoothableSegment,MnjSmoothableLine,MnjSmoothableArc> test;
  //sudoku_test1();
  
  //TestMnjSmoother test;
  //test.Test();
  
  //WrapperReference();
  
   //GeomUtils::TestGeomUtils::TestLineLineIntersect();  
   //TestGeomUtils test;
   //test.Test();
  return 0;
}
