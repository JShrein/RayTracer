#ifndef __MATHS__
#define __MATHS__

#include "Constants.h"
#include <random>
#include <ctime>

inline double max(double x0, double x1);
inline double max(double x0, double x1)
{
	return((x0 > x1) ? x0 : x1);
}

inline void rand_seed(unsigned int seed);
inline void rand_seed(unsigned int seed)
{

	srand(seed);
}

inline void rand_seed();
inline void rand_seed()
{

	srand(time(0));
}

inline float rand_float();
inline float rand_float()
{
	return rand() * INV_RAND_MAX;
}

#endif
