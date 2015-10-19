#include "Constants.h"
#include "ShadeRec.h"

// Constructors - No default since World must be supplied
ShadeRec::ShadeRec(World& wr)
	:hitAnObject(false),
	mat_ptr(NULL),
	hit_point(),
	localHitPoint(),
	normal(),
	ray(),
	depth(0),
	t(0),
	dir(),
	color(black),
	w(wr)
{ }

ShadeRec::ShadeRec(const ShadeRec& sr)
	: hitAnObject(sr.hitAnObject),
	hit_point(sr.hit_point),
	mat_ptr(sr.mat_ptr),
	localHitPoint(sr.localHitPoint),
	normal(sr.normal),
	ray(sr.ray),
	depth(sr.depth),
	t(sr.t),
	dir(sr.dir),
	color(sr.color),
	w(sr.w)
{ }

// Destructor
ShadeRec::~ShadeRec()
{
}