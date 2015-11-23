#include "Constants.h"
#include "CompoundObject.h"

// Constructors
CompoundObject::CompoundObject()
	: GeometricObject()
{ }

// copy constructor
CompoundObject::CompoundObject(const CompoundObject& c)
	: GeometricObject(c) 
{
	copyObjects(c.objects);
}

// assignment operator
CompoundObject& CompoundObject::operator= (const CompoundObject& co) 
{
	if (this == &co)
		return *this;

	GeometricObject::operator= (co);

	copyObjects(co.objects);

	return *this;
}

// destructor
CompoundObject::~CompoundObject() 
{
	deleteObjects();
}

CompoundObject* CompoundObject::clone() const
{
	return new CompoundObject(*this);
}

void CompoundObject::addObject(GeometricObject* object_ptr) 
{
	objects.push_back(object_ptr);
}

void CompoundObject::setMat(Material* material_ptr) 
{
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->setMat(material_ptr);
}

// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 
void CompoundObject::deleteObjects()
{
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase(objects.begin(), objects.end());
}

void CompoundObject::copyObjects(const std::vector<GeometricObject*>& geoObjects)
{
	deleteObjects();
	int num_objects = geoObjects.size();

	for (int j = 0; j < num_objects; j++)
		objects.push_back(geoObjects[j]->clone());
}

bool CompoundObject::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double		t;
	Normal		normal;
	Point3D		hitPoint;
	bool		hit = false;
	tmin = kHugeValue;
	int 		num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin))
		{
			hit = true;
			tmin = t;
			mat_ptr = objects[j]->getMat();	// lhs is GeometricObject::material_ptr
			normal = sr.normal;
			hitPoint = sr.localHitPoint;
		}

	if (hit)
	{
		sr.t = tmin;
		sr.normal = normal;
		sr.localHitPoint = hitPoint;
	}

	return hit;
}

bool CompoundObject::shadowHit(const Ray& ray, double& tmin) const
{
	double		t;
	bool		hit = false;
	tmin =		kHugeValue;
	int 		num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		if (objects[j]->shadowHit(ray, t) && (t < tmin))
		{
			hit = true;
			tmin = t;
		}
	}

	return hit;
}