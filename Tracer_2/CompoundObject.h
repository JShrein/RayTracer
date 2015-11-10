#ifndef COMPOUND_OBJECT_H
#define COMPOUND_OBJECT_H

#include <vector> 
#include "GeometricObject.h"

// CompoundObject class: allows construction of nested compound objects
class CompoundObject : public GeometricObject 
{
public:
	CompoundObject();
	CompoundObject(const CompoundObject& c);
	~CompoundObject();

	virtual CompoundObject* clone() const;
	CompoundObject& operator= (const CompoundObject& c);

	virtual void setMat(Material* material_ptr);

	virtual void addObject(GeometricObject* object_ptr);
	int getNumObj();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& s) const;
	virtual bool shadowHit(const Ray& ray, double& tMin) const;

protected:
	std::vector<GeometricObject*> objects;

private:
	void deleteObjects();
	void copyObjects(const std::vector<GeometricObject*>& otherObjects);
};

//  get_num_objects
inline int CompoundObject::getNumObj()
{
	return (objects.size());
}

#endif // COMPOUND_OBJECT_H