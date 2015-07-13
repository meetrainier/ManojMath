#pragma once 
#include "MnjVector.h"
///
//#include <boost/shared_ptr.hpp>
extern MnjVector operator*(double d, const MnjVector& v);
//-----------------------------------------------------------------------------------------
extern MnjVector operator*(int i, const MnjVector& v);
//-----------------------------------------------------------------------------------------
extern MnjVector operator*(float f, const MnjVector& v);