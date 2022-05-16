#include "mbed.h"

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define abs(value) ((value)> 0 ?(value):(-value))
//////Utils Function copied from VESC Source Code/////HT
#define UTILS_LP_FAST(value, sample, filter_constant)   (value -= (filter_constant) * (value - (sample)))

//static constexpr double NO_ANGLE = -999;
//const double PI = 3.1415926;

