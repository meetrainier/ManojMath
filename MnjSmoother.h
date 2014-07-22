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

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "GeomUtils.h"
using namespace boost;

//template 
// <typename MnjSmoothableSegment, typename MnjSmoothableArc, typename MnjSmoothableLine>
class __declspec(dllexport)  MnjSmoother{

public:
	
  MnjSmoother(double istep=.01){
		msteps=istep;
	}

  void CreateArcs(vector<boost::shared_ptr<MnjSmoothableSegment>> &isegVec, 
                  vector<boost::shared_ptr<MnjSmoothableSegment>> &osegs,
                   map<unsigned int,int> &oChange);

  void SetStatus(std::list<boost::shared_ptr<MnjSmoothableSegment>> list, 
                 Segment::SegmentChange ch);
private:
  void InsertArc(//vector<boost::shared_ptr<MnjSmoothableSegment>> &segVec, 
			               boost::shared_ptr<MnjSmoothableArc> &arc,
			               vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator it, 
	                   vector<boost::shared_ptr<MnjSmoothableSegment>>::iterator &oit1,
							       vector<boost::shared_ptr<MnjSmoothableSegment>> &ioSegVec);
   

	//line-line case 
	int CreateArc( 
		boost::shared_ptr<MnjSmoothableLine> &seg1,
		boost::shared_ptr<MnjSmoothableLine> &seg2,
		boost::shared_ptr<MnjSmoothableArc> &oarc);

	int CreateArc( 
		boost::shared_ptr<MnjSmoothableLine>  &seg1,
		boost::shared_ptr<MnjSmoothableArc> &seg2,
		boost::shared_ptr<MnjSmoothableArc> &oarc);

	//arc-arc case
	int CreateArc( 
		boost::shared_ptr<MnjSmoothableArc> &seg1,
		boost::shared_ptr<MnjSmoothableArc> &seg2,
		boost::shared_ptr<MnjSmoothableArc> &oarc);

	int CreateArc(  int a ,
	    boost::shared_ptr<MnjSmoothableSegment> &seg1,
	    boost::shared_ptr<MnjSmoothableSegment> &seg2,
	    boost::shared_ptr<MnjSmoothableArc> &oarc);
    
  void SelectNewArcEnd(const MnjPoint<double> &p1,
                       const MnjPoint<double> &pc,
                       const boost::shared_ptr<MnjSmoothableArc> &icsarc,
                       const MnjPoint<double> &p2cand1,
                       const MnjPoint<double> &p2cand2,
								       bool &op2_found,
                       MnjPoint<double> &op2 );

    void Copy(vector<boost::shared_ptr<MnjSmoothableSegment>> &isegVec, 
                        vector<boost::shared_ptr<MnjSmoothableSegment>>  &osegs);

   //void CreateArcs(vector<boost::shared_ptr<MnjSmoothableSegment>> &isegVec, 
   //             vector<boost::shared_ptr<MnjSmoothableSegment>>  &osegs,
   //             map<unsigned int,int> &oChange);

   

   void SelectNewArcEnd( MnjSmoothableArc &a,
	                 const MnjPoint<double> &pcand1,
	                 const MnjPoint<double> &pcand2, 
					       bool &op_found,
						   MnjPoint<double> &op);

  /* int LineArcPointOnLine(MnjLine::shared_ptr&l,
                          boost::shared_ptr<MnjSmoothableArc> &a,
                          double &ir,
                          MnjPoint<double> &opt_on_line);
                          */
   int LineArcCenter(MnjLine::shared_ptr&l,
                  boost::shared_ptr<MnjSmoothableArc> &a,
                  double &ir,
                  const MnjPoint<double> &ipt_on_line,
                  MnjPoint<double> &oc);

   int LineArcArc( 
                MnjLine::shared_ptr&l,
                boost::shared_ptr<MnjSmoothableArc> &a,
                double &ir,
                MnjPoint<double> &ipt_on_line,
                MnjPoint<double> &ic,
                boost::shared_ptr<MnjSmoothableArc> &oarc);

   int CreateArc( boost::shared_ptr<MnjSmoothableArc>  &a,
                  boost::shared_ptr<MnjSmoothableLine> &l,
                  boost::shared_ptr<MnjSmoothableArc>  &oarc);

   int CreateArc( 
	  boost::shared_ptr<MnjSmoothableLine> &l,
	  boost::shared_ptr<MnjSmoothableArc> &a,
	  double &ir,
	  boost::shared_ptr<MnjSmoothableArc> &oarc);
   /*
void Compress( list<boost::shared_ptr<MnjSmoothableSegment>> &l,
               list<boost::shared_ptr<MnjSmoothableSegment>>::iterator it,
               map<unsigned int,int> &oChange,
			   double tol);
               */
/*bool IsCompressible(boost::shared_ptr<MnjSmoothableSegment> &current,
                                  boost::shared_ptr<MnjSmoothableSegment> &next,
                                  double tol, boost::shared_ptr<MnjSmoothableSegment> &oNewT);
                  */
/*
boost::shared_ptr<MnjSmoothableSegment>  Merge(boost::shared_ptr<MnjSmoothableSegment> iSeg1,
                                         boost::shared_ptr<MnjSmoothableSegment> iSeg2);

  */
   int GetCenter(
      boost::shared_ptr<MnjSmoothableLine>&l,
	    boost::shared_ptr<MnjSmoothableArc> &a,
	    double &ir,
	    MnjPoint<double> &ocp);

  int GetFactor(boost::shared_ptr<MnjSmoothableLine>&l,
                boost::shared_ptr<MnjSmoothableArc> &a, 
                                   int &ofactor);

  int GetPerpendicularDirection(boost::shared_ptr<MnjSmoothableLine> &l,
                                boost::shared_ptr<MnjSmoothableArc> &a,
                                                 MnjDirection &oDir) ;

  int GetAPointTowardsArc(boost::shared_ptr<MnjSmoothableLine>&l,
	                                         boost::shared_ptr<MnjSmoothableArc> &a,
                                             MnjPoint<double> &op);

  void IdentifyRedundantCornerRequest(std::list<boost::shared_ptr<MnjSmoothableSegment>> &list);

  void SetStatus(std::list<boost::shared_ptr<MnjSmoothableSegment>> list,
                            MnjSmoothableSegment::SegmentChange ch);

  int LineArcCenter(boost::shared_ptr<MnjSmoothableLine> &l,
	                                 boost::shared_ptr<MnjSmoothableArc> &a,
                                     double &r, 
                                     const MnjPoint<double> &ipt_on_line,
                                     MnjPoint<double> &oc);
  int LineArcArc( 
	       boost::shared_ptr<MnjSmoothableLine> &l,
	       boost::shared_ptr<MnjSmoothableArc> &a,
    double &r, 
    MnjPoint<double> &ipt_on_line,
    MnjPoint<double> &ic,
	boost::shared_ptr<MnjSmoothableArc> &oarc);
  double msteps;
};