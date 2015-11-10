#ifndef SHADE_REC_H
#define SHADE_REC_H

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
	Point3D hitPoint;
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

#endif // SHADE_REC_H