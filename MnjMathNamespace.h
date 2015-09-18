#ifndef MnjMathNamespace
#define MnjMathNamespace

////////////////////////////////////////////////////////////
///
/
///     Subsystem : None
///     Author : Manoj Lnu
///     Date : 1/30/2015
///
#include <utility>
#include <vector>
#include <memory>

#include "MnjPoint.h"

using namespace std;


namespace MnjMath {

	typedef vector<double> vec_dbl;
	typedef vector<vector<double>> vec_vec_dbl;
	typedef vector<vector<vector<double>>> vec_vec_vec_dbl;

	typedef MnjPoint<double> dbl_3d_pt;
	typedef shared_ptr<MnjPoint<double>> shared_ptr_pt;
	typedef std::pair<double, double> dbl_dbl_pr;

	typedef vector<std::shared_ptr<MnjPoint<double>>>     shared_ptr_vec_pt; 
		
	

	
	map < int , string > digit2string = {
	{1,"one"},
	{2,"two"},
	{3,"three"},
	{4,"four"},
	{5,"five"},
	{6,"six"},
	{7,"seven"},
	{8,"eight"},
	{9,"nine"},
}; 
};
#endif 
