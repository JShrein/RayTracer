#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <stdlib.h>
#include "RGBColor.h"

const double 	PI = 3.1415926535897932384;
const double 	TWO_PI = 6.2831853071795864769;
const double 	PI_ON_180 = 0.0174532925199432957;
const double	ONE_EIGHTY_ON_PI = 57.295779513082320877;
const double 	INV_PI = 0.3183098861837906715;
const double 	INV_TWO_PI = 0.1591549430918953358;

const double 	kEpsilon = 0.0001;
const double	kHugeValue = 1.0E10;

const RGBColor	black(0.0);
const RGBColor	white(1.0);
const RGBColor  gray(0.5, 0.5, 0.5);
const RGBColor	red(1.0, 0.0, 0.0);
const RGBColor  green(0.0, 1.0, 0.0);
const RGBColor  blue(0.0, 0.0, 1.0);
const RGBColor magenta(1.0, 0.0, 1.0);
const RGBColor cyan(0.0, 1.0, 1.0);
const RGBColor yellow(1.0, 1.0, 0.0);

const float 	INV_RAND_MAX = 1.0f / (float)RAND_MAX;

#endif
