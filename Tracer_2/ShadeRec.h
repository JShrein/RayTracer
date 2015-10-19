#ifndef __SHADE_REC__
#define __SHADE_REC__

#include "Constants.h"

#include <vector>

class World;
class Material;

#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec {
public:
	bool hitAnObject;
	Material* mat_ptr;
	Point3D hit_point;
	Point3D localHitPoint;
	Normal normal;
	Ray ray;
	int depth;
	double t;
	RGBColor color;
	Vector3D dir;
	World& w;

	ShadeRec(World& wr);
	ShadeRec(const ShadeRec& sr);
	~ShadeRec();
};

#endif // __SHADE_REC__