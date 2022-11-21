//copyright(c) 2009- 2016 Manoj Lnu. All rights reserved. 
// 
//

#include <iostream>
#include <vector>
#include <list>
//Local includes 
#include "MnjSmoothableSegment.h"
#include "MnjArc.h"
#include "MnjDirection.h"
#include "MnjLine.h"
#include "MnjSmoothableArc.h"
#include "MnjSmoothableLine.h"
#include "MnjPoint.h" 
#include "GeomUtils.h"
//#include "MnjCircleCR.h"
#include "MnjCircle.h"
#include "MnjSmootherUtils.h"

//#include "TestMnjSmoother.h"
#include "MnjInfiniteLine.h"
#include "MnjBiDirectionalMerge.h"
#include "MnjOperators.h"
#include "MnjSmoother.h"

////////////////////////////////////////////
////////////////////////////////////////////////////////
using namespace std; 
//using namespace boost; 
//tbd:

int MnjSmoother::CreateArc( 
	shared_ptr<MnjSmoothableLine> &seg1,
	shared_ptr<MnjSmoothableLine> &seg2,
	shared_ptr<MnjSmoothableArc> &oarc){
	
	int error = 0;
	
	//TBD: check for collinear lines and return error. 

	////////TBD : remove/comment///////
	//TestMnjSmoother test;
	//char str[MAX_STR_SIZE];
	//strcpy_s(str,MAX_STR_SIZE,"");
	//test.Display(seg1,str);
	//test.Display(seg2,str);
     //////////////////////////////////

     //input valdation 
	if(!seg1||!seg2)
		return -1; 
	double r = seg1->GetCornerRadius();
    if(0.0 == r) 
	   return -1;
	std::shared_ptr<MnjLine> parallel_seg1(new MnjLine());
	MnjPoint<double>  hintpoint1;
	GeomUtils::GetFarEndOfOtherLine(seg1->GetLine(),seg2->GetLine(),hintpoint1);
	seg1->CreateParallelLine(r, hintpoint1, parallel_seg1);

	std::shared_ptr<MnjLine> parallel_seg2(new MnjLine());
	MnjPoint<double>  hintpoint2;
	GeomUtils::GetFarEndOfOtherLine(seg2->GetLine(),seg1->GetLine(),hintpoint2);
    seg2->CreateParallelLine(r, hintpoint2, parallel_seg2);
    
	if(parallel_seg1){
		MnjPoint<double> center;
		parallel_seg1->Intersect(*parallel_seg2,center);
		MnjPoint<double>  p1;
		if( -1 == seg1->Project(center,p1) ){
			//MessageBox(NULL,"Error 21",__FUNCTION__,MB_OK);
			return error = -21;
		}
		MnjPoint<double> p2;
		if( -1 == seg2->Project(center,p2) ) 
		{
			//MessageBox(NULL,"Error 22",__FUNCTION__,MB_OK);
			return error = -22;
		}
        //set the values into the segments
        MnjPoint<double> cornerPoint = seg1->GetCommonPoint(seg2,error);

        seg1->ResetThePoint(cornerPoint,p1);
		/////////////debug
		//test.Display(p1,str);
		//test.Display(center,str);
		//test.Display(p2,str);
		////////////
        oarc->Set(p1,center,p2);
        seg2->ResetThePoint(cornerPoint,p2);

   	}
   return 0;
  
}

/////////////////////////////////////////////////////////////
int MnjSmoother::CreateArc( 
	std::shared_ptr<MnjSmoothableLine> &l,
	std::shared_ptr<MnjSmoothableArc> &a,
	std::shared_ptr<MnjSmoothableArc> &oarc){

   int error = 0;
   if(!l||!a)
		return -1;
   double r = l->GetCornerRadius();
   return CreateArc(l,a,r,oarc);

}
/////////////////////////////////////////////////////////////
int MnjSmoother::CreateArc( 
	std::shared_ptr<MnjSmoothableArc> &a,
	std::shared_ptr<MnjSmoothableLine> &l,
	std::shared_ptr<MnjSmoothableArc> &oarc){
    int error = 0;
    if(!l||!a)
		return -1;
    double r = a->GetCornerRadius();
    return CreateArc(l,a, r, oarc);
}
/////////////////////////////////////////////////////////////////////
int MnjSmoother::CreateArc( 
	std::shared_ptr<MnjSmoothableLine> &l,
	std::shared_ptr<MnjSmoothableArc> &a,
	double &ir,
	std::shared_ptr<MnjSmoothableArc> &oarc){

      ///approach2//
       
      MnjPoint<double> cp ;
      int error= GetCenter(l,a,ir,cp);
       if(error>=0){
           MnjPoint<double> pt_on_a;
           error = a->Project(cp,pt_on_a);
           if(error>=0){
               MnjPoint<double> pt_on_l;
               error = l->Project(cp,pt_on_l);
               if(error>=0){
                 MnjPoint<double> cornerPoint = l->GetCommonPoint(a,error);
                 l->ResetThePoint(cornerPoint,pt_on_l);
                 a->ResetThePoint(cornerPoint,pt_on_a);
                 oarc->SetSmallerArc(pt_on_a,cp,pt_on_l);
               }
           }
       }
	   //remove
	   //TestMnjSmoother test;
	   //test.NewDisplay(l,__FUNCTION__);
	   //test.NewDisplay(a,__FUNCTION__);
	   //test.NewDisplay(oarc,__FUNCTION__);
   return error;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int MnjSmoother::CreateArc( 
	std::shared_ptr<MnjSmoothableArc> &a1,
	std::shared_ptr<MnjSmoothableArc> &a2,
	std::shared_ptr<MnjSmoothableArc> &oarc){

   int error = -2;//mnj
   if(!a1||!a2)
		return -1;
   
   MnjArc arc1;
   a1->GetArc(arc1);
   MnjCircle circle1(arc1); 

   MnjArc arc2;
   a2->GetArc(arc2);
   MnjCircle circle2(arc2); 

   shared_ptr_vec_pt pt_vec;
   //Increment the radii by r and Intersect
   double r = a1->GetCornerRadius(); 

   double r1 = circle1.Radius();
   double locus_r1 = r1+r ;
   circle1.SetRadius(locus_r1);

   double r2 = circle2.Radius();
   double locus_r2 = r2+r ;
   circle2.SetRadius(locus_r2);
  
  circle1.Intersect( circle2,pt_vec);
  MnjPoint<double> c1 = circle1.Center();
  MnjPoint<double> c2 = circle2.Center();

   for( unsigned int i = 0; i <pt_vec.size() ; i++ ) {

       MnjLine l2(*(pt_vec[i]),c2);
       MnjPoint<double> p2 ;
       l2.GetPointOnLine(*(pt_vec[i]),r,p2);
       
       if(a2->IsPointOnArc(p2)){
       
           MnjLine l1(*(pt_vec[i]),c1);
           MnjPoint<double> p1 ;
           l1.GetPointOnLine(*(pt_vec[i]),r,p1);
       
           if(a1->IsPointOnArc(p1)){
               MnjPoint<double> cp = *(pt_vec[i]);
               oarc->SetSmallerArc(p1,cp,p2);
               MnjPoint<double> cornerPoint = a1->GetCommonPoint(a2,error);
               a1->ResetThePoint(cornerPoint,p1);
               //oarc->Set(p1,cp,p2);
               a2->ResetThePoint(cornerPoint,p2);
               error = 0;
               break;//tbd: what if both points qualify the criteria
           }
       
       }

   }

   return error;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MnjSmoother::IdentifyRedundantCornerRequest(std::list<std::shared_ptr<MnjSmoothableSegment>> &list){
  
 if(list.size() > 1) {

    std::list<std::shared_ptr<MnjSmoothableSegment>>::iterator it0=list.begin();
   
    for ( std::list<std::shared_ptr<MnjSmoothableSegment>>::iterator it = it0;  it!=list.end(); it++ ) {
     ;
     
      if((*it)->IsCorner()){
         std::list<std::shared_ptr<MnjSmoothableSegment>>::iterator next=GeomUtils::NextIter(list,it);
         std::list<std::shared_ptr<MnjSmoothableSegment>>::iterator prev=GeomUtils::PrevIter(list,it);
        
         if( (*it)->IsTangent(*next)  && (*it)->IsTangent(*prev) ) {
                (*it)->SetCornerAttribute(MnjSmoothableSegment::NEXT_PREV_TANGENT_NOT_NEEDED);
         }
        
      }
      
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MnjSmoother::SetStatus(std::list<std::shared_ptr<MnjSmoothableSegment>> list,
                            MnjSmoothableSegment::SegmentChange ch){
  std::list<std::shared_ptr<MnjSmoothableSegment>>::iterator it0=list.begin();
  for ( std::list<std::shared_ptr<MnjSmoothableSegment>>::iterator it = it0;  it!=list.end(); it++ ) {

      (*it)->SetStatus(ch);
  }
   
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void MnjSmoother::GetFarEndOfOtherLine( 
	const boost::shared_ptr<MnjLine> &l1,
	const boost::shared_ptr<MnjLine> &l2,
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
		GeomUtils::DistancePointInfiniteLine(p21,p11,p12,d1);

		MnjPoint<double> p22;
		l2->GetEndPoint(p22);
		double d2= 0;
		GeomUtils::DistancePointInfiniteLine(p22,p11,p12,d2);
		if(d2 < d1 ) 
			oPoint = p21;
		else
			oPoint = p22;
		if(fabs(d1-d2) <.0001)//debug break
		{
			;//cout  <<  the diffrence is too small. 
		}
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
void MnjSmoother::SelectNewArcEnd(const MnjPoint<double> &p1,
	                               const MnjPoint<double> &pc,
	                               const std::shared_ptr<MnjSmoothableArc> &icsarc,
								                  const MnjPoint<double> &p2cand1,
								   const MnjPoint<double> &p2cand2,
								         bool &op2_found,
                                         MnjPoint<double> &op2 
	){
		MnjArc arc;
		icsarc->GetArc(arc);
        MnjPoint<double> p2cand1tmp = p2cand1; 
	bool p2cand1onarc = arc.IsPointOnArc(p2cand1tmp);
        MnjPoint<double> p2cand2tmp = p2cand2;
	bool p2cand2onarc = arc.IsPointOnArc(p2cand2tmp);
	
	if(p2cand1onarc && !p2cand2onarc){
	  op2 = p2cand1;
	  op2_found = true;
	}else if ( !p2cand1onarc && p2cand2onarc){
	  op2 = p2cand2;
	  op2_found = true;
   }else if(!p2cand1onarc && !p2cand2onarc){
      op2_found = false;
   }
   else {//if both are on arc 
	   MnjArc candidate1(p1,pc,p2cand1);
	   MnjArc candidate2(p1,pc,p2cand2);
      double length1 = MnjArc(p1,pc,p2cand1).GetLength();
	  double length2 = MnjArc(p1,pc,p2cand2).GetLength();
	  //tbd:clarify: if radius or tolerance is a criteria here 
	  op2_found = true;
	  if(length1<length2){
	    op2 = p2cand1;
	       
	  }else{
	    op2 = p2cand2;
	  }
   }
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
void MnjSmoother::InsertArc( 
			                 std::shared_ptr<MnjSmoothableArc> &arc,
			                 vector<std::shared_ptr<MnjSmoothableSegment>>::iterator it,
							 vector<std::shared_ptr<MnjSmoothableSegment>>::iterator &oit1,
	                         vector<std::shared_ptr<MnjSmoothableSegment>> &ioSegVec){
								 

	 oit1 = ioSegVec.insert(++it,arc);
	 oit1++;
	 if(oit1==ioSegVec.end()){
	    oit1=ioSegVec.begin();
	 }
		 

}

///////////////////////////////////////////////////////////////////////////////////////////
int MnjSmoother::CreateArc(int a,
	                         std::shared_ptr<MnjSmoothableSegment> &isimpleSeg1, 
                             std::shared_ptr<MnjSmoothableSegment> &isimpleSeg2, 
	                         std::shared_ptr<MnjSmoothableArc>  &arc){
	int error = 0;
	if(!isimpleSeg1 || !isimpleSeg1 || !arc ) 
        return -1;
	
    std::shared_ptr<MnjSmoothableArc> arc1 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (isimpleSeg1);
    std::shared_ptr<MnjSmoothableLine> line1 = std::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (isimpleSeg1);
	std::shared_ptr<MnjSmoothableArc> arc2 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (isimpleSeg2);
    std::shared_ptr<MnjSmoothableLine> line2 = std::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (isimpleSeg2);
	
	if(line1 && line2){
	   error = CreateArc(line1,line2,arc);
	}
    else if(line1 && arc2){
	   error = CreateArc(line1,arc2,arc);
	}
	else if(arc1 && line2){
	   error = CreateArc(arc1,line2,arc);
	}
    else if(arc1 && arc2){
	   error = CreateArc(arc1,arc2,arc);
    }

    if(!(error<0) && arc){

        ICSAttribute attr;
        vector< std::shared_ptr<MnjSmoothableSegment> > icsSegVec;
	      icsSegVec.push_back(isimpleSeg1);
	      icsSegVec.push_back(isimpleSeg2);
   	    
        //MnjSmootherUtils::GetAttributeWithLowestValues(icsSegVec,attr);
        //arc->SetICSAttribute(attr);
        
        //Set scribe
        if ( isimpleSeg1->IsScribe() && isimpleSeg2->IsScribe() ){
         arc->SetSegProp(ICSAttribute::SEG_SCRIBE);
        }
        
        arc->SetStatus(MnjSmoothableSegment::NEW);
        //isimpleSeg1->SetStatus(MnjSmoothableSegment::SegmentChange::MODIFIED);
        isimpleSeg1->SetStatus(MnjSmoothableSegment::MODIFIED);
        isimpleSeg2->SetStatus(MnjSmoothableSegment::MODIFIED);
    }

    	  // arc->Print();
     return error; 
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
void MnjSmoother::CreateArcs(vector<std::shared_ptr<MnjSmoothableSegment>> &isegVec, 
                              vector<std::shared_ptr<MnjSmoothableSegment>>  &osegs,
                              map<unsigned int,int> &oChange){

   double tol=.0001;
   int error=0;
   double dist=-1;
   vector<std::shared_ptr<MnjSmoothableSegment>>::iterator brokenit;
   bool connected = MnjSmootherUtils::IsConnected(isegVec,brokenit,dist);
   if(!connected ) 
       return;
   //create a list from vector
   std::list<std::shared_ptr<MnjSmoothableSegment>> compressedSegList(isegVec.begin(), isegVec.end());
  
   std::list<std::shared_ptr<MnjSmoothableSegment>>::iterator it0=compressedSegList.begin();
   
   //Mark all of them orginal
   SetStatus(compressedSegList,MnjSmoothableSegment::ORIGINAL);

   //Get rid of small edges ( if needed)
   MnjBiDirectionalMerge bm;
   bm.CompressNonRecursive(compressedSegList,it0,oChange,tol);
   //MessageBox(NULL,"After CompressNonRecursive",__FUNCTION__,MB_OK);
   
   //Get rid of redundant corner request (where the corner is already tangent)
   IdentifyRedundantCornerRequest(compressedSegList);
   vector<std::shared_ptr<MnjSmoothableSegment>> compressedSegVec(compressedSegList.begin(), compressedSegList.end());

   // check compress results  for connectvity and planarity
   connected = MnjSmootherUtils::IsConnected(compressedSegVec);
   if(!connected ) 
       return;
   
   //call create arc for each of them
   vector<std::shared_ptr<MnjSmoothableSegment>>::iterator it=compressedSegVec.begin();
   while (it != compressedSegVec.end() ) {

	   //if((*it)->IsCorner() ){//tbd: remove
	      
		  //MessageBox(NULL,"Entered while loop.",__FUNCTION__,MB_OK);		 
		  //char str[MAX_STR_SIZE];
		  //strcpy_s(str,MAX_STR_SIZE,"");
		  //TestMnjSmoother test;
		  //test.Display(*it,str);
	    
	   //}

	 if((*it)->IsRelevantCorner() ){
         
		 //MessageBox(NULL,"Relevant corner",__FUNCTION__,MB_OK);		 
		 
		 vector<std::shared_ptr<MnjSmoothableSegment>>::iterator it1=it+1;
		 if(it1== compressedSegVec.end()){
			 it1=  compressedSegVec.begin();
		 }//handle closed curve
         std::shared_ptr<MnjSmoothableArc>  arc(new MnjSmoothableArc());
		 
		 error = CreateArc(1,*it,*it1,arc);
		 
		 ////////////////////////TBD: remove
		 //char str[MAX_STR_SIZE];
		 //strcpy_s(str,MAX_STR_SIZE,"");
		 //TestMnjSmoother test;
		 //test.Display(*it,str);
		 //test.Display(*it1,str);
		 ////////////////////////
		 
		 if(arc && error >= 0 ){
			 vector<std::shared_ptr<MnjSmoothableSegment>>::iterator newIt;
			 InsertArc(arc,it,newIt,compressedSegVec);   
			 ///////////////////////////////////
			 //char str[MAX_STR_SIZE];//tbd: debug , removelater
			 //strcpy_s(str,MAX_STR_SIZE,"");
			 //TestMnjSmoother test;
			 //test.Display(arc,str);
			 //////////////////////////////////////
			 if(newIt == compressedSegVec.begin() )
				 break;
			 it=newIt;
			 continue;
		 }
	   }
	   it++;
   }
   osegs = compressedSegVec;
}
///////////////////////////////////////////////////////////////////////////////////
void MnjSmoother::Copy(vector<std::shared_ptr<MnjSmoothableSegment>> &isegVec, 
                        vector<std::shared_ptr<MnjSmoothableSegment>>  &osegs){
osegs = isegVec;
		/*vector<boost::shared_ptr<MnjSmoothableSegment>>::reverse_iterator it;
		for (it = isegVec.rbegin() ; it != isegVec.rend();it++){
            ;//osegs.push_back(it);
		}*/
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
int MnjSmoother::GetCenter(
    std::shared_ptr<MnjSmoothableLine> &l,
	std::shared_ptr<MnjSmoothableArc> &a,
	double &ir,
	MnjPoint<double> &ocp
    ){
        int error =0;
        //Create Circle 
        MnjPoint<double> commonPoint = l->GetCommonPoint(a,error);
        MnjDirection  tangent= a->TangentAtEnd(commonPoint);
        int factor = 1;
        MnjPoint<double> otherEndOfLine = l->GetOtherEnd(commonPoint,error);
        if(tangent.IsObtuse(MnjDirection(commonPoint,otherEndOfLine))) 
            factor = -1; 
         
        MnjCircle tmpCircle(a->GetArc());
        double R = a->GetRadius();
        double tmpCicrleR = R+factor*ir;
        tmpCircle.SetRadius(tmpCicrleR);

        //Create Line
        MnjPoint<double> pTowardsArc;
        error = GetAPointTowardsArc(l,a,pTowardsArc); 
        std::shared_ptr<MnjLine> parallel_line;
        l->CreateParallelLine(ir,pTowardsArc,parallel_line);
        //Take Intersection
        MnjInfiniteLine inf_parallel_line(&(*parallel_line));
        shared_ptr_vec_pt pt_vec;
        tmpCircle.Intersect(inf_parallel_line,pt_vec);
        if(1==pt_vec.size()){ 
             ocp = *pt_vec[0]; 
             return 1;
        }else if (0==pt_vec.size()) {
            return -1;
        } 
        //Select valid Intersection point 
        //The (center point of new arc) point must qualify these conditions:
        // 1. It should project on line segment.
        // 2. the distance between the point and arc a == r

        shared_ptr_vec_pt can_project_pt_vec;
        GeomUtils::GetPointsThatProjectOnLineSegment(*(l->GetLine()),  
                 pt_vec,
                 can_project_pt_vec);
        if(1==can_project_pt_vec.size()){ 
            ocp = *can_project_pt_vec[0]; 
            return 11;
        } else if (0==can_project_pt_vec.size()) {
            return -2;
        }
        //test that the point(s) are at distance r fron the circle. 
        shared_ptr_vec_pt pt_at_distance_r_from_arc_vec;
		auto arc1 = a->GetArc();
        GeomUtils::GetPointsAtGivenDistanceFromArc(arc1,ir,  
                 can_project_pt_vec,
                 pt_at_distance_r_from_arc_vec);
        if(1==pt_at_distance_r_from_arc_vec.size()){ 
            ocp = *pt_at_distance_r_from_arc_vec[0]; 
            return 22;
        } else  {
            return -22;
        }
       
        return error;
}
///////////////////////////////////////////////////////////////////////////////////////
int MnjSmoother::GetAPointTowardsArc(std::shared_ptr<MnjSmoothableLine> &l,
	                                         std::shared_ptr<MnjSmoothableArc> &a,
                                             MnjPoint<double> &op) {
   int error = 0;
  
   MnjPoint<double> cornerPoint = l->GetCommonPoint(a,error);
   MnjDirection startTangent = a->TangentAtEnd(cornerPoint);
   op = cornerPoint + startTangent*10; 
   
   return error;
  }
////////////////////////////////////////////////////////////////////////////////////////
 int MnjSmoother::GetFactor(std::shared_ptr<MnjSmoothableLine> &l,
	                         std::shared_ptr<MnjSmoothableArc> &a, 
                             //double &r, 
                             int &ofactor){
   int error = 0;
   MnjPoint<double> commonPoint = l->GetCommonPoint(a,error);
   MnjDirection  tangent= a->Tangent(commonPoint);
        
   ofactor = 1;
   MnjPoint<double> otherEndOfLine = l->GetOtherEnd(commonPoint,error);
   if(tangent.IsObtuse(MnjDirection(commonPoint,otherEndOfLine))) {
       ofactor = -1; 
   }
   return error;
 }
///////////////////////////////////////////////////////////////////////////////////////
 /*
int MnjSmoother::LineArcPointOnLine(boost::shared_ptr<MnjSmoothableLine> &l,
	                                 boost::shared_ptr<MnjSmoothableArc>  &a, 
                                     double &r, MnjPoint<double> &opt_on_line) {
   
   int error = 0;
   double R = a->GetRadius();
   //double r = l->GetCornerRadius();
   if(0.0 == r || r < 0 ) 
	   return -1;
   int factor = 1;//tmp
   error = GetFactor(l,a,factor); 
   double distance_from_start= sqrt(pow((R+factor*r),2) - pow(r,2)) -R ; 
   if(distance_from_start < 0 )
       return -2;//error

   MnjPoint<double> cornerPoint = l->GetCommonPoint(a,error);
   error= l->GetPointOnLine(cornerPoint,distance_from_start,opt_on_line);	
   return error;

}
*/
///////////////////////////////////////////////////////////////////////////////////////
int MnjSmoother::LineArcCenter(std::shared_ptr<MnjSmoothableLine> &l,
	                                 std::shared_ptr<MnjSmoothableArc> &a,
                                     double &r, 
                                     const MnjPoint<double> &ipt_on_line,
                                     MnjPoint<double> &oc) {

   int error = 0;
   MnjInfiniteLine perp_line;
  
   MnjPoint<double> cornerPoint = l->GetCommonPoint(a,error);
   double R = a->GetRadius();
   
   if(0.0 == r || r < 0 ) 
	   return -1;

   double distance_from_start= sqrt(pow((R+r),2) - pow(r,2)) -R ;
   l->GetPerpendicularAt(cornerPoint,distance_from_start,perp_line);

   MnjPoint<double> arcStartPoint;
   a->GetStartPoint(arcStartPoint);
   MnjDirection startTangent = a->Tangent(arcStartPoint);
   MnjDirection cand_perp_dir = perp_line.GetDirection();
   MnjDirection perp_dir = cand_perp_dir.GetDirectionAlong(startTangent);

   GeomUtils::Translate(ipt_on_line,perp_dir*1, oc);
   return error;
}
///////////////////////////////////////////////////////////////////////////////////////
int MnjSmoother::LineArcArc( 
	std::shared_ptr<MnjSmoothableLine> &l,
	std::shared_ptr<MnjSmoothableArc> &a,
    double &r, 
    MnjPoint<double> &ipt_on_line,
    MnjPoint<double> &ic,
	std::shared_ptr<MnjSmoothableArc> &oarc){
    
    int error = 0;
    
   MnjPoint<double> PC2 ;
   a->GetCenter(PC2);
   MnjInfiniteLine norm_line(PC2,ic);//line connecting candidate arc-center and arc center
   
   shared_ptr_vec_pt pt_vec;
   error = a->Intersect(norm_line,pt_vec);
      
   if(1==pt_vec.size()){
		error = oarc->Set(ipt_on_line,ic,*(pt_vec[0]));
        if(error<0) 
            return error;
        ////

        MnjPoint<double> cornerPoint = l->GetCommonPoint(a,error);
        l->ResetThePoint(cornerPoint,ipt_on_line);
        a->ResetThePoint(cornerPoint,*(pt_vec[0]));
        double angle = oarc->GetAngle();
        if(angle>M_PI)
            oarc->Flip();// startPoint becomes endPoint and vice-versa 
		////
       // break;
	}else if (2==pt_vec.size()){
        double d1 = GeomUtils::GetDistance(ic,*(pt_vec[0]));           		   		   
        double d2 = GeomUtils::GetDistance(ic,*(pt_vec[1]));

        MnjArc tmpArc(ipt_on_line,ic,*(pt_vec[0]));           		   		   
        //double r = l->GetCornerRadius();
        if(fabs(d2-r) < fabs(d1-r))
		   error = tmpArc.Set(ipt_on_line,ic,*(pt_vec[1]));           		   		   

        if(error >= 0){
            //
            MnjPoint<double> otherEnd = tmpArc.GetOtherEnd(ipt_on_line,error);
            MnjPoint<double> cornerPoint = l->GetCommonPoint(a,error);
            l->ResetThePoint(cornerPoint,ipt_on_line);
            a->ResetThePoint(cornerPoint,otherEnd);
            double angle = tmpArc.GetAngle();
            if(angle>M_PI)
              tmpArc.Flip();// startPoint becomes endPoint and vice-versa 
			oarc->SetArc(tmpArc);
		}
	}
    
    return error;
}
