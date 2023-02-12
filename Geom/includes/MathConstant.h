#pragma once
//copyright(c) 2009- 2016 Manoj Lnu 
//#define M_PI 3.1415926536
#include <math.h>
#ifdef M_PI
#undef M_PI 
#define M_PI 3.14159265358979323846264338327
#endif 
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

#define MNJ_DEFAULT_ANGLE_TOLERANCE (M_PI/180.0)

#define MNJ_IS_FINITE(x) (0x7FF0 != (*((unsigned short*)(&x) + 3) & 0x7FF0))
#define MNJ_DBL_MIN 2.22507385850720200e-308
#define MNJ_UNSET_VALUE -1.23432101234321e+308
#define MNJ_SQRT_EPSILON 1.490116119385000000e-8
#define MNJ_ZERO_TOLERANCE 1.0e-12
#define MNJ_MINIMUM_ANGLE_TOLERANCE (MNJ_DEFAULT_ANGLE_TOLERANCE/10.0)


// works on little endian CPUs with IEEE doubles
#define MNJ_IS_FINITE(x) (0x7FF0 != (*((unsigned short*)(&x) + 3) & 0x7FF0))  // valid for little endian CPUs with IEEE doubles
#define MNJ_IS_VALID(x)  (x != MNJ_UNSET_VALUE && 0x7FF0 != (*((unsigned short*)(&x) + 3) & 0x7FF0))  // valid for little endian CPUs with IEEE doubles
#define MNJ_IS_VALID_FLOAT(x)  (x != MNJ_UNSET_FLOAT)   // valid for little endian CPUs with IEEE doubles

#if defined(DBL_EPSILON)
#define MNJ_EPSILON DBL_EPSILON
#else
#define MNJ_EPSILON 2.2204460492503131e-16
#endif
