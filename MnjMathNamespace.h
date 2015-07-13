#ifndef MnjMathNamespace
#define MnjMathNamespace

////////////////////////////////////////////////////////////
///
///     Flow International Corp.
///     Project : Cycle time prediction
///     Subsystem : None
///     Author : Manoj Lnu
///     Date : 1/30/2015
///
///     Copyright (C) 2015 Flow International Corp.
///		All rights reserved.
///
/// 1/30/2015:Manoj : Name space for Flow Math Infrastructure 
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

	//typedef boost::shared_ptr<MnjLine> shared_ptr_line;
	//typedef boost::shared_ptr<MnjArc> shared_ptr_arc;

	typedef vector<std::shared_ptr<MnjPoint<double>>>     shared_ptr_vec_pt; 
	//typedef vector<std::shared_ptr<FlowSegment>> shared_ptr_vec;
	//typedef vector<std::shared_ptr<FlowSegment>>::iterator shared_ptr_vec_it;
	//typedef vector<std::shared_ptr<FlowSegment>>::const_iterator shared_ptr_vec_const_it;

	//typedef list<std::shared_ptr<FlowSegment>> shared_ptr_list;
	//typedef list<std::shared_ptr<FlowSegment>>::iterator shared_ptr_list_it;

	////const counterprts of the above
	//typedef std::shared_ptr<const FlowSegment> const_shared_ptr;
	////typedef boost::shared_ptr<const FlowLine> const_shared_ptr_line;
	////typedef boost::shared_ptr<const FlowArc> const_shared_ptr_arc;

	//typedef vector<std::shared_ptr<const FlowSegment>> const_shared_ptr_vec;
	//typedef vector<std::shared_ptr<const FlowSegment>>::iterator const_shared_ptr_vec_it;
	//typedef vector<std::shared_ptr<const FlowSegment>>::const_iterator const_shared_ptr_vec_const_it;

	//typedef list<std::shared_ptr<const FlowSegment>> const_shared_ptr_list;
	//typedef list<std::shared_ptr<const FlowSegment>>::iterator const_shared_ptr_list_it;
};
#endif 