#ifndef __WORLD__
#define __WORLD__

#include "Maths.h"

#include "ViewPlane.h"
#include "RGBColor.h"
#include "Sphere.h"
#include "Tracer.h"

#include <vector>

class World {
public:
	ViewPlane vp;
	RGBColor background_color;
	std::vector<GeometricObject*> objects;
	Sphere sphere;
	Tracer* tracer_ptr;

	World();
	~World();

	void build();

	void add_object(GeometricObject* object_ptr);

	ShadeRec hit_bare_bones_object(const Ray& ray);

	void render_scene() const;

	void open_window(const int hres, const int vres) const;

	void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

	RGBColor max_to_one(const RGBColor& c) const;

	RGBColor clamp_to_color(const RGBColor& raw_color) const;

	RGBColor color_to_range(const RGBColor& c, int max) const;
};

inline void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

#endif // __WORLD__