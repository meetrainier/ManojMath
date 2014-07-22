#pragma once
#include <list>
#include <map>
#include <boost\shared_ptr.hpp>

#include "MnjSmoothableSegment.h"


///////////////////////////////////////////////////////////////////////////////
class MnjBiDirectionalMerge{
public:
    void CompressNonRecursive( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
			                         list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                               map<unsigned int,int> &oChange,
							                 double tol);
    /*
   void Compress( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
			                 list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                             map<unsigned int,int> &oChange,
							 double tol);
    */
   bool IsMergeable(boost::shared_ptr<MnjSmoothableSegment> iSeg1,
                    boost::shared_ptr<MnjSmoothableSegment> iSeg2, 
                    MnjSmoothableSegment::ProcessingState iState,
                       int &oerror);

protected:
  //bool Returnable(list<boost::shared_ptr<MnjSmoothableSegment>> &l,
    //              list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it);
  
  list<boost::shared_ptr<MnjSmoothableSegment>>::iterator 
  NextIter(list<boost::shared_ptr<MnjSmoothableSegment>> &l,
                              list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it);
  
  list<boost::shared_ptr<MnjSmoothableSegment>>::iterator 
  PrevIter(list<boost::shared_ptr<MnjSmoothableSegment>> &l,
                              list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it);

  
  
  boost::shared_ptr<MnjSmoothableSegment>  Merge(boost::shared_ptr<MnjSmoothableSegment> iSeg1,
                                           boost::shared_ptr<MnjSmoothableSegment> iSeg2);
  
  double GetAngle(boost::shared_ptr<MnjSmoothableSegment> iSeg1,
                  boost::shared_ptr<MnjSmoothableSegment> iSeg2,
                  int &error);

};
////////////////////////////////////////////////////////////////////////
class CompressPrior: public MnjBiDirectionalMerge {
public:
        //constructor
        CompressPrior(list<boost::shared_ptr<MnjSmoothableSegment>> &l):morginal_list_size(l.size()){num=0;max_iter=2*morginal_list_size;}
        //main method 
        /*
        void CompressP( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
			                 list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                             map<unsigned int,int> &oChange,
							 double tol);
         */
        bool ReturnablePrev(list<boost::shared_ptr<MnjSmoothableSegment>> &l,
                            list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it);

        bool IsPriorCompressible(list<boost::shared_ptr<MnjSmoothableSegment>> &l,
                           list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                           double tol, 
                           boost::shared_ptr<MnjSmoothableSegment> &oNewT);

    //unsigned int GetOrginalListSize(void){ return morginal_list_size ;}
     //bool IsPriorMergeable(boost::shared_ptr<MnjSmoothableSegment> iSeg1,boost::shared_ptr<MnjSmoothableSegment> iSeg2, int &oerror);
//private:
    unsigned int morginal_list_size;
    unsigned int max_iter;// morginal_list_size*(1 + 1/2 + 1/4 + 1/8........=2.0) 
    unsigned int num ;
};
///////////////////////////////////////////////////////////////////////////////
class CompressNext: public MnjBiDirectionalMerge {
public:

        //constructor
        CompressNext(list<boost::shared_ptr<MnjSmoothableSegment>> &l):morginal_list_size(l.size()){num=0;max_iter=2*morginal_list_size;}
        //main method 
        //void CompressN( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
			   //              list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
           //                  map<unsigned int,int> &oChange,
					//		 double tol);
public:
        bool ReturnableNext(list<boost::shared_ptr<MnjSmoothableSegment>> &l,
                            list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it);

        bool IsNextCompressible(list<boost::shared_ptr<MnjSmoothableSegment>> &l,
                           list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
                           double tol, 
                           boost::shared_ptr<MnjSmoothableSegment> &oNewT);

    //unsigned int GetOrginalListSize(void){ return morginal_list_size ;}
    //bool IsNextMergeable(boost::shared_ptr<MnjSmoothableSegment> iSeg1,boost::shared_ptr<MnjSmoothableSegment> iSeg2, int &oerror);
//private:
    unsigned int morginal_list_size;//useless for alogo. useful for debugging. 
                                    //Just used in calculation of max_iter that is done in constructor only. 
    unsigned int max_iter;// morginal_list_size*(1 + 1/2 + 1/4 + 1/8........=2.0) 
    unsigned int num ;
};