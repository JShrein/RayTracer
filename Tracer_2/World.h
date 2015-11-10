#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "ViewPlane.h"
#include "RGBColor.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Light.h"
#include "Ambient.h"
#include "AmbientOccluder.h"
#include "Sphere.h"
#include "Ray.h"
#include "SingleSphere.h"

#include "Camera.h"

using std::vector;

class World {
public:
	ViewPlane vp;
	RGBColor backgroundColor;
	vector<GeometricObject*> objects;
	Sphere sphere;
	Tracer* tracer_ptr;
	Camera* camera_ptr;
	Light* ambient_ptr;
	vector<Light*> lights;
    //int rank;
    //int size;

	World();
	~World();

	void build();

	void addObject(GeometricObject* object_ptr);
	void addLight(Light* light_ptr);

	//ShadeRec hitBareBonesObject(const Ray& ray);
	ShadeRec hitObjects(const Ray& ray);

	void setCamera(Camera* camera_ptr);
	void setAmbientLight(Ambient* ambient_ptr);
	void setAmbientLight(AmbientOccluder* ambient_ptr);

	// Orthographic render
	void renderScene() const;

	// Perspective render
	void render_perspective() const;

	void openWindow(const int hRes, const int vRes) const;
	void displayPixel(const int row, const int column, const RGBColor& pixelColor) const;

	RGBColor maxToOne(const RGBColor& c) const;
	RGBColor clampToColor(const RGBColor& raw_color) const;
	RGBColor colorToRange(const RGBColor& c, int max) const;
};

inline void World::addObject(GeometricObject* object_ptr) 
{
	objects.push_back(object_ptr);
}

inline void World::addLight(Light* light_ptr)
{
	lights.push_back(light_ptr);
}

// Set camera
inline void World::setCamera(Camera* cam_ptr)
{
	camera_ptr = cam_ptr;
}

inline void World::setAmbientLight(Ambient* amb_ptr)
{
	ambient_ptr = amb_ptr;
}

inline void World::setAmbientLight(AmbientOccluder* amb_ptr)
{
	ambient_ptr = amb_ptr;
}

#endif // WORLD_H
