#pragma once

#include <vector>
#include <map>
#include <list>
//#include "MnjSmoothableSegment.h"
//#include "MnjArc.h"
//#include "MnjLine.h"
#include "MnjSmoothableArc.h"
//#include "FlowICSLine.h"
#include "MnjPoint.h" 
#include "MnjDirection.h" 

//#include <boost/shared_ptr.hpp>
//#include <boost/weak_ptr.hpp>
#include "GeomUtils.h"
using namespace std;

//template 
// <typename MnjSmoothableSegment, typename MnjSmoothableArc, typename MnjSmoothableLine>
class __declspec(dllexport)  MnjSmoother{

public:
	
  MnjSmoother(double istep=.01){
		msteps=istep;
	}

  void CreateArcs(vector<shared_ptr<MnjSmoothableSegment>> &isegVec, 
                  vector<shared_ptr<MnjSmoothableSegment>> &osegs,
                   map<unsigned int,int> &oChange);

  void SetStatus(std::list<shared_ptr<MnjSmoothableSegment>> list, 
                 Segment::SegmentChange ch);
private:
  void InsertArc(//vector<boost::shared_ptr<MnjSmoothableSegment>> &segVec, 
			               shared_ptr<MnjSmoothableArc> &arc,
			               vector<shared_ptr<MnjSmoothableSegment>>::iterator it, 
	                   vector<shared_ptr<MnjSmoothableSegment>>::iterator &oit1,
							       vector<shared_ptr<MnjSmoothableSegment>> &ioSegVec);
   

	//line-line case 
	int CreateArc( 
		shared_ptr<MnjSmoothableLine> &seg1,
		shared_ptr<MnjSmoothableLine> &seg2,
		shared_ptr<MnjSmoothableArc> &oarc);

	int CreateArc( 
		shared_ptr<MnjSmoothableLine>  &seg1,
		shared_ptr<MnjSmoothableArc> &seg2,
		shared_ptr<MnjSmoothableArc> &oarc);

	//arc-arc case
	int CreateArc( 
		shared_ptr<MnjSmoothableArc> &seg1,
		shared_ptr<MnjSmoothableArc> &seg2,
		shared_ptr<MnjSmoothableArc> &oarc);

	int CreateArc(  int a ,
	    shared_ptr<MnjSmoothableSegment> &seg1,
	    shared_ptr<MnjSmoothableSegment> &seg2,
	    shared_ptr<MnjSmoothableArc> &oarc);
    
  void SelectNewArcEnd(const MnjPoint<double> &p1,
                       const MnjPoint<double> &pc,
                       const shared_ptr<MnjSmoothableArc> &icsarc,
                       const MnjPoint<double> &p2cand1,
                       const MnjPoint<double> &p2cand2,
								       bool &op2_found,
                       MnjPoint<double> &op2 );

    void Copy(vector<shared_ptr<MnjSmoothableSegment>> &isegVec, 
                        vector<shared_ptr<MnjSmoothableSegment>>  &osegs);

   //void CreateArcs(vector<shared_ptr<MnjSmoothableSegment>> &isegVec, 
   //             vector<shared_ptr<MnjSmoothableSegment>>  &osegs,
   //             map<unsigned int,int> &oChange);

   

   void SelectNewArcEnd( MnjSmoothableArc &a,
	                 const MnjPoint<double> &pcand1,
	                 const MnjPoint<double> &pcand2, 
					       bool &op_found,
						   MnjPoint<double> &op);

  /* int LineArcPointOnLine(MnjLine::shared_ptr&l,
                          shared_ptr<MnjSmoothableArc> &a,
                          double &ir,
                          MnjPoint<double> &opt_on_line);
                          */
   int LineArcCenter(MnjLine::shared_ptr&l,
                  shared_ptr<MnjSmoothableArc> &a,
                  double &ir,
                  const MnjPoint<double> &ipt_on_line,
                  MnjPoint<double> &oc);

   int LineArcArc( 
                MnjLine::shared_ptr&l,
                shared_ptr<MnjSmoothableArc> &a,
                double &ir,
                MnjPoint<double> &ipt_on_line,
                MnjPoint<double> &ic,
                shared_ptr<MnjSmoothableArc> &oarc);

   int CreateArc( shared_ptr<MnjSmoothableArc>  &a,
                  shared_ptr<MnjSmoothableLine> &l,
                  shared_ptr<MnjSmoothableArc>  &oarc);

   int CreateArc( 
	  shared_ptr<MnjSmoothableLine> &l,
	  shared_ptr<MnjSmoothableArc> &a,
	  double &ir,
	  shared_ptr<MnjSmoothableArc> &oarc);
   /*
void Compress( list<shared_ptr<MnjSmoothableSegment>> &l,
               list<shared_ptr<MnjSmoothableSegment>>::iterator it,
               map<unsigned int,int> &oChange,
			   double tol);
               */
/*bool IsCompressible(shared_ptr<MnjSmoothableSegment> &current,
                                  shared_ptr<MnjSmoothableSegment> &next,
                                  double tol, shared_ptr<MnjSmoothableSegment> &oNewT);
                  */
/*
shared_ptr<MnjSmoothableSegment>  Merge(shared_ptr<MnjSmoothableSegment> iSeg1,
                                         shared_ptr<MnjSmoothableSegment> iSeg2);

  */
   int GetCenter(
      shared_ptr<MnjSmoothableLine>&l,
	    shared_ptr<MnjSmoothableArc> &a,
	    double &ir,
	    MnjPoint<double> &ocp);

  int GetFactor(shared_ptr<MnjSmoothableLine>&l,
                shared_ptr<MnjSmoothableArc> &a, 
                                   int &ofactor);

  int GetPerpendicularDirection(shared_ptr<MnjSmoothableLine> &l,
                                shared_ptr<MnjSmoothableArc> &a,
                                                 MnjDirection &oDir) ;

  int GetAPointTowardsArc(shared_ptr<MnjSmoothableLine>&l,
	                                         shared_ptr<MnjSmoothableArc> &a,
                                             MnjPoint<double> &op);

  void IdentifyRedundantCornerRequest(std::list<shared_ptr<MnjSmoothableSegment>> &list);

  void SetStatus(std::list<shared_ptr<MnjSmoothableSegment>> list,
                            MnjSmoothableSegment::SegmentChange ch);

  int LineArcCenter(shared_ptr<MnjSmoothableLine> &l,
	                                 shared_ptr<MnjSmoothableArc> &a,
                                     double &r, 
                                     const MnjPoint<double> &ipt_on_line,
                                     MnjPoint<double> &oc);
  int LineArcArc( 
	       shared_ptr<MnjSmoothableLine> &l,
	       shared_ptr<MnjSmoothableArc> &a,
    double &r, 
    MnjPoint<double> &ipt_on_line,
    MnjPoint<double> &ic,
	shared_ptr<MnjSmoothableArc> &oarc);
  double msteps;
};