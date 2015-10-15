#ifndef __SHADE_REC__
#define __SHADE_REC__

#include "Constants.h"

#include <vector>

class World;

#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"
//#include "World.h"

class ShadeRec {
public:
	bool hit_an_object;
	Point3D local_hit_point;
	Normal normal;
	RGBColor color;
	World& w;

	ShadeRec(World& wr);
	ShadeRec(const ShadeRec& sr);
};

#endif // __SHADE_REC__