/**
7/13/2012 Added error messaging in constructors and set

*/
#include <exception>
#include <typeinfo> 

#include "ErrorUtils.h"
#include "Segment.h"
#include "MnjArc.h"
#include "MnjPoint.h"
#include "GeomUtils.h"
#include "MnjCircle.h"
using namespace std;

MnjArc::MnjArc(shared_ptr &iSeg1, shared_ptr& iSeg2){
  
  //TestMnjSmoother test;
  
  int error = 0;
  MnjPoint<double> commonPoint = iSeg1->GetCommonPoint(iSeg2,error);
  
  if(error>=0){
	  
	  //MessageBox(NULL,"Not error1",__FUNCTION__,MB_OK);
      MnjPoint<double> p1 = iSeg1->GetOtherEnd(commonPoint,error);
      if(error>=0){
		  
		  //MessageBox(NULL,"Not error2",__FUNCTION__,MB_OK);
          MnjPoint<double> p2 = iSeg2->GetOtherEnd(commonPoint,error);
          //test.NewDisplay(p2,__FUNCTION__);//tbd

          if(error>=0){
              //MessageBox(NULL,"Not error3",__FUNCTION__,MB_OK);
              //calculate center
              MnjInfiniteLine bisector ;
              MnjLine(p1,p2).GetPerpendicularBisector(bisector);
              MnjInfiniteLine normal(p2,iSeg2->GetCenter()); 
              MnjPoint<double> cp;
              error = bisector.Intersect(normal,cp);
               
              //test.NewDisplay(bisector,__FUNCTION__);//tbd
			  //test.NewDisplay(normal,"normal");//tbd
              //char str[100];
			  //MessageBox(NULL,_itoa(error,str,10),__FUNCTION__,MB_OK);

			  //create arc 
              if(error>=0){

                  //MessageBox(NULL,"Not error4",__FUNCTION__,MB_OK);

                  MnjDirection stdTangent = iSeg2->TangentAtEnd(p2);
                  error = Set(p1,cp,p2);//set must be called before tangent of this is calculated 
                  if(error>=0){
                      MnjDirection currentTangent = TangentAtEnd(p2);

                      //If needed flip arc. Thus make sure that arc is formed on the correct side
                      if(stdTangent.DotProduct(currentTangent)<0) 
                         Flip();
                      /*{   
                          //debug code
                          double a1 = iSeg1->GetAngle();
                          double a2 = iSeg2->GetAngle();
                          double a = GetAngle();
                          //
                          double l1 = iSeg1->GetLength();
                          double l2 = iSeg2->GetLength();
                          double l = GetLength();
                          int aaaa =0;
                      }*/
                  }
              }
          }
      }
  }

  if(error<0){
   //std::exception()
   string s;
   //throw std::exception("Invalid Geometry Input for Arc");
   string msg("Invalid Geometry Input for Arc");
   Mnj::ErrorUtils::CreateErrorString(__FILE__, __LINE__,__FUNCTION__, msg,s);
   throw std::exception(s.c_str());
  }
}
//------------------------------------------------------------------------------
/*
void MnjArc::CreateErrorString(char *file, int line_no,char *func, string &imsg,std::string &s) {
 s.append("File: ");
 s.append(file);
 char buffer[100];
 itoa(line_no,buffer,10);
 s.append("\tLine: ");
 s.append(buffer);
 s.append("\tMethod: ");
 s.append(func);
 s.append("\tMessage: ");
 s.append(imsg);
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
MnjArc::MnjArc(boost::shared_ptr<MnjLine> &iSeg1, shared_ptr& iSeg2){
  int error = 0;
  MnjPoint<double> commonPoint = iSeg1->GetCommonPoint(iSeg2,error);
  if(error>=0){
      MnjPoint<double> p1 = iSeg1->GetOtherEnd(commonPoint,error);
      if(error>=0){
          MnjPoint<double> p2 = iSeg2->GetOtherEnd(commonPoint,error);
          
          if(error>=0){
          
              //calculate center
              MnjInfiniteLine bisector ;
              MnjLine(p1,p2).GetPerpendicularBisector(bisector);
              MnjInfiniteLine normal(p2,iSeg2->GetCenter()); 
              MnjPoint<double> cp;
              error = bisector.Intersect(normal,cp);
             
              //reate arc 
              MnjDirection stdTangent = iSeg2->Tangent(p2);
              Set(p1,cp,p2);//set must be called before tangent of this is calculated 
              MnjDirection currentTangent = Tangent(p2);

              //In needed flip arc. Thus make sure that arc is formed on the correct side
              if(stdTangent.DotProduct(currentTangent)<0) 
                  Flip();
          }
      }
  }
   if(error<0){
   //std::exception()
   string s;
   //throw std::exception("Invalid Geometry Input for Arc");
   string msg("Invalid Geometry Input for Arc");
   Mnj::ErrorUtils::CreateErrorString(__FILE__, __LINE__,__FUNCTION__, msg,s);
   throw std::exception(s.c_str());
  }
}
/////////////////////////////////////////////////////
MnjArc::MnjArc(shared_ptr &iSeg1, MnjLine::shared_ptr& iSeg2){

  int error = 0;
  MnjPoint<double> commonPoint = iSeg1->GetCommonPoint(iSeg2,error);
  
  if(error>=0){

      MnjPoint<double> p1 = iSeg1->GetOtherEnd(commonPoint,error);
      
      if(error>=0){
      
          MnjPoint<double> p2 = iSeg2->GetOtherEnd(commonPoint,error);
          
          if(error>=0){
          
              MnjInfiniteLine bisector;
              MnjLine(p1,p2).GetPerpendicularBisector(bisector);
              
              //Calculate center
              MnjInfiniteLine normal = iSeg2->Normal(p2,p1,error); 
              MnjPoint<double> cp;
              error = bisector.Intersect(normal,cp);
             
              //Create arc 
              MnjDirection stdTangent = iSeg2->Tangent();
              Set(p1,cp,p2);//set must be called before tangent of this is calculated 
              MnjDirection currentTangent = Tangent(p2);

              //In needed flip arc. Thus make sure that arc is formed on the correct side
              if(stdTangent.DotProduct(currentTangent)<0) 
                  Flip();
          }
      }
  }

   if(error<0){
   //std::exception()
   string s;
   //throw std::exception("Invalid Geometry Input for Arc");
   string msg("Invalid Geometry Input for Arc");
   Mnj::ErrorUtils::CreateErrorString(__FILE__, __LINE__,__FUNCTION__, msg,s);
   throw std::exception(s.c_str());
  }
}
//--------------------------------------------------------------------
MnjArc::MnjArc(const MnjPoint<double> &ip1, 
               const MnjPoint<double> &center, 
               const MnjPoint<double> &ip2){

  double d1 = GeomUtils::GetDistance(ip1,center) ;
  double d2 = GeomUtils::GetDistance(ip2,center) ;
 
  if( fabs(d1-d2) > .001 ){
    string msg = "Start and End Point at different distance from center.";
    string s;
    Mnj::ErrorUtils::CreateErrorString(__FILE__, __LINE__,__FUNCTION__, msg,s);
    throw std::exception(s.c_str());
  }
	
  startPoint  = ip1;
	centerPoint = center;
	endPoint    = ip2;

}

void MnjArc::GetStartPoint(MnjPoint<double> &op)const{
	op = startPoint;
}

void MnjArc::GetCenter(MnjPoint<double> &oc){
	oc = centerPoint;
}
/////////////////////////////////////////////////////////////
void MnjArc::GetEndPoint(MnjPoint<double> &op)const{
	op = endPoint;
}
/*
//Tbd: If it ise used. convert to smaprt pointer later and uncomment.  

MnjArc::Arc(Segment &iSeg1, Segment &iSeg2){
	MnjPoint<double> startPoint;
	iSeg1.GetStartPoint(startPoint);
	SetStartPoint(startPoint);

	//tbd:1.Set center
	//    1.1get normal at the two points, the intersection of the normals is the center.
	//    1.1.1 Method to get normal to a line at the 
	//    1.1.1 Method to get inersection of two lines. 
	//for now just use center point of the 1st segment
	MnjPoint<double> cp;
	{
	  SegmentType::ARC == iSeg1.GetType();
      Arc *arc = (Arc *)&iSeg1; 
	 if(arc){
	   arc->GetCenter(cp);
	   SetCenter(cp);
	  }
	}

	MnjPoint<double> endPoint;
	iSeg2.GetEndPoint(endPoint);
	SetEndPoint(endPoint);
	

}
*/
void MnjArc::SetStartPoint(MnjPoint<double> &p){
	startPoint = p;
}

void MnjArc::SetCenter(MnjPoint<double> &p){
	centerPoint = p;
}

void MnjArc::SetEndPoint(MnjPoint<double> &p){
	endPoint = p;
}


double MnjArc::GetMaxDistance(MnjPoint<double> &p){
	return -1;//tbd
}
/*
void MnjArc::GetNormalAtStartPoint(MnjLine &l){

}

void MnjArc::GetNormalAtEndPoint(MnjLine &l){

}
*/

double MnjArc::GetRadius(void) const{
	double d  = -1;
	GeomUtils::GetDistance(centerPoint,startPoint,d);
	return  d;
}
/*
//Tbd: If it ise used. convert to smaprt pointer later and uncomment.  

 bool MnjArc::IsSameGeometry(Segment *s,double &tol){
	 bool flag = false;
	 if(!s) return flag;
	// Arc *arc = std::dynamic_cast<Arc*>(s);
	 Arc *arc = NULL;
	 if(SegmentType::ARC == s->GetType()){ arc = (Arc*) s  ;}
	 double  r1 = GetRadius();

	if(arc){
		double r2 = arc->GetRadius();

		if(fabs(r1-r2)<tol )
		{   MnjPoint<double> c1;
			GetCenter(c1);
			MnjPoint<double> c2;
			arc->GetCenter(c2);
			double d = -1;
			GeomUtils::GetDistance(c1,c2,d);
			if(d < tol){
				flag = true;
			}
		}
	}
	return flag;

 }
 */
///////////////////////////////////////////////////////////////////////
double MnjArc::GetLength()const{
	double thetaInRadian = GetAngle();
	double r = GetRadius();
	double length=0;
	
	return length = (thetaInRadian/(2*M_PI))*2*M_PI*r;
}
////////////////////////////////////////////////////
MnjPoint<double>  MnjArc::GetCenter(void)const{

    return MnjPoint<double>(centerPoint);
}
////////////////////////////////////////////////
double MnjArc::GetAngle()const{


	MnjDirection X(centerPoint,startPoint);
	MnjDirection vec2(centerPoint,endPoint);
	double angle = X.Angle(vec2);
	return angle;
}


double MnjArc::GetAngle(MnjPoint<double> &ip)const{


	MnjDirection X(centerPoint,startPoint);
	MnjDirection vec2(centerPoint,ip);
	double angle = X.Angle(vec2);
	return angle;
}
//////////////////////////////////////////////////////

/*
double MnjArc::GetMaxDistance(MnjPoint<double> &p){
	return -1;//tbd
}

void MnjArc::GetNormalAtStartPoint(MnjLine &l){

}

void MnjArc::GetNormalAtEndPoint(MnjLine &l){

}
*/
int MnjArc::CreateSmallestArc(vector<boost::shared_ptr<MnjPoint<double>>> &pt_vec,MnjArc &oa){
		 vector<boost::shared_ptr<MnjPoint<double>>>::iterator  it;
		 oa = *this;
		 MnjArc tmp_arc=*this;
		 int error = 0;
		 for(it=pt_vec.end();it!=pt_vec.end();it++){
            tmp_arc.SetEndPoint(**it); 
			double tmpLength =  tmp_arc.GetLength();
			double oaLength =  oa.GetLength();
			if(tmpLength< oaLength) {
				MnjPoint<double> tmpe;
				oa.GetEndPoint(tmpe);
			    //error = 
					oa.SetEndPoint(**it);
				//tbd reset to prvous vlue of the new point result in different radius
			}
		 }
		 return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int MnjArc::Intersect(MnjInfiniteLine &il, vector<boost::shared_ptr<MnjPoint<double>>> &opt_vec){
		int error = 0;
		MnjDirection X = GetXAxis();
		MnjDirection Y = GetYAxis();
		MnjPlane plane(centerPoint,X,Y);
		MnjCircle circle(plane,GetRadius());
        vector<boost::shared_ptr<MnjPoint<double>>> pt_vec;
		error = circle.Intersect(il,pt_vec);
        if(!(error<0)){
            vector<boost::shared_ptr<MnjPoint<double>>>::iterator it=pt_vec.begin();
            for (it; it != pt_vec.end(); it++){
               if(IsPointOnArc(**it)){
                   opt_vec.push_back(*it);
               }
            }

        }
        if(opt_vec.size() > 0 ) 
            error = 0;
		return error;
}
////////////////////////////////////////////////////////////////////////////////////////
bool MnjArc::IsPointOnArc(MnjPoint<double> &p)const{
		double angle = GetAngle(p);
        double dist = GeomUtils::GetDistance(centerPoint,p);
        double endangle = GetAngle(MnjPoint<double>(endPoint));
        if (angle <   endangle  && fabs(GetRadius() -dist) < .0001) 
            return true;
        else 
            return false;
		
}
//////////////////////////////////////////////////////////////////////////////////////////
int MnjArc::ResetThePoint(MnjPoint<double> &icornerPoint,MnjPoint<double> &ip){
        double ds = GeomUtils::GetDistance(icornerPoint,startPoint);
        double de = GeomUtils::GetDistance(icornerPoint,endPoint);
        if(ds<de){
            startPoint = ip;
        }
        else{
            endPoint = ip;
        }
        return 0;
    }
 /////////////////////////////////////////////////////////////////////////////////
  void MnjArc::Flip(void){
        MnjPoint<double> tmp = startPoint;
        startPoint  = endPoint;
        endPoint = tmp;
 }
  int MnjArc::SetSmallerArc(MnjPoint<double> &e1,MnjPoint<double> &c,MnjPoint<double> &e2){
    int error = Set(e1,c,e2);//mnj
    if(GetAngle()>M_PI)
        Flip();
    return error;
 }
  //////////////////////////////////////////////////////////////////////////////////
  MnjPoint<double> MnjArc::GetOtherEnd(const MnjPoint<double> &ip,int &oerror)const{
      oerror = 0;
      if(GeomUtils::IsSame(startPoint,ip)){
          return MnjPoint<double>(endPoint);
      }
      else if(GeomUtils::IsSame(endPoint,ip)) {
          return MnjPoint<double>(startPoint);
      }else{
          oerror = -1;
          return MnjPoint<double>(endPoint);
      }
      
  }
///////////////////////////////////////////////////////////////////////////////////////////
int MnjArc::Set(MnjPoint<double> &s,MnjPoint<double> &center,MnjPoint<double> &e){
 
 int error = 0;
 string msg;

 double d1 = GeomUtils::GetDistance(s,center) ;
 double d2 = GeomUtils::GetDistance(e,center) ;
 if( fabs(d1-d2) > .001 ){
     msg = "Start and End Point at different distance from center.";
     error = -1;
  }
	
  if(error<0){
   string s;
   Mnj::ErrorUtils::CreateErrorString(__FILE__, __LINE__,__FUNCTION__, msg,s);
   throw std::exception(s.c_str());
  }

  SetStartPoint(s);
	SetCenter(center);
	SetEndPoint(e);
  
  return error;

}
///////////////////////////////////////////////////////////////////////////////////////////
MnjDirection MnjArc::Tangent(MnjPoint<double> &ip) {
	double theta = GetAngle(ip);
	//do not make it 1.001*theta (problem when 0==theta ) 
	MnjPoint<double> &p1 =GetPointAtAngle(0.00001 + theta);
	return MnjDirection(ip,p1); 
}
///////////////////////////////////////////////////////////////////////////
MnjDirection MnjArc::TangentAtEnd(MnjPoint<double> &ip){
	  double theta = GetAngle(ip);
 
	MnjPoint<double> &p1 =GetPointAtAngle(theta + 0.00001 );
    if(!IsPointOnArc(p1)){
       p1 =GetPointAtAngle(theta - 0.00001 );
    }
	return MnjDirection(ip,p1); 

 }
///////////////////////////////////////////////////////////////////////////////////////////
 //working before new version 
MnjPoint<double> MnjArc::GetPointAtAngle(const double &itheta) {
		double  r = GetRadius();
		MnjDirection X = GetXAxis();
		MnjDirection Y = GetYAxis();
		//FlowVector vec = centerPoint + (X*r)*cos(itheta)+ Y*r*sin(itheta);
        {//debug code 
            MnjDirection z_cal = X.CrossProduct(Y);
            //double num  = z_cal.DotProduct(Z);
            //MnjDirection prod = z_cal.CrossProduct(Z);
            int a = 0;
        }
		double x_c= fabs(r*cos(itheta)); 
		double y_c= fabs(r*sin(itheta));
		MnjVector vec = MnjVector(centerPoint) + X*x_c+ Y*y_c;
		return MnjPoint<double>(vec.x,vec.y,vec.z); 
}
//////////////////////////////////////////////////////////////////////
double MnjArc::Distance(MnjPoint<double> &ip,int &oerror) {
		
    oerror =0;
    //MnjPoint<double> C = GetCenter();
    //MnjInfiniteLine infLine(centerPoint,ip);
    //FlowCircle circle(*this);
    //circle.Intersect(infLine);

    double r = GetRadius();
    double d = GeomUtils::GetDistance(ip,centerPoint);

    return fabs(d-r);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool MnjArc::PointProjectOnArc(MnjPoint<double> &ip,MnjPoint<double> &op,int &oerror) {
		
    oerror =0;

    double r = GetRadius();
    double d = GeomUtils::GetDistance(ip,centerPoint);
    op = centerPoint + MnjDirection(centerPoint,ip)*r;
    return IsPointOnArc(op);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool MnjArc::PointProjectOnArc(MnjPoint<double> &ip,int &oerror) {
		
    MnjPoint<double> p ;
    return PointProjectOnArc(ip,p,oerror);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
 int MnjArc::Partition(const unsigned int &n, list<boost::shared_ptr<MnjArc>> &ol){
    int error =0;
    if(n<=0 || ol.size()> 0)
        error = -1;
    if(!error){
        double startA = GetAngle(startPoint);
        double endA = GetAngle(endPoint);
        //MnjPoint<double> cp = 
        for(  unsigned int i = 0; i < n ; i++ ) {
            MnjPoint<double> stmp = GetPointAtAngle(startA + ((endA -startA)*i)/n);
            MnjPoint<double> etmp = GetPointAtAngle(startA + ((endA-startA)*(i+1))/n);
            boost::shared_ptr<MnjArc> ltmp(new MnjArc(stmp,centerPoint,etmp));
            ol.push_back(ltmp);
        }
    }
   return error;
}
 /////////////////////////////////////////////////////////////////////////////////
 int MnjArc::Project(MnjPoint<double> &ip,MnjPoint<double> &op) {
		
    int error =0;
    double r = GetRadius();
    MnjPoint<double>  centerPoint = GetCenter();
    double d = GeomUtils::GetDistance(ip,centerPoint);
    op = centerPoint + MnjDirection(centerPoint,ip)*r;
    if(!IsPointOnArc(op) ) error = -1;
    return error;
}
 //////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	inline MnjDirection MnjArc::GetXAxis(void)const{
		return MnjDirection(centerPoint,startPoint);
	}
	///////////////////////////////////////////////////////////
	inline MnjDirection MnjArc::GetYAxis(void)const{
		return GetZAxis().CrossProduct(GetXAxis());
	}
	///////////////////////////////////////////////////////////
	inline MnjDirection MnjArc::GetZAxis(void)const{
	     return GetXAxis().CrossProduct(MnjVector(centerPoint,endPoint));
	     
	}

void MnjArc::GetEnds(MnjPoint<double> &s, MnjPoint<double> &e)const{
	GetStartPoint(s);
	GetEndPoint(e);
}
 /////////////////////////////////////////////////////////////////////////////////////////
#if _DEBUG 
	void MnjArc::Print(void){
cout << "Arc: ";
cout << "\tStart: ";
	startPoint.Print();
cout << "\tCenter MnjPoint<double>: ";
	centerPoint.Print();
cout << "\tEnd: ";
	endPoint.Print();
}
#endif 
