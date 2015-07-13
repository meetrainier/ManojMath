 
/*
5/31/2012 : manoj : Added new class CompressPrior,CompressNext 

*/
#include <memory> 
#include "MnjBiDirectionalMerge.h"
#include "MnjSmoother.h"
#include "MnjDirection.h"
#include <cmath>
using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////
void MnjBiDirectionalMerge::CompressNonRecursive( list<shared_ptr<MnjSmoothableSegment>> &l,
			                                            list<shared_ptr<MnjSmoothableSegment>>::iterator it,
                                                  map<unsigned int,int> &oChange,
							                                    double tol){

     CompressNext N(l);
     CompressPrior P(l);

     while( !(N.CompressNext::num > N.max_iter) ){
        
      bool compressed = false;

      decltype(it) it0=it;
      shared_ptr<MnjSmoothableSegment> newSegmentPair;
            
			if(!N.ReturnableNext(l,it) && 
                N.IsNextCompressible(l,it,tol,newSegmentPair)){
                decltype(it) it01 = NextIter(l,it0);    
                decltype(it01) it02 = NextIter(l,it01);
				
        l.erase(it01);
				decltype(it) it1 = l.erase(it02);
				decltype(it) it2 = l.insert(it1,newSegmentPair);
				N.CompressNext::num++;
				//cout << endl << "iteration:equal  " << num << endl;
				//PrintList(l);		    
				//CompressN(l,it0,oChange,tol);
                compressed = true;
			}
      
      if( !P.ReturnablePrev(l,it) && 
           P.IsPriorCompressible(l,it0,tol,newSegmentPair)){

        decltype(it0) prevIT=PrevIter(l,it0);
         //prevIT--;
        l.erase(prevIT);
	      decltype(it) it1 = l.erase(it0);
	      decltype(it) it2 = l.insert(it1,newSegmentPair);
        it=it2;
        compressed = true;
      }
			
      N.CompressNext::num++;
				//cout << endl << "iteration: " << num << endl;
				//PrintList(l);
      if(!compressed){
		      it = NextIter(l,it);//
      }

     };      

}
///////////////////////////////////////////////////////////
bool CompressPrior::IsPriorCompressible(list<std::shared_ptr<MnjSmoothableSegment>> &l,
                                             list<std::shared_ptr<MnjSmoothableSegment>>::iterator it,
                                             double tol, //useless for now: remove? Manoj 5/15/2012
											 std::shared_ptr<MnjSmoothableSegment> &oNewT
                                             ){
    bool flag = false;
    decltype(it) nextIT= NextIter(l,it); //nextIT++;
	std::shared_ptr<MnjSmoothableSegment> current = *it;

    bool tangent = current->IsTangent(*nextIT);

     //if( current->IsCorner() && current->IsPrevRelevant() ){
	 if( current->IsCorner() && !tangent ){
        
        decltype(it) prevIT= PrevIter(l,it); //prevIT--;
        //decltype(it) nextIT= NextIter(l,it); //nextIT++;
        int error = 0;

       if(IsMergeable(current,*nextIT,MnjSmoothableSegment::PREV_PROCESSED,error) && error >= 0 ){
        //if ( currentLength < minimumLength ) {
			oNewT = Merge(current,*prevIT);//tbd: catch error: retun false in that case
			flag = true;
            if(!oNewT){
                flag = false;
            }
        }else{
                (*it)->SetProcessingState(MnjSmoothableSegment::PREV_PROCESSED);
             }

	}
	return flag;
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool CompressNext::IsNextCompressible(list<std::shared_ptr<MnjSmoothableSegment>> &l,
                                             list<std::shared_ptr<MnjSmoothableSegment>>::iterator it,
                                             double tol, //useless for now: remove? Manoj 5/15/2012
                                             std::shared_ptr<MnjSmoothableSegment> &oNewT
                                             ){
    bool flag = false;
    std::shared_ptr<MnjSmoothableSegment> current =  *it;
    decltype(it) nextIT = NextIter(l,it);
    bool tangent = current->IsTangent(*nextIT);
	
    if( current->IsCorner() && !tangent){
        
        //decltype(it) nextIT = NextIter(l,it); //nextIT++; if(nextIT==l.end()) {nextIT = ++(l.begin());} 
        int error = 0;
        decltype(it) nextNextIT= NextIter(l,nextIT); 
        /*
        double angle = GetAngle(current,*nextIT,error);
        //double angle = GetAngle(*nextIT,*nextNextIT,error);
        if(error<0) {
            return false;
        }
        double r = current->GetCornerRadius();
        double nextLength = (*nextIT)->GetCharacteristic();
        //double sum = val2 + val3 ;
        double minimumLength = r/tan(angle/2);
        */

		//if(nextLength < minimumLength ) {
         if(IsMergeable(current,*nextIT,MnjSmoothableSegment::NEXT_PROCESSED,error) && error >= 0) {
            //decltype(it) nextNextIT= NextIter(l,nextIT); //nextNextIT++;
			oNewT = Merge(*nextIT,*nextNextIT);//tbd: catch error: return false in that case
                                                //tbd:ensure that the function returns FALSE, when the error 
                                                //    because of Merge is tool large. (because of angle between (*nextIT,*nextNextIT) 
           // double ch = oNewT->GetCharacteristic();   
			flag = true;
            }else{
                (*it)->SetProcessingState(MnjSmoothableSegment::NEXT_PROCESSED);
             }
    }
	return flag;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//working with all test cases:
std::shared_ptr<MnjSmoothableSegment>  MnjBiDirectionalMerge::Merge(std::shared_ptr<MnjSmoothableSegment> iSeg1,
                                                                      std::shared_ptr<MnjSmoothableSegment> iSeg2){
  int error = 0;
  if(iSeg1 && iSeg2 ) {
      /*
        ICSAttribute attr;
        vector< boost::shared_ptr<MnjSmoothableSegment> > icsSegVec;
	    icsSegVec.push_back(iSeg1);
	    icsSegVec.push_back(iSeg2);
        FlowSmoother s;
	    s.GetAttributeWithLowestValues(icsSegVec,attr);
        */
      std::shared_ptr<MnjSmoothableArc> arc1 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (iSeg1);
      MnjSmoothableLine::shared_ptr line1 = std::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (iSeg1);
      std::shared_ptr<MnjSmoothableArc> arc2 = std::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (iSeg2);
      MnjSmoothableLine::shared_ptr line2 = std::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (iSeg2);
	   
      std::shared_ptr<MnjSmoothableSegment> retICSSegment;
      
      try {
       if(line1 && line2){

        //return boost::shared_ptr<MnjSmoothableLine>(new MnjSmoothableLine(line1,line2,MnjSmoothableSegment::MERGED) );
		   retICSSegment = std::shared_ptr<MnjSmoothableLine>(new MnjSmoothableLine(line1, line2, MnjSmoothableSegment::MERGED));
       
       }else if(line1 && arc2){//tbd
	     
        //return boost::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(line1,arc2,MnjSmoothableSegment::MERGED) );
		   retICSSegment = std::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(line1, arc2, MnjSmoothableSegment::MERGED));
	     
       } else if(arc1 && line2){//tbd
       
        //return boost::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(arc1,line2,MnjSmoothableSegment::MERGED) );
		   retICSSegment = std::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(arc1, line2, MnjSmoothableSegment::MERGED));
       
       }else if(arc1 && arc2){//tbd
        
        //return boost::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(arc1,arc2,MnjSmoothableSegment::MERGED) );
		   retICSSegment = std::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(arc1, arc2, MnjSmoothableSegment::MERGED));
       }
     }
     catch (std::exception e){
           throw e;
         //mnj return boost::shared_ptr<MnjSmoothableLine>((MnjSmoothableLine *)NULL);
      }
     return retICSSegment;
    }
  return std::shared_ptr<MnjSmoothableLine>((MnjSmoothableLine *)NULL);

}
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
working with all test cases:
boost::shared_ptr<MnjSmoothableSegment>  MnjBiDirectionalMerge::Merge(boost::shared_ptr<MnjSmoothableSegment> iSeg1,
                                                       boost::shared_ptr<MnjSmoothableSegment> iSeg2){
  int error = 0;
  if(iSeg1 && iSeg2 ) {
        ICSAttribute attr;
        vector< boost::shared_ptr<MnjSmoothableSegment> > icsSegVec;
	    icsSegVec.push_back(iSeg1);
	    icsSegVec.push_back(iSeg2);
        FlowSmoother s;
	    s.GetAttributeWithLowestValues(icsSegVec,attr);

        boost::shared_ptr<MnjSmoothableArc> arc1 = boost::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (iSeg1);
        MnjSmoothableLine::shared_ptrline1 = boost::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (iSeg1);
        boost::shared_ptr<MnjSmoothableArc> arc2 = boost::dynamic_pointer_cast<MnjSmoothableArc,MnjSmoothableSegment> (iSeg2);
        MnjSmoothableLine::shared_ptrline2 = boost::dynamic_pointer_cast<MnjSmoothableLine,MnjSmoothableSegment> (iSeg2);
	
       if(line1 && line2){
           return boost::shared_ptr<MnjSmoothableLine>(new MnjSmoothableLine(line1,line2,attr,MnjSmoothableSegment::MERGED) );
       }
    
    else if(line1 && arc2){//tbd
	     return boost::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(line1,arc2,attr,MnjSmoothableSegment::MERGED) );
	}
	
    else if(arc1 && line2){//tbd
      return boost::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(arc1,line2,attr,MnjSmoothableSegment::MERGED) );
	}
    else if(arc1 && arc2){//tbd
      return boost::shared_ptr<MnjSmoothableArc>(new MnjSmoothableArc(arc1,arc2,attr,MnjSmoothableSegment::MERGED) );
     }
     
    
    }
    return boost::shared_ptr<MnjSmoothableLine>((MnjSmoothableLine *)NULL);

}
*/
///////////////////////////////////////////////////////////////////////////////////////////////
/*
void CompressPrior::CompressP( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
			                            list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                                        map<unsigned int,int> &oChange,
							               double tol){
	

	if(ReturnablePrev(l,it) || num > max_iter){
                return;
     }
			
    decltype(it) it0=it;
	decltype(it) it1;
	decltype(it) it2;
	decltype(it) it01 = NextIter(l,it0);
	//it01++;
	//if ( it01 == l.end() ) 
        //   return;
	boost::shared_ptr<MnjSmoothableSegment> newSegmentPair;//(new MnjSmoothableSegment());

	decltype(it01) it02 = NextIter(l,it01);
	//it02++; 
	//boost::shared_ptr<MnjSmoothableSegment> seg3;

	//if(it02 == l.end() ){ 
		//	return ; 
	//}else{
	//	seg3 = *it02;
			//}
			

//mnj	if( it0 != l.begin() &&  IsPriorCompressible(l,it0,tol,newSegmentPair)){
	if(  IsPriorCompressible(l,it0,tol,newSegmentPair)){

    decltype(it0) prevIT=PrevIter(l,it0);
    //prevIT--;
    l.erase(prevIT);
	it1 = l.erase(it0);
	it2 = l.insert(it1,newSegmentPair);
	//if(it2 == l.end() || !seg3) {
	//	return;
	//}
	//else{
		num++;
		//cout << endl << "iteration:equal  " << num << endl;
		//PrintList(l);		    
		CompressP(l,it2,oChange,tol);
	//}
  }
  else {
	num++;
	//cout << endl << "iteration: " << num << endl;
	//PrintList(l);
	it=NextIter(l,it);//it++
	CompressP(l,it,oChange,tol);
    }
	       
}
*/
///////////////////////////////////////////////////////////////////////////////////////////
bool CompressNext::ReturnableNext(list<std::shared_ptr<MnjSmoothableSegment>> &l,
	list<std::shared_ptr<MnjSmoothableSegment>>::iterator it){
     bool flag = false;
     if(l.end()==it) 
         return true;//should not normally come here
     if(MnjSmoothableSegment::NEXT_PROCESSED == (*it)->GetProcessingState())
               return true;

	 list<std::shared_ptr<MnjSmoothableSegment>>::iterator it1 = NextIter(l, it);
     if(MnjSmoothableSegment::NEXT_PROCESSED == (*it1)->GetProcessingState())
               return true;

	 list<std::shared_ptr<MnjSmoothableSegment>>::iterator it2 = NextIter(l, it1);
     if(MnjSmoothableSegment::NEXT_PROCESSED == (*it2)->GetProcessingState())
               return true;
     
     return flag;
 }
 /////////////////////////////////////////////////////////////////////////////////////////
bool CompressPrior::ReturnablePrev(list<std::shared_ptr<MnjSmoothableSegment>> &l,
	list<std::shared_ptr<MnjSmoothableSegment>>::iterator it){
     int s1 = l.size();
     bool flag = false;
     if(l.end()==it) 
         return true;//should not normally come here
     if(MnjSmoothableSegment::PREV_PROCESSED == (*it)->GetProcessingState())
               return true;

     list<std::shared_ptr<MnjSmoothableSegment>>::iterator it1 = NextIter(l,it);
     if(MnjSmoothableSegment::PREV_PROCESSED == (*it1)->GetProcessingState())
               return true;

     //list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it2 = NextIter(l,it1);
     //if(MnjSmoothableSegment::PREV_PROCESSED == (*it2)->GetProcessingState())
       //        return true;
     
     return flag;
 }
 ///////////////////////////////////////////////////////////////////////////////////////////
list<std::shared_ptr<MnjSmoothableSegment>>::iterator
MnjBiDirectionalMerge::NextIter(list<std::shared_ptr<MnjSmoothableSegment>> &l,
                              list<std::shared_ptr<MnjSmoothableSegment>>::iterator it){        
       if(l.end() == it) 
           return it = l.begin();
       
       it++;
       
       if(l.end() == it) 
           return it = l.begin();
       else 
           return it;
 }
 ///////////////////////////////////////////////////////////////////////////////////////////
 list<std::shared_ptr<MnjSmoothableSegment>>::iterator 
 MnjBiDirectionalMerge::PrevIter(list<std::shared_ptr<MnjSmoothableSegment>> &l,
                              list<std::shared_ptr<MnjSmoothableSegment>>::iterator it){        
       if(l.begin() == it) 
           it = l.end();
       it--;
       return it;
 }
 //////////////////////////////////////////////////////////////////////////////////////////
 /*
void CompressNext::CompressN( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
			                 list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                             map<unsigned int,int> &oChange,
							 double tol){

     if(ReturnableNext(l,it) || CompressNext::num > max_iter){
                return;
     }
            static unsigned int current_index = 0;
            static int count =0;

            decltype(it) it0=it;
			decltype(it) it1;
			decltype(it) it2;
			decltype(it) it01 = NextIter(l,it0);
			//it01++;
			//if ( it01 == l.end() ) 
             //   return;
			boost::shared_ptr<MnjSmoothableSegment> newSegmentPair;//(new MnjSmoothableSegment());

			decltype(it01) it02 = NextIter(l,it01);

			if(IsNextCompressible(l,it0,tol,newSegmentPair)){

				l.erase(it01);
				it1 = l.erase(it02);
				it2 = l.insert(it1,newSegmentPair);
				CompressNext::num++;
				//cout << endl << "iteration:equal  " << num << endl;
				//PrintList(l);		    
				CompressN(l,it0,oChange,tol);
			}
			else {
				
                CompressNext::num++;
				//cout << endl << "iteration: " << num << endl;
				//PrintList(l);
				it = NextIter(l,it);//it++;
                current_index++;
				CompressN(l,it,oChange,tol);
			}
	       
}
*/
///////////////////////////////////////////////////////////////////////////////////////////
//list based implementaion of compress 
/*void MnjBiDirectionalMerge::Compress( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
			                 list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                             map<unsigned int,int> &oChange,
							 double tol){
	
	       CompressNext N(l);
           N.CompressN(l,it,oChange,tol);
          
	       CompressPrior P(l);
           std::list<boost::shared_ptr<MnjSmoothableSegment>>::iterator itB=l.begin();
           P.CompressP(l,itB,oChange,tol);
}
*/
//////////////////////////////////////////////////////////////////////////////////////
double MnjBiDirectionalMerge::GetAngle(std::shared_ptr<MnjSmoothableSegment> iSeg1,
                                       std::shared_ptr<MnjSmoothableSegment> iSeg2, int &oerror){
  //int error = 0;
  //TBD: Make sure that get Angle serves the purpose for Arc-line and arc-arc corners.
  //FlowPoint<double> commonPoint = SegmentCommonPoint(iSeg1,iSeg2,oerror);
  dbl_3d_pt commonPoint = iSeg1->GetCommonPoint(iSeg2,oerror);
  double angle = -9999;
  if(oerror>=0){
      dbl_3d_pt p1 = iSeg1->GetOtherEnd(commonPoint,oerror);
      if(oerror>=0){
          dbl_3d_pt p2 = iSeg2->GetOtherEnd(commonPoint,oerror);
          MnjDirection dir1(commonPoint,p1); 
          MnjDirection dir2(commonPoint,p2); 
          angle = dir1.Angle(dir2);
          if(angle>M_PI){ 
              angle =  2*M_PI - angle;
          }
      }
   }
  return angle;
}
//////////////////////////////////////////////////////////////////////////////////////////
bool MnjBiDirectionalMerge::IsMergeable(std::shared_ptr<MnjSmoothableSegment> iSeg1,
                                     std::shared_ptr<MnjSmoothableSegment> iSeg2, 
                                     MnjSmoothableSegment::ProcessingState iState,
                                     int &oerror){
    if( !iSeg1 || !iSeg2)
        return false;

    double r =  iSeg1->GetCornerRadius();
    std::shared_ptr<Segment> seg1 = iSeg1->GetSegment(); 
    std::shared_ptr<Segment> seg2 = iSeg2->GetSegment(); 
    std::shared_ptr<MnjArc>  arc(new MnjArc());
    oerror = GeomUtils::CreateArc(seg1,seg2,r,arc);
    
    if(arc && oerror<0) {
        oerror = 0; 
        return true;
    }
    else{
      /*  if(iState!=iSeg1->GetProcessingState()){
           iSeg1->SetProcessingState(iState);
          oerror = 0; 
          return true;
        }
        */
        return false;
    }
}
/*
bool MnjBiDirectionalMerge::IsCompressible(list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                                  //boost::shared_ptr<MnjSmoothableSegment> &next,
                                  double tol, boost::shared_ptr<MnjSmoothableSegment> &oNewT, bool &opriorSegMerged){
    bool flag = false;
    boost::shared_ptr<MnjSmoothableSegment> current =  *it;
	if( current->IsCorner() ){

		double mergeParam = current->GetMergeParameter();
		double val2 = current->GetCharacteristic();
        decltype(it) nextIT=it; nextIT++;
        double val3 = (*nextIT)->GetCharacteristic();
        double sum = val2 + val3 ;
		if(sum < mergeParam) {
			oNewT = Merge(current,*nextIT);//tbd: catch error: retun false in that case
			flag = true;
            double newCharacteritsic = oNewT->GetCharacteristic();
            if(newCharacteritsic<mergeParam){ //if needed merge prior element {
                decltype(it) priorIT= it; 
                priorIT--;
                oNewT = Merge(oNewT,*priorIT);
                opriorSegMerged = true;
            }
		}

	}
	return flag;
}
*/


