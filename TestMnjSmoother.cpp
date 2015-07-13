#include "TestMnjSmoother.h"
#include "MnjSmootherUtils.h"
#include "MnjSmoothableSegment.h"
#include <memory> 
#include <assert.h> 
//#include <boost/weak_ptr.hpp>

//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
/*template <class MnjSmoothableSegment, class MnjSmoothableLine, class MnjSmoothableArc>
*/
int TestMnjSmoother::Test(void){
   	
    //////////////////Line Line case///////
 try{
  TestLineLineOpen();               //working 
  
   TestLineLineClosed();             //working
    TestLineLineOpenSmallSegments();  //working
	TestLineLineClosedSmallSegments();//working
 
    //////////////////Line-Arc case////////////////////////
	TestLineArcOpen();               //working
  TestLineArcClosed();             //working
  TestLineArcClosedRedundant();    //working
    
  TestLineArcOpenSmallSegments();  //working
	
  TestLineArcClosedSmallSegments();//working
    
	//////////////////Arc-Line case/////////////////////////
  TestArcLineOpen();             //working
	//TestArcLineClosed(); //not needed TestLineArcClosed() fulfills it. 
                                //but can test by passing input of TestLineArcClosed() in reverse order 
	TestArcLineOpenSmallSegments();  //working
	TestArcLineClosedSmallSegments();//working
	
    ///// Arc - Arc case/////////////////////// 
  TestArcArcOpen();               //working
  TestArcArcClosed();             //working
  
  TestArcArcOpenSmallSegments();// working 
  TestArcArcClosedSmallSegments();//working 
 }catch(std::exception e) {
   cout << e.what() << std::endl;
 }
  return 0;    
}
//----------------------------------------------------------------------
void TestMnjSmoother::TestLineLineOpen(){
	
  MnjPoint<double> x1(10,0,0);
	MnjPoint<double> y1(0,10,0);
  ICSAttribute attr1;
	attr1.color = 80;
	MnjPoint<double> o(0,0,0);
	std::shared_ptr<MnjSmoothableLine> l1(new MnjSmoothableLine(x1,o));//,attr1));
	ICSAttribute attr2;
	attr2.color = 60;
	std::shared_ptr<MnjSmoothableLine>  l2(new MnjSmoothableLine(o,y1));//,attr2));

	vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	if(l1){
	  segVec.push_back(l1);
	  //l1->SetCorner(true);
	  double r=5;
	  l1->SetCornerRadius(r);
    l1->SetSegProp(ICSAttribute::SEG_SCRIBE);
	}

	if(l2){
    l2->SetSegProp(ICSAttribute::SEG_SCRIBE);
	  segVec.push_back(l2);
	}

    //execute
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	//MnjSmoother<Segment,MnjLine,MnjArc> s;
	MnjSmoother s;
  map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec,changes );
	
    //verify the result 
	bool connected = MnjSmootherUtils::IsConnected(osegVec);
  assert(true==connected);
  assert(3==osegVec.size());
	//ICSAttribute icsAttr;
	assert(osegVec[1]);
	
  //osegVec[1]->GetICSAttribute(icsAttr);
	std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[1]);
	assert(resultArc);
  assert(5 == resultArc->GetRadius());
   //assert(60==icsAttr.color);
    
   //test: scribe status of the new arc
  bool scribe = resultArc->IsScribe();
  assert(true==scribe);
  double angle = resultArc->GetAngle();

  MnjSmootherUtils::SegmentType seg_type = MnjSmootherUtils::GetType(osegVec[1]);
    assert(MnjSmootherUtils::SMOOTHABLE_SEG_ARC==seg_type) ;
    assert(MnjSmoothableSegment::MODIFIED == osegVec[0]->Status());
    assert(MnjSmoothableSegment::NEW == resultArc->Status());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[2]->Status());
	double result_r = resultArc->GetRadius();
	
	//print the result
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
#ifdef _DEBUG 
	GetString(osegVec,tmp);
#endif

	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}

//////////////////////////////////////////////////////////////
 //
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::Print(MnjPoint<double>&c,char str[]){
    char msgline[100];
	sprintf_s(msgline,100,"x=%f y=%f z=%f \n",c.x,c.y,c.z);
	strncat_s(str,MAX_STR_SIZE,msgline,1+strlen(msgline));
}
//////////////////////////////////////////////////////////////
/*void TestMnjSmoother::Print(shared_ptr_arc &icsarc,char str[] ) {
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
*/
//////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
#if _DEBUG
void TestMnjSmoother::Print(const std::shared_ptr<MnjSmoothableLine>&icsline,char str[] ) {

 std::shared_ptr<MnjLine> line;
 if(icsline)
	line = icsline->GetLine();
 
 MnjPoint<double>s;
 MnjPoint<double>e; 
 line->GetEnds(s,e);
 strncat_s(str,MAX_STR_SIZE,"Line:\n",strlen("Line:\n")+1);
 Print(s,str);
 Print(e,str);

}
#endif 
////////////////////////////////////////////////////////////////
//
//void TestMnjSmoother<Segment,MnjArc,MnjLine>::Print(ICSAttribute &a,char str[]){
 //char msgline[100];
 //sprintf_s(msgline,100,"color=%d \n",a.color);
 //strncat_s(str,MAX_STR_SIZE,msgline,1+strlen(msgline));
//}
////////////////////////////////////////////////////////////////
/*
template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
*/
#ifdef _DEBUG
void TestMnjSmoother::Print(shared_ptr_seg &icsSeg,char str[]){
	//if(icsSeg) icsSeg->Print();
	if(!icsSeg) 
		return;
	shared_ptr_arc icsarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (icsSeg);
  shared_ptr_line icsline = std::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (icsSeg);
	if(icsarc){
		Print(icsarc,str);
	}else if(icsline ){
		Print(icsline,str);
	}
  
	//ICSAttribute a;
	//icsSeg->GetICSAttribute(a);
	//Print(a,str);
  
}
#endif
////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>

#ifdef _DEBUG 
void TestMnjSmoother::GetString(vector<std::shared_ptr<MnjSmoothableSegment>> icssegVec,char tmp[] ){
	//vector<boost::shared_ptr<MnjSmoothableSegment>> it;
	for (unsigned int i = 0 ; i < icssegVec.size() ;i++) {
		Print(icssegVec[i],tmp);
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////
/*template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineLineOpen(){
	
 MnjPoint<double> x1(10,0,0);
	MnjPoint<double> y1(0,10,0);
  ICSAttribute attr1;
	attr1.color = 80;
	MnjPoint<double> o(0,0,0);
	MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(x1,o,attr1));
	ICSAttribute attr2;
	attr2.color = 60;
	MnjSmoothableLine::shared_ptr l2(new MnjSmoothableLine(o,y1,attr2));

	vector<boost::shared_ptr<MnjSmoothableSegment>> segVec;
	if(l1){
	  segVec.push_back(l1);
	  //l1->SetCorner(true);
	  double r=5;
	  l1->SetCornerRadius(r);
      l1->SetSegProp(ICSAttribute::SEG_SCRIBE);
	}

	if(l2){
      l2->SetSegProp(ICSAttribute::SEG_SCRIBE);
	  segVec.push_back(l2);
	}

    //execute
	vector<boost::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
    map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec,changes );
	
    //verify the result 
	bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(3==osegVec.size());
	ICSAttribute icsAttr;
	assert(osegVec[1]);
	osegVec[1]->GetICSAttribute(icsAttr);
	boost::shared_ptr<MnjSmoothableArc> resultArc = boost::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[1]);
	assert(resultArc);
  MnjSmootherUtils::ICSSegmentType seg_type = MnjSmootherUtils::GetType(osegVec[1]);
    assert(MnjSmootherUtils::SMOOTHABLE_SEG_ARC==seg_type) ;
    assert(MnjSmoothableSegment::MODIFIED == osegVec[0]->Status());
    assert(MnjSmoothableSegment::NEW == resultArc->Status());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[2]->Status());
	double result_r = resultArc->GetRadius();
	assert(5 == resultArc->GetRadius());
	//assert(60==icsAttr.color);
    
    //test: scribe status of the new arc
    bool scribe = resultArc->IsScribe();
    assert(true==scribe);
	//print the result
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
	GetString(osegVec,tmp);
	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}
*/
 
//////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineLineClosed(){
	MnjPoint<double> x1(10,0,0);
	MnjPoint<double> y1(0,10,0);
//	ICSAttribute attr1,attr2;
//	attr1.color = 80;
//	attr2.color = 60;
	MnjPoint<double> o(0,0,0);
  
	MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(x1,o));//,attr1));
	MnjSmoothableLine::shared_ptr l2(new MnjSmoothableLine(o,y1));//,attr2));
	MnjSmoothableLine::shared_ptr l3(new MnjSmoothableLine(y1,x1));//,attr2));
  /*
  MnjLine::shared_ptr l1(new MnjLine(x1,o));
	MnjLine::shared_ptr l2(new MnjLine(o,y1));
	MnjLine::shared_ptr l3(new MnjLine(y1,x1));
  */
	vector<TestMnjSmoother::shared_ptr_seg> segVec;
	if(l1){
		segVec.push_back(l1);
		//l1->SetCorner(true);
		double r=5;
		l1->SetCornerRadius(r);
	}
	if(l2){
    	segVec.push_back(l2);
		//l2->SetCorner(true);
		double r=1;
		l2->SetCornerRadius(r);
	}
	if(l3){
    	segVec.push_back(l3);
		l3->SetCorner(true);
		double r=1;
		l3->SetCornerRadius(r);
	}
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
    map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec,changes );
	//verify the result 
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
	assert(6==osegVec.size());
	assert(MnjSmoothableSegment::MODIFIED == osegVec[0]->Status());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[2]->Status());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[4]->Status());
    
    //first corner
	ICSAttribute icsAttr;
	assert(osegVec[1]);
	osegVec[1]->GetICSAttribute(icsAttr);
	std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[1]);
	assert(resultArc);
	double result_r = resultArc->GetRadius();
	assert(5 == result_r );
	////assert(60==icsAttr.color);
    assert(MnjSmoothableSegment::NEW == osegVec[1]->Status());
	
    //2nd corner
	assert(osegVec[3]);
	ICSAttribute icsAttr1;
	osegVec[3]->GetICSAttribute(icsAttr1);
	std::shared_ptr<MnjSmoothableArc> resultArc1 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[3]);
	assert(resultArc1);
	double result_r1 = resultArc1->GetRadius();
	assert(1 == result_r1 );
	//assert(60==icsAttr.color);
    assert(MnjSmoothableSegment::NEW == osegVec[3]->Status());

	//3rd corner
	assert(osegVec[5]);
	ICSAttribute icsAttr2;
	osegVec[5]->GetICSAttribute(icsAttr2);
	std::shared_ptr<MnjSmoothableArc> resultArc2 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[5]);
	assert(resultArc2);
	double result_r2 = resultArc2->GetRadius();
	assert( fabs(result_r2 -1) < .00000001 );
	//assert(60==icsAttr.color);
   assert(MnjSmoothableSegment::NEW == osegVec[5]->Status());
  
	//print 
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");

#ifdef _DEBUG 
	GetString(osegVec,tmp);
#endif

	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}//TestLineLineClosed

//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>

void TestMnjSmoother::TestLineLineOpenSmallSegments(){
	
	vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	for ( int i = 0 ; i < 10 ; i++){
	     MnjPoint<double> x2(10-i,0,0);
	     MnjPoint<double> x1(9-i,0,0);
	     ICSAttribute attr1;
	     attr1.color = 80;
	     MnjSmoothableLine::shared_ptr l(new MnjSmoothableLine(x2,x1));//,attr1));
		 if(9==i){
			 //l->SetCorner(true);
			 l->SetCornerRadius(5);
		 }
		 segVec.push_back(l);
	}
	for ( int i = 0 ; i < 10 ; i++){
	     MnjPoint<double> y2(0,i+1,0);
	     MnjPoint<double> y1(0,i,0);
	     ICSAttribute attr1;
	     attr1.color = 60;
	     MnjSmoothableLine::shared_ptr l(new MnjSmoothableLine(y1,y2));//,attr1));
		 segVec.push_back(l);
	}
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
    map<unsigned int, int> changes;
	s.CreateArcs(segVec,  osegVec, changes );
    //test S
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    int size1 = osegVec.size();
    assert(13 == osegVec.size());
    std::shared_ptr<MnjSmoothableArc> oarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[6]);
    assert(oarc);
    double out_r = oarc->GetRadius();
    assert(fabs(out_r - 5 ) < .001) ; 
	//Print
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
	//GetString(osegVec,tmp);
	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineLineClosedSmallSegments(){
	
	vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	for ( int i = 0 ; i < 10 ; i++){
	     MnjPoint<double> x2(10-i,0,0);
	     MnjPoint<double> x1(9-i,0,0);
	     ICSAttribute attr1;
	     attr1.color = 80;
	     MnjSmoothableLine::shared_ptr l(new MnjSmoothableLine(x2,x1));//,attr1));
		 if(9==i){
			 //l->SetCorner(true);
			 l->SetCornerRadius(4);
		 }
		 segVec.push_back(l);
	}
    //y -axis segments
	for ( int i = 0 ; i < 10 ; i++){
	     MnjPoint<double> y2(0,i+1,0);
	     MnjPoint<double> y1(0,i,0);
	     ICSAttribute attr1;
	     attr1.color = 60;
	     MnjSmoothableLine::shared_ptr l(new MnjSmoothableLine(y1,y2));//,attr1));
         if(9==i){
			 //l->SetCorner(true);
			 l->SetCornerRadius(1.5);
		 }
		 segVec.push_back(l);
	}

    //join the lines to close
     //y -axis segments
  MnjPoint<double> p1(0,10,0);
	MnjPoint<double> p2(10,0,0);

	for ( int i = 0 ; i < 10 ; i++){
	     MnjPoint<double> p11 = p1 + (p2-p1)*(i/10.0);
	     MnjPoint<double> p12 = p1 + (p2-p1)*((i+1.0)/10.0);

	     ICSAttribute attr1;
	     attr1.color = 60;
	     MnjSmoothableLine::shared_ptr l(new MnjSmoothableLine(p11,p12));//,attr1));
         if(9==i){
			 //l->SetCorner(true);
			 l->SetCornerRadius(1.5);
		 }
		 segVec.push_back(l);
	}
    

	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
  map<unsigned int, int> changes;
	
  s.CreateArcs(segVec,  osegVec, changes );
    //test 
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(16 == osegVec.size());
    std::shared_ptr<MnjSmoothableArc> oarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[4]);
    assert(oarc);
    double out_r0 = oarc->GetRadius();
    assert(fabs(out_r0 - 4 ) < .001) ; 
	
    //test 2nd arc 
    oarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[9]);
    assert(oarc);
    double out_r1 = oarc->GetRadius();
    assert(fabs(out_r1 - 1.5 ) < .001) ; 

    //test 3rd arc 
    oarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[15]);
    assert(oarc);
    double out_r2 = oarc->GetRadius();
    assert(fabs(out_r2 - 1.5 ) < .001) ; 


    //Print
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
	//GetString(osegVec,tmp);
	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////

//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineArcOpen(){
	
    //Create line
    MnjPoint<double> P2(20,0,0);
	MnjPoint<double> P1(10,0,0);
	ICSAttribute attr1;
	attr1.color = 80;
	MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(P2,P1));//,attr1));
	
    //Create Arc
    ICSAttribute attr2;
	attr2.color = 60;
	MnjPoint<double> o(0,0,0);
	MnjPoint<double> P0(0,10,0);
	std::shared_ptr<MnjSmoothableArc>  l2(new MnjSmoothableArc(P1,o,P0));//,attr2));
   
	vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	if(l1){
	  segVec.push_back(l1);
	  //l1->SetCorner(true);
	  double r=1;
	  l1->SetCornerRadius(r);
	}

	if(l2){
	  segVec.push_back(l2);
	}
    
    //insert arcs
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
  map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec, changes );
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
	
    //verify the result 
	assert(3==osegVec.size());
  assert(MnjSmoothableSegment::MODIFIED == osegVec[0]->Status());
  assert(MnjSmoothableSegment::NEW == osegVec[1]->Status());
  assert(MnjSmoothableSegment::MODIFIED == osegVec[2]->Status());

	ICSAttribute icsAttr;
	assert(osegVec[1]);
	osegVec[1]->GetICSAttribute(icsAttr);
	std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[1]);
	assert(resultArc);
	double result_r = resultArc->GetRadius();
  double rad_diff = 1 -resultArc->GetRadius();
	assert(fabs(rad_diff) < .001);
	//assert(60==icsAttr.color);
	MnjPoint<double> s1,e1;
	resultArc->GetEnds(s1,e1);
	assert(fabs(s1.x - 9.95832) < .001);//by hand 9.958932064677038 //prog s1.x = 9.9585919546387061
  assert(fabs(s1.y - 0.9053018181818182) < .01);// by hand 0.9053574604251853 //prog s1.y = y = 0.90909090909834389
	//print the result
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
	//GetString(osegVec,tmp);
	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineArcClosed(){

    MnjPoint<double> p1(10,6,0);
    MnjPoint<double> p2(6,10,0);
    MnjPoint<double> p3(-6,10,0);
    MnjPoint<double> p4(-10,6,0);
    MnjPoint<double> p5(-10,-6,0);
    MnjPoint<double> p6(-6,-10,0);
    MnjPoint<double> p7(6,-10,0);
    MnjPoint<double> p8(10,-6,0);
    
    ICSAttribute attr;
    attr.color = 60;
  MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(p8,p1));//,attr));
	MnjSmoothableLine::shared_ptr l2(new MnjSmoothableLine(p2,p3));//,attr));
	MnjSmoothableLine::shared_ptr l3(new MnjSmoothableLine(p4,p5));//,attr));
	MnjSmoothableLine::shared_ptr l4(new MnjSmoothableLine(p6,p7));//,attr));

    MnjPoint<double> c1(5,5,0);
    MnjPoint<double> c2(-5,5,0);
    MnjPoint<double> c3(-5,-5,0);
    MnjPoint<double> c4(5,-5,0);

    std::shared_ptr<MnjSmoothableArc>  a1(new MnjSmoothableArc(p1,c1,p2));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a2(new MnjSmoothableArc(p3,c2,p4));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a3(new MnjSmoothableArc(p5,c3,p6));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a4(new MnjSmoothableArc(p7,c4,p8));//,attr));

    vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
    
	segVec.push_back(l1);segVec.push_back(a1);
  segVec.push_back(l2);segVec.push_back(a2);
  segVec.push_back(l3);segVec.push_back(a3);
  segVec.push_back(l4);segVec.push_back(a4);


    //Input Preparation: step3: specify corners
    for ( unsigned int i = 0 ; i < segVec.size() ;i++ ) {
        //segVec[i]->SetCorner(true);
        segVec[i]->SetCornerRadius(.5);
    }
    
    //Execution::insert arcs
    vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
    map<unsigned int, int> changes;
    MnjSmoother s;
	s.CreateArcs(segVec, osegVec, changes );
    
    //Testing
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    int size1 = osegVec.size();
    assert(16==osegVec.size());
    //is each segment at odd idex an arc?
    //is radius correct?
    for ( unsigned int i = 0 ; i < osegVec.size() ;i++ ) {
       	std::shared_ptr<MnjSmoothableArc> icsarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[i]);
        if(1==i%2){
            assert(icsarc);
            double result_r = icsarc->GetRadius();
            assert(fabs(result_r -0.5) < .001);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineArcClosedSmallSegmentsInputs(vector<shared_ptr_seg> &segVec){

    MnjPoint<double> p1(10,6,0);
    MnjPoint<double> p2(6,10,0);
    MnjPoint<double> p3(-6,10,0);
    MnjPoint<double> p4(-10,6,0);
    MnjPoint<double> p5(-10,-6,0);
    MnjPoint<double> p6(-6,-10,0);
    MnjPoint<double> p7(6,-10,0);
    MnjPoint<double> p8(10,-6,0);
    
    ICSAttribute attr;
    attr.color = 60;
    MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(p8,p1));//,attr));
	MnjSmoothableLine::shared_ptr l2(new MnjSmoothableLine(p2,p3));//,attr));
	MnjSmoothableLine::shared_ptr l3(new MnjSmoothableLine(p4,p5));//,attr));
	MnjSmoothableLine::shared_ptr l4(new MnjSmoothableLine(p6,p7));//,attr));

    MnjPoint<double> c1(5,5,0);
    MnjPoint<double> c2(-5,5,0);
    MnjPoint<double> c3(-5,-5,0);
    MnjPoint<double> c4(5,-5,0);

  std::shared_ptr<MnjSmoothableArc>  a1(new MnjSmoothableArc(p1,c1,p2));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a2(new MnjSmoothableArc(p3,c2,p4));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a3(new MnjSmoothableArc(p5,c3,p6));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a4(new MnjSmoothableArc(p7,c4,p8));//,attr));

    vector<std::shared_ptr<MnjSmoothableSegment>> segVecTmp;
    
	segVecTmp.push_back(l1);segVecTmp.push_back(a1);
  segVecTmp.push_back(l2);segVecTmp.push_back(a2);
  segVecTmp.push_back(l3);segVecTmp.push_back(a3);
  segVecTmp.push_back(l4);segVecTmp.push_back(a4);


    int num_of_divs = 20;
    for ( unsigned int i = 0 ; i < segVecTmp.size() ;i++ ) {
        list<std::shared_ptr<MnjSmoothableSegment>> segVecTmpDiv;
        segVecTmp[i]->Partition(num_of_divs,segVecTmpDiv);
        segVec.insert(segVec.end(),segVecTmpDiv.begin(),segVecTmpDiv.end());
    }
    
    //Input Preparation: step3: specify corners
    for ( unsigned int i = 19 ; i < segVec.size() ;i=i+20 ) {
        //segVec[i]->SetCorner(true);
        segVec[i]->SetCornerRadius(.5);
    }
   
  }
  ////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineArcClosedSmallSegments(){

    //Create Inputs
    vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
    TestLineArcClosedSmallSegmentsInputs(segVec);
    //Execution::insert arcs
    
    vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
    map<unsigned int, int> changes;
    MnjSmoother s;
	  s.CreateArcs(segVec, osegVec, changes );

    //Testing
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(168==osegVec.size());
    //is each segment at odd idex an arc?
    //is radius correct?
    for ( unsigned int i = 0 ; i < osegVec.size() ;i++ ) {
       	  std::shared_ptr<MnjSmoothableArc> icsarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[i]);
          if( (i+1)%21 == 0 ) {
            
               assert(icsarc);//it is an arc S
               assert(MnjSmoothableSegment::NEW == icsarc->Status());//it is a new arc
               double result_r = icsarc->GetRadius();
               assert(fabs(result_r -0.5) < .001);
            }

    }
   std::shared_ptr<MnjSmoothableSegment> ics79 =  osegVec[79];
   std::shared_ptr<MnjSmoothableSegment> ics80 =  osegVec[80];
   int k = 0;
}
////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineArcOpenSmallSegments(){
	
  //Create line segments
  MnjPoint<double> P2(20,0,0);
	MnjPoint<double> P1(10,0,0);
	ICSAttribute attr1;
	attr1.color = 80;
	MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(P2,P1));//,attr1));
    //mnj list< MnjSmoothableLine::shared_ptr >  lsegs;
    list< std::shared_ptr<MnjSmoothableSegment>  >  lsegs;
    l1->Partition(20,lsegs);

    //Create Arc
    ICSAttribute attr2;
	attr2.color = 60;
	MnjPoint<double> o(0,0,0);
	MnjPoint<double> P0(0,10,0);
	std::shared_ptr<MnjSmoothableArc>  l2(new MnjSmoothableArc(P1,o,P0));//,attr2));
    list< std::shared_ptr<MnjSmoothableSegment>  > arcsegs;
    l2->Partition(20,arcsegs);

    //create the list  that defines whole curve
	vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	//make last lin seg a corner
    //list< boost::shared_ptr<MnjSmoothableLine>>::iterator it = lsegs.back();
    std::shared_ptr<MnjSmoothableSegment> last = lsegs.back();
    {
      //last->SetCorner(true);
	  double r=1;
	  last->SetCornerRadius(r);
      
      segVec.assign(lsegs.begin(),lsegs.end());
      segVec.insert(segVec.end(),arcsegs.begin(),arcsegs.end());

	}

    //Insert arcs
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
  map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec, changes );
	
    //Verify the result 
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
  assert(true==connected);
	assert(39==osegVec.size());
  assert(MnjSmoothableSegment::MODIFIED == osegVec[18]->Status());
  assert(MnjSmoothableSegment::NEW == osegVec[19]->Status());
  assert(MnjSmoothableSegment::MODIFIED == osegVec[20]->Status());

	ICSAttribute icsAttr;
	assert(osegVec[19]);
	osegVec[19]->GetICSAttribute(icsAttr);
	std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[19]);
	assert(resultArc);
	double result_r = resultArc->GetRadius();
    double rad_diff = 1 -resultArc->GetRadius();
	assert(fabs(rad_diff) < .001);
	//assert(60==icsAttr.color);
	MnjPoint<double> s1,e1;
	resultArc->GetEnds(s1,e1);
	assert(fabs(s1.x - 9.958932064677038) < .001);//by hand 9.958932064677038 //prog s1.x = 9.9585919546387061
    assert(fabs(s1.y - 0.9053018181818182) < .01);// by hand 0.9053574604251853 //prog s1.y = y = 0.90909090909834389
	//print the result
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
	//GetString(osegVec,tmp);
	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}
////////////////////////////////////////////////////////////////////////////

//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcLineOpen(){
	MnjPoint<double> P2(20,0,0);
	MnjPoint<double> P1(10,0,0);
	ICSAttribute attr1;
	attr1.color = 80;
	MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(P2,P1));//,attr1));
	ICSAttribute attr2;
	attr2.color = 60;
	MnjPoint<double> o(0,0,0);
	MnjPoint<double> P0(0,10,0);
	std::shared_ptr<MnjSmoothableArc>  l2(new MnjSmoothableArc(P1,o,P0));//,attr2));

	vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	if(l2){
	  segVec.push_back(l2);
	  //l2->SetCorner(true);
	  double r=1;
	  l2->SetCornerRadius(r);
	}

	if(l1){
	segVec.push_back(l1);
	}
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
    map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec, changes );
	//verify the result 
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
	assert(3==osegVec.size());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[0]->Status());
    assert(MnjSmoothableSegment::NEW == osegVec[1]->Status());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[2]->Status());

	ICSAttribute icsAttr;
	assert(osegVec[1]);
	osegVec[1]->GetICSAttribute(icsAttr);
	std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[1]);
	assert(resultArc);
	double result_r = resultArc->GetRadius();
  double rad_diff = 1 -resultArc->GetRadius();
	assert(fabs(rad_diff) < .001);
	//assert(60==icsAttr.color);
	MnjPoint<double> s1,e1;
	resultArc->GetEnds(s1,e1);
	assert(fabs(s1.x - 9.95832) < .001);//by hand 9.958932064677038 //prog s1.x = 9.9585919546387061
  assert(fabs(s1.y - 0.9053018181818182) < .01);// tbd: check for accuracy; Sby hand 0.9053574604251853 //prog s1.y = y = 0.90909090909834389
	//print the result
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
	//GetString(osegVec,tmp);
	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}


//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcLineOpenSmallSegments(){
	
    //Create line segments
    
	MnjPoint<double> P1(10,0,0);
  MnjPoint<double> P2(20,0,0);
	ICSAttribute attr1;
	attr1.color = 80;
	MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(P1,P2));//,attr1));
  list< std::shared_ptr<MnjSmoothableSegment>  >  lsegs;
  l1->Partition(20,lsegs);

    //Create Arc
  ICSAttribute attr2;
	attr2.color = 60;
	MnjPoint<double> o(0,0,0);
	MnjPoint<double> P0(0,10,0);
	std::shared_ptr<MnjSmoothableArc>  l2(new MnjSmoothableArc(P1,o,P0));//,attr2));
    list< std::shared_ptr<MnjSmoothableSegment>  > arcsegstmp;
    l2->Partition(20,arcsegstmp);

    //create the list  that defines whole curve
	vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	//make last arc seq. a corner
    //list< boost::shared_ptr<MnjSmoothableLine>>::iterator it = lsegs.back();
    list< std::shared_ptr<MnjSmoothableSegment>  > arcsegs(arcsegstmp.rbegin(),arcsegstmp.rend());
    
    std::shared_ptr<MnjSmoothableSegment> last = arcsegs.back();
    {
      //last->SetCorner(true);
	  double r=1;
	  last->SetCornerRadius(r);
      
      segVec.assign(arcsegs.begin(),arcsegs.end());
      segVec.insert(segVec.end(),lsegs.begin(),lsegs.end());

	}

    //Insert arcs
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
	MnjSmoother s;
  map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec, changes );
	
    //Verify the result 
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
	  assert(39==osegVec.size());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[18]->Status());
    assert(MnjSmoothableSegment::NEW == osegVec[19]->Status());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[20]->Status());

	ICSAttribute icsAttr;
	assert(osegVec[19]);
	osegVec[19]->GetICSAttribute(icsAttr);
	std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[19]);
	assert(resultArc);
	double result_r = resultArc->GetRadius();
  double rad_diff = 1 -resultArc->GetRadius();
	assert(fabs(rad_diff) < .001);
	//assert(60==icsAttr.color);
	MnjPoint<double> s1,e1;
	resultArc->GetEnds(s1,e1);
	assert(fabs(s1.x - 9.958932064677038) < .001);//by hand 9.958932064677038 //prog s1.x = 9.9585919546387061
  assert(fabs(s1.y - 0.9053018181818182) < .01);// by hand 0.9053574604251853 //prog s1.y = y = 0.90909090909834389
	
    //print the result
	char tmp[MAX_STR_SIZE];
	strcpy_s(tmp,MAX_STR_SIZE,"");
	//GetString(osegVec,tmp);
	std::cout << "Printing whole string" << endl;
	std::cout << tmp << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcLineClosedSmallSegmentsInputs(vector<std::shared_ptr<MnjSmoothableSegment>> &osegVec){
    
    vector<std::shared_ptr<MnjSmoothableSegment>> segVecTmp;

    TestLineArcClosedSmallSegmentsInputs(segVecTmp);
    MnjSmoother s;
    bool connected = MnjSmootherUtils::IsConnected(segVecTmp);
    osegVec.assign(segVecTmp.rbegin(),segVecTmp.rend());
    //Clean any previous corner
    //Input Preparation: step3: specify corners
    for ( unsigned int i = 0 ; i < osegVec.size() ;i=i+20 ) {
        osegVec[i]->SetCorner(false);
        osegVec[i]->SetCornerRadius(0.0);
    }
   
    //Input Preparation: specify corners
    for ( unsigned int i = 19 ; i < osegVec.size() ;i=i+20 ) {
        //osegVec[i]->SetCorner(true);
        osegVec[i]->SetCornerRadius(.5);
    }
   
}
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcLineClosedSmallSegments(){

    //Create Inputs
    vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
    TestArcLineClosedSmallSegmentsInputs(segVec);
    //Execution::insert arcs
    vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
    map<unsigned int, int> changes;
    MnjSmoother s;
	s.CreateArcs(segVec, osegVec, changes );

    //Testing

    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(168==osegVec.size());
    //is each segment at odd idex an arc?
    //is radius correct?
    for ( unsigned int i = 0 ; i < osegVec.size() ;i++ ) {
       	  std::shared_ptr<MnjSmoothableArc> icsarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[i]);
          if( (i+1)%21 == 0 ) {
            
               assert(icsarc);//it is an arc S
               assert(MnjSmoothableSegment::NEW == icsarc->Status());//it is a new arc
               double result_r = icsarc->GetRadius();
               assert(fabs(result_r -0.5) < .001);
            }

    }
   
}


///////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcArcClosed(){

    vector<std::shared_ptr<MnjSmoothableSegment>> segVec;

    MnjPoint<double> e1(10,0,0);
	MnjPoint<double> c1(10,10,0);
	MnjPoint<double> s1(0,10,0);
	ICSAttribute attr1;
	attr1.color = 80;
//mnj	std::shared_ptr<MnjSmoothableArc>  a1(new MnjSmoothableArc(s1,c1,e1,attr1));
  	shared_ptr_arc  a1(new MnjSmoothableArc(s1,c1,e1));
    a1->SetCornerRadius(1);
    //a1->SetCorner(true);
   
  MnjPoint<double> e2(0,10,0);
	MnjPoint<double> c2(-10,10,0);
	MnjPoint<double> s2(-10,0,0);
	ICSAttribute attr2;
	attr2.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a2(new MnjSmoothableArc(s2,c2,e2));//mnj,attr2));
  a2->SetCornerRadius(1);
    //a2->SetCorner(true);
	
  MnjPoint<double> e3(-10,0,0);
	MnjPoint<double> c3(-10,-10,0);
	MnjPoint<double> s3(0,-10,0);
	ICSAttribute attr3;
	attr3.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a3(new MnjSmoothableArc(s3,c3,e3));//,attr3));
  a3->SetCornerRadius(1);
  a3->SetCorner(true);
    
  MnjPoint<double> s4(10,0,0);
	MnjPoint<double> c4(10,-10,0);
	MnjPoint<double> e4(0,-10,0);
	ICSAttribute attr4;
	attr4.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a4(new MnjSmoothableArc(s4,c4,e4));//,attr4));
    a4->SetCornerRadius(1);
    a4->SetCorner(true);

   // unsigned int index =0; 
    double r=5;
	segVec.push_back(a1);
	segVec.push_back(a2);
    segVec.push_back(a3);
    segVec.push_back(a4);

    MnjSmoother s;
	//std::shared_ptr<MnjSmoothableArc>  arc(new MnjSmoothableArc());
	//s.CreateArc(a1, a2, arc );
    vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
    map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec, changes );
    
    //Test
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(8==osegVec.size());
    for ( unsigned int i = 1; i < osegVec.size(); i=i+2){

      std::shared_ptr<MnjSmoothableArc> arc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[i]);
     
      if(arc){
        assert(MnjSmoothableSegment::NEW == osegVec[i]->Status());
        double r_arc = arc->GetRadius();
	    assert(fabs(r_arc-1.00) < .0001);
         std::shared_ptr<MnjSmoothableArc> prev_arc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[i-1]);
        CheckResults(prev_arc,arc);
      }

   }
 
}
///////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcArcOpenSmallSegments(){

    vector<std::shared_ptr<MnjSmoothableSegment>> segVec;

    MnjPoint<double> s1(10,0,0);
	MnjPoint<double> c1(0,0,0);
	MnjPoint<double> e1(0,10,0);
	ICSAttribute attr1;
	attr1.color = 80;
	std::shared_ptr<MnjSmoothableArc>  a1(new MnjSmoothableArc(s1,c1,e1));//,attr1));
    

    MnjPoint<double> s2(20,10,0);
	MnjPoint<double> c2(20,0,0);
	MnjPoint<double> e2(10,0,0);
	ICSAttribute attr2;
	attr2.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a2(new MnjSmoothableArc(s2,c2,e2));//,attr2));
	unsigned int index =0; 

    //Create Inputs:
	list<std::shared_ptr<MnjSmoothableSegment>> a1segs;
  a1->Partition(20,a1segs);

    (*a1segs.begin())->SetCornerRadius(1);
    (*a1segs.begin())->SetCorner(true);
    segVec.assign(a1segs.rbegin(),a1segs.rend());
    
    list<std::shared_ptr<MnjSmoothableSegment>> a2segs;
    a2->Partition(20,a2segs);
   // list<std::shared_ptr<MnjSmoothableSegment>>::iterator ittmp1 = a2segs.rbegin();
	//segVec.insert(segVec.end(),a2segs.begin(),a2segs.end());
	segVec.insert(segVec.end(),a2segs.rbegin(),a2segs.rend());

    //temp code 
    double char2 = a2->GetCharacteristic();

    std::shared_ptr<MnjSmoothableArc> icsarc21 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment>(segVec[20]);
    MnjArc arc21 = icsarc21->GetArc();
    double angle21 = arc21.GetAngle();
    double l21 = arc21.GetLength();

    std::shared_ptr<MnjSmoothableArc> icsarc20 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment>(segVec[19]);
    MnjArc arc20 = icsarc20->GetArc();
    double angle20 = arc20.GetAngle();
    double l20 = arc20.GetLength();

    for (unsigned int i = 0 ; i < segVec.size() ;i++) {
		double c = segVec[i]->GetCharacteristic();
        std::shared_ptr<MnjSmoothableArc> arc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment>(segVec[i]);
        double angle =0;
        if(arc){
           angle = arc->GetAngle();
        }
        if(c>2)
            bool e = 1;
	}
	//execute
    MnjSmoother s;
	  vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
    map<unsigned int, int> changes;
	  s.CreateArcs(segVec, osegVec, changes);
    
    //test
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    //assert(33==osegVec.size());
    assert(31==osegVec.size());
    //std::for_each(osegVec.begin(),osegVec.begin(),&TestMnjSmoother<Segment,MnjArc,MnjLine>::IsNew);

    //vector<boost::shared_ptr<MnjSmoothableSegment>> it1;
	for (unsigned int i = 0 ; i < osegVec.size() ;i++) {
		if(MnjSmoothableSegment::NEW == osegVec[i]->Status())
            break;
	}

    std::shared_ptr<MnjSmoothableSegment> prev =  osegVec[14];
    std::shared_ptr<MnjSmoothableSegment> newseg =  osegVec[15];
    std::shared_ptr<MnjSmoothableSegment> next =  osegVec[16];

    assert(MnjSmoothableSegment::MODIFIED == prev->Status());
    assert(MnjSmoothableSegment::NEW == newseg->Status());
    assert(MnjSmoothableSegment::MODIFIED == next->Status());

    std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (newseg);
    double r_arc = resultArc->GetRadius();
	  assert(fabs(r_arc-1.00) < .0001);
    
    MnjPoint<double> sp(9.0909090909090899 ,4.1659779045053087 ,0.00000000000000000);
    MnjPoint<double> r_sp ; resultArc->GetStartPoint(r_sp);
    double dsp = GeomUtils::GetDistance(sp,r_sp);
    assert(fabs(dsp) < .0001);

    MnjPoint<double> ep(10.909090909090910 ,4.1659779045053087, 0.00000000000000000);
    MnjPoint<double> r_ep ; resultArc->GetEndPoint(r_ep);
    double d_ep = GeomUtils::GetDistance(ep,r_ep);
    assert(fabs(d_ep) < .0001);

    MnjPoint<double> cp(10.000000000000000 ,4.5825756949558398, 0.00000000000000000);
    MnjPoint<double> r_cp ; resultArc->GetCenter(r_cp);
    double d_cp = GeomUtils::GetDistance(cp,r_cp);
    assert(d_cp < .0001);

    int error = 0;
    MnjPoint<double> i1= prev->GetCommonPoint(resultArc,error);
    std::shared_ptr<MnjSmoothableArc> prevarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (prev);
    MnjArc arc1 = prevarc->GetArc();
    double cal_r1 = GeomUtils::GetDistance(arc1.GetCenter(),i1);
    assert(fabs(cal_r1-a1->GetRadius())<.0001);

    std::shared_ptr<MnjSmoothableArc> nextArc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (next);
    assert(nextArc);
    MnjArc arc2= nextArc->GetArc();
    MnjPoint<double> i2 = next->GetCommonPoint(newseg,error);
    double cal_r2 = GeomUtils::GetDistance(arc2.GetCenter(),i2);
    assert(fabs(cal_r2-a1->GetRadius())<.0001);
//	std::for_each(osegVec.begin(),osegVec.begin(),Print);
}
////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcArcClosedSmallSegments(){


  MnjPoint<double> e1(10,0,0);
	MnjPoint<double> c1(10,10,0);
	MnjPoint<double> s1(0,10,0);
	ICSAttribute attr1;
	attr1.color = 80;
	std::shared_ptr<MnjSmoothableArc>  a1(new MnjSmoothableArc(s1,c1,e1));//,attr1));
    a1->SetCornerRadius(1);
    a1->SetCorner(true);
   
    MnjPoint<double> e2(0,10,0);
	MnjPoint<double> c2(-10,10,0);
	MnjPoint<double> s2(-10,0,0);
	ICSAttribute attr2;
	attr2.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a2(new MnjSmoothableArc(s2,c2,e2));//,attr2));
    a2->SetCornerRadius(1);
    a2->SetCorner(true);
	
  MnjPoint<double> e3(-10,0,0);
	MnjPoint<double> c3(-10,-10,0);
	MnjPoint<double> s3(0,-10,0);
	ICSAttribute attr3;
	attr3.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a3(new MnjSmoothableArc(s3,c3,e3));//,attr3));
  a3->SetCornerRadius(1);
  a3->SetCorner(true);
    
  MnjPoint<double> s4(10,0,0);
	MnjPoint<double> c4(10,-10,0);
	MnjPoint<double> e4(0,-10,0);
	ICSAttribute attr4;
	attr4.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a4(new MnjSmoothableArc(s4,c4,e4));//,attr4));
  a4->SetCornerRadius(1);
  a4->SetCorner(true);

   // unsigned int index =0; 
  vector<std::shared_ptr<MnjSmoothableSegment>> segVecTmp;

	segVecTmp.push_back(a1);
  segVecTmp.push_back(a4);
  segVecTmp.push_back(a3);
	segVecTmp.push_back(a2);

  int num_of_divs = 20;
  vector<std::shared_ptr<MnjSmoothableSegment>> segVec;

  for ( unsigned int i = 0 ; i < segVecTmp.size() ;i++ ) {
        list<std::shared_ptr<MnjSmoothableSegment>> segVecTmpDiv;
        segVecTmp[i]->Partition(num_of_divs,segVecTmpDiv);
        segVec.insert(segVec.end(),segVecTmpDiv.begin(),segVecTmpDiv.end());
  }
    
    //Input Preparation: step3: specify corners
    for ( unsigned int i = 19 ; i < segVec.size() ;i=i+20 ) {
        segVec[i]->SetCorner(true);
        segVec[i]->SetCornerRadius(1);
    }

    MnjSmoother s;
	//std::shared_ptr<MnjSmoothableArc>  arc(new MnjSmoothableArc());
	//s.CreateArc(a1, a2, arc );
    vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
    map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec, changes );
    
    //Test
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(44==osegVec.size());
    for ( unsigned int i = 1; i < osegVec.size(); i++){

		std::shared_ptr<MnjSmoothableArc> arc = std::dynamic_pointer_cast<MnjSmoothableArc, MnjSmoothableSegment> (osegVec[i]);
     
      if(0==(i+1)%11){
        assert(arc);
        assert(MnjSmoothableSegment::NEW == osegVec[i]->Status());
        int newarc = 1;
        double r_arc = arc->GetRadius();
	    assert(fabs(r_arc-1.00) < .0001);
		std::shared_ptr<MnjSmoothableArc> prev_arc = std::dynamic_pointer_cast<MnjSmoothableArc, MnjSmoothableSegment> (osegVec[i - 1]);
         CheckResults(prev_arc,arc);
        }
      }

 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::CheckResults(std::shared_ptr<MnjSmoothableArc> icsarc1, std::shared_ptr<MnjSmoothableArc> icsarc2){
    int error = 0;
    MnjPoint<double> i1= icsarc1->GetCommonPoint(icsarc2,error);//mnj

    MnjArc arc1; 
    icsarc1->GetArc(arc1);
    double cal_r1 = GeomUtils::GetDistance(arc1.GetCenter(),i1);
    assert(fabs(cal_r1- arc1.GetRadius())<.0001);

    MnjArc arc2; 
    icsarc2->GetArc(arc2); 
    double cal_r2 = GeomUtils::GetDistance(arc2.GetCenter(),i1);
    assert(fabs(cal_r2-arc2.GetRadius())<.0001);

    assert(fabs(cal_r2-icsarc1->GetCornerRadius())<.0001);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestLineArcClosedRedundant(){

    MnjPoint<double> p1(10,5,0);
    MnjPoint<double> p2(5,10,0);
    MnjPoint<double> p3(-5,10,0);
    MnjPoint<double> p4(-10,5,0);
    MnjPoint<double> p5(-10,-5,0);
    MnjPoint<double> p6(-5,-10,0);
    MnjPoint<double> p7(5,-10,0);
    MnjPoint<double> p8(10,-5,0);
    
    ICSAttribute attr;
    attr.color = 60;
    MnjSmoothableLine::shared_ptr l1(new MnjSmoothableLine(p8,p1));//,attr));
	MnjSmoothableLine::shared_ptr l2(new MnjSmoothableLine(p2,p3));//,attr));
	MnjSmoothableLine::shared_ptr l3(new MnjSmoothableLine(p4,p5));//,attr));
	MnjSmoothableLine::shared_ptr l4(new MnjSmoothableLine(p6,p7));//,attr));

    MnjPoint<double> c1(5,5,0);
    MnjPoint<double> c2(-5,5,0);
    MnjPoint<double> c3(-5,-5,0);
    MnjPoint<double> c4(5,-5,0);

    std::shared_ptr<MnjSmoothableArc>  a1(new MnjSmoothableArc(p1,c1,p2));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a2(new MnjSmoothableArc(p3,c2,p4));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a3(new MnjSmoothableArc(p5,c3,p6));//,attr));
	std::shared_ptr<MnjSmoothableArc>  a4(new MnjSmoothableArc(p7,c4,p8));//,attr));

    vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
	segVec.push_back(l1);segVec.push_back(a1);
    segVec.push_back(l2);segVec.push_back(a2);
    segVec.push_back(l3);segVec.push_back(a3);
    segVec.push_back(l4);segVec.push_back(a4);

    for ( unsigned int i = 0 ; i < segVec.size() ;i++ ) {
        segVec[i]->SetCornerRadius(.5);
        segVec[i]->SetCorner(true);
    }

    // insert arcs
    vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
    map<unsigned int, int> changes;
    MnjSmoother s;
	s.CreateArcs(segVec, osegVec, changes );
    //Test
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(8==osegVec.size());
    //is each segment at odd idex an arc?
    //is radius correct?
    for ( unsigned int i = 0 ; i < osegVec.size() ;i++ ) {
       	std::shared_ptr<MnjSmoothableArc> icsarc = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (osegVec[i]);
        if(1==i%2){
            assert(icsarc);
            double result_r = icsarc->GetRadius();
            assert(fabs(result_r -5.0) < .001);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestArcArcOpen(){

  vector<std::shared_ptr<MnjSmoothableSegment>> segVec;

  MnjPoint<double> s1(10,0,0);
	MnjPoint<double> c1(0,0,0);
	MnjPoint<double> e1(0,10,0);
	ICSAttribute attr1;
	attr1.color = 80;
	std::shared_ptr<MnjSmoothableArc>  a1(new MnjSmoothableArc(s1,c1,e1));//,attr1));
    a1->SetCornerRadius(1);
    a1->SetCorner(true);

    MnjPoint<double> s2(20,10,0);
	MnjPoint<double> c2(20,0,0);
	MnjPoint<double> e2(10,0,0);
	ICSAttribute attr2;
	attr2.color = 60;
	std::shared_ptr<MnjSmoothableArc>  a2(new MnjSmoothableArc(s2,c2,e2));//,attr2));
	unsigned int index =0; 
	
	double r=5;
	segVec.push_back(a1);
	segVec.push_back(a2);
	MnjSmoother s;
	//std::shared_ptr<MnjSmoothableArc>  arc(new MnjSmoothableArc());
	vector<std::shared_ptr<MnjSmoothableSegment>> osegVec;
  map<unsigned int, int> changes;
	s.CreateArcs(segVec, osegVec, changes);
    
    //Test
    bool connected = MnjSmootherUtils::IsConnected(osegVec);
    assert(true==connected);
    assert(MnjSmoothableSegment::MODIFIED == osegVec[0]->Status());
    assert(MnjSmoothableSegment::NEW == osegVec[1]->Status());
    assert(MnjSmoothableSegment::MODIFIED == osegVec[2]->Status());

	std::shared_ptr<MnjSmoothableArc> resultArc = std::dynamic_pointer_cast<MnjSmoothableArc, MnjSmoothableSegment> (osegVec[1]);
    double r_arc = resultArc->GetRadius();
	  assert(fabs(r_arc-1.00) < .0001);
    
    int error = 0;
    MnjPoint<double> i1= a1->GetCommonPoint(resultArc,error);
    MnjArc arc1; 
    a1->GetArc(arc1);
    double cal_r1 = GeomUtils::GetDistance(arc1.GetCenter(),i1);
    assert(fabs(cal_r1-a1->GetRadius())<.0001);

    MnjArc arc2; 
    a2->GetArc(arc2);
    MnjPoint<double> i2 = a2->GetCommonPoint(resultArc,error);
    double cal_r2 = GeomUtils::GetDistance(arc2.GetCenter(),i2);
    assert(fabs(cal_r2-a1->GetRadius())<.0001);
//	std::for_each(osegVec.begin(),osegVec.begin(),Print);
}
////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::IsNew(std::shared_ptr<MnjSmoothableSegment> seg) {
    if(seg){
        if(MnjSmoothableSegment::NEW == seg->Status()) {
        ;
        }
            //return true;
    }
    //return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename MnjSmoothableSegment, typename MnjSmoothableLine, typename MnjSmoothableArc>
void TestMnjSmoother::TestIsConnected(void){
  vector<std::shared_ptr<MnjSmoothableSegment>> segVec;
    for ( int i = 0 ; i < 10 ; i++){
	     MnjPoint<double> x2(10-i,0,0);
	     MnjPoint<double> x1(9-i,0,0);
	     ICSAttribute attr1;
	     attr1.color = 80;
	     MnjSmoothableLine::shared_ptr l(new MnjSmoothableLine(x2,x1));//,attr1));
		 if(9==i){
			 l->SetCorner(true);
			 l->SetCornerRadius(5);
		 }
		 segVec.push_back(l);
	}
    //make disconnected
    segVec[5]->SetStartPoint(MnjPoint<double>(5000,0,0));
    vector<std::shared_ptr<MnjSmoothableSegment>>::iterator it1;
    double od = -1;
    MnjSmoother s;
    bool flag   = MnjSmootherUtils::IsConnected(segVec,it1,od);
    assert(false == flag);
 }
 