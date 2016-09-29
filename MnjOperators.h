#pragma once 
//copyright(c) 2009- 2016 Manoj Lnu 
#include "MnjVector.h"
///
//#include <boost/shared_ptr.hpp>
extern MnjVector operator*(double d, const MnjVector& v);
//-----------------------------------------------------------------------------------------
extern MnjVector operator*(int i, const MnjVector& v);
//-----------------------------------------------------------------------------------------
extern MnjVector operator*(float f, const MnjVector& v);