#ifndef __MATHS__
#define __MATHS__

#include "Constants.h"
#include <random>
#include <ctime>

// Declarations
//*************************************************
inline double toRads(double angle);
inline double toDegs(double angle);
inline double max(double x0, double x1);
inline double min(double x0, double x1);
inline void rand_seed(unsigned int seed);

// MAKE SURE TO CALL ME BEFORE USING RAND FNCT'S
inline void rand_seed();

inline float randFloat();
inline float randFloat(int a, int b);
inline int randInt();
inline float randInt(int a, int b);
//*************************************************

// Definitions
//*************************************************
inline double toRads(double angle)
{
	return angle * PI_ON_180;
}

inline double toDegs(double angle)
{
	return angle * ONE_EIGHTY_ON_PI;
}

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
inline float randFloat()
{
	return rand() * INV_RAND_MAX;
}

// Gen random float in range [a,b]
inline float randFloat(int a, int b)
{
	return randFloat() * (b - a) + a;
}

// Gen random int 
inline int randInt()
{
	return rand();
}

// Gen random int in range [a,b]
inline float randInt(int a, int b)
{
	return randFloat() * (b - a) + a;
}

//*************************************************

#endif
