#ifndef __MATHS__
#define __MATHS__

#include "Constants.h"
#include <random>
#include <ctime>

// Declarations
//*************************************************
inline double max(double x0, double x1);
inline double min(double x0, double x1);
inline void rand_seed(unsigned int seed);

// MAKE SURE TO CALL ME BEFORE USING RAND FNCT'S
inline void rand_seed();

inline float rand_float();
inline float rand_float(int a, int b);
inline int rand_int();
inline float rand_int(int a, int b);
//*************************************************

// Definitions
//*************************************************
inline double max(double x0, double x1)
{
	return x0 > x1 ? x0 : x1;
}

inline double min(double x0, double x1)
{
	return x0 < x1 ? x0 : x1;
}


inline void rand_seed(unsigned int seed)
{

	srand(seed);
}


inline void rand_seed()
{
	srand((unsigned int)time(0));
}

// Gen random float
inline float rand_float()
{
	return rand() * INV_RAND_MAX;
}

// Gen random float in range [a,b]
inline float rand_float(int a, int b)
{
	return rand_float() * (b - a) + a;
}

// Gen random int 
inline int rand_int()
{
	return rand();
}

// Gen random int in range [a,b]
inline float rand_int(int a, int b)
{
	return rand_float() * (b - a) + a;
}

//*************************************************

#endif
