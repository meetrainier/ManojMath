//copyright(c) 2009- 2016 Manoj Lnu 
#ifndef MnjMathNamespace
#define MnjMathNamespace

////////////////////////////////////////////////////////////
///
///     Subsystem : None
///     Author : Manoj Lnu
///     Date : 1/30/2015
///
#include <utility>
#include <vector>
#include <memory>
#include <map>
#include "MnjPoint.h"

using namespace std;


namespace MnjMath {

	//changing the above to using 
	using vec_dbl = vector<double> ;
	using vec_vec_dbl= vector<vector<double>> ;
	using vec_vec_vec_dbl= vector<vector<vector<double>>> ;

	using dbl_3d_pt= MnjPoint<double> ;
	using shared_ptr_pt = shared_ptr<MnjPoint<double>> ;
	using dbl_dbl_pr= std::pair<double, double> ;

	using shared_ptr_vec_pt = vector<std::shared_ptr<MnjPoint<double>>>     ;
	
	const map < int , string > digit2string = {
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
