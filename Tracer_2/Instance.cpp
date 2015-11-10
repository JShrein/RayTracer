#include "Constants.h"
#include "Instance.h"

// Declare static transformation matrix
Matrix Instance::transformation;


// Default constructor
Instance::Instance(void)
	: GeometricObject(),
	obj_ptr(NULL),
	inverseMat(),
	aabb(),
	doTextureTransform(true)
{
	transformation.setIdentity();
}


// Constructor
Instance::Instance(GeometricObject* object_ptr)
	: GeometricObject(),
	  obj_ptr(object_ptr),
	  inverseMat(),
	  aabb(),
	  doTextureTransform(true)
{
	transformation.setIdentity();
}


// Copy constructor
Instance::Instance(const Instance& instance)
	: GeometricObject(instance),
	  inverseMat(instance.inverseMat),
	  doTextureTransform(instance.doTextureTransform)
{
	if (instance.obj_ptr)
		obj_ptr = instance.obj_ptr->clone();
	else 
		obj_ptr = NULL;
}


// Clone
Instance* Instance::clone() const 
{
	return new Instance(*this);
}


// Destructor
Instance::~Instance()
{
	if (obj_ptr) 
	{
		delete obj_ptr;
		obj_ptr = NULL;
	}
}


// Assignment operator
Instance& Instance::operator= (const Instance& inst)
{
	if (this == &inst)
		return *this;

	GeometricObject::operator=(inst);

	if (obj_ptr)
	{
		delete obj_ptr;
		obj_ptr = NULL;
	}

	if (inst.obj_ptr)
		obj_ptr = inst.obj_ptr->clone();
	else
		obj_ptr = NULL;

	inverseMat = inst.inverseMat;
	aabb = inst.aabb;
	doTextureTransform = inst.doTextureTransform;

	return *this;
}


// Set Object
void Instance::setObject(GeometricObject* object_ptr)
{
	obj_ptr = object_ptr;
}

// Set the bounding box
// Note: ***Always call from build function and only when placing in grid
void Instance::computeAABB()
{
	// Get untransformed axis-aligned bounding box
	AABB objectAABB = obj_ptr->getAABB();

	// Transform each box vertex and find min and max
	Point3D v[8];

	v[0].x = objectAABB.x0; v[0].y = objectAABB.y0; v[0].z = objectAABB.z0;
	v[1].x = objectAABB.x1; v[1].y = objectAABB.y0; v[1].z = objectAABB.z0;
	v[2].x = objectAABB.x1; v[2].y = objectAABB.y1; v[2].z = objectAABB.z0;
	v[3].x = objectAABB.x0; v[3].y = objectAABB.y1; v[3].z = objectAABB.z0;

	v[4].x = objectAABB.x0; v[4].y = objectAABB.y0; v[4].z = objectAABB.z1;
	v[5].x = objectAABB.x1; v[5].y = objectAABB.y0; v[5].z = objectAABB.z1;
	v[6].x = objectAABB.x1; v[6].y = objectAABB.y1; v[6].z = objectAABB.z1;
	v[7].x = objectAABB.x0; v[7].y = objectAABB.y1; v[7].z = objectAABB.z1;


	// Do transformation
	v[0] = transformation * v[0];
	v[1] = transformation * v[1];
	v[2] = transformation * v[2];
	v[3] = transformation * v[3];
	v[4] = transformation * v[4];
	v[5] = transformation * v[5];
	v[6] = transformation * v[6];
	v[7] = transformation * v[7];

	// Set transformation to identity (since it is static we must prepare for next use)
	transformation.setIdentity();

	// Find min
	float x0 = v[0].x;//kHugeValue;
	float y0 = v[0].y;//kHugeValue;
	float z0 = v[0].z;//kHugeValue;

	for (int j = 1; j <= 7; j++)
	{
		if (v[j].x < x0)
			x0 = v[j].x;
	}

	for (int j = 1; j <= 7; j++)
	{
		if (v[j].y < y0)
			y0 = v[j].y;
	}

	for (int j = 1; j <= 7; j++)
	{
		if (v[j].z < z0)
			z0 = v[j].z;
	}

	// Find max
	float x1 = v[0].x;//-kHugeValue;
	float y1 = v[0].y;//-kHugeValue;
	float z1 = v[0].z;//-kHugeValue;

	for (int j = 1; j <= 7; j++)
	{
		if (v[j].x > x1)
			x1 = v[j].x;
	}

	for (int j = 1; j <= 7; j++)
	{
		if (v[j].y > y1)
			y1 = v[j].y;
	}

	for (int j = 1; j <= 7; j++)
	{
		if (v[j].z > z1)
			z1 = v[j].z;
	}

	// Assign values to bounding box
	// NOTE: ***Remember AABB is defined by 2 points***
	aabb.x0 = x0;
	aabb.y0 = y0;
	aabb.z0 = z0;
	aabb.x1 = x1;
	aabb.y1 = y1;
	aabb.z1 = z1;
}


// Get bounding box
AABB Instance::getAABB()
{
	return aabb;
}

// Get material
Material* Instance::getMat() const
{
	return mat_ptr;
}


// Set_material
// NOTE: ***mat_ptr is GeometricObject::mat_ptr
void Instance::setMat(Material* m_ptr)
{
	mat_ptr = m_ptr;
}



// Do hit function
// NOTE: ***Each shape hit() function is called, no need to modify***
bool Instance::hit(const Ray& ray, double& t, ShadeRec& sr) const {
	// inverseRay is ray transformed by inverse transformation matrix
	Ray inverseRay(ray);
	inverseRay.o = inverseMat * inverseRay.o;
	inverseRay.d = inverseMat * inverseRay.d;

	if (obj_ptr->hit(inverseRay, t, sr))
	{
		sr.normal = inverseMat * sr.normal;
		sr.normal.normalize();

		if (obj_ptr->getMat())
			mat_ptr = obj_ptr->getMat();

		if (!doTextureTransform)
			sr.localHitPoint = ray.o + t * ray.d;

		return true;
	}
	return false;
}


// Scale
void Instance::scale(const Vector3D& s)
{

	Matrix	invScaleMat;

	invScaleMat.m[0][0] = 1.0 / s.x;
	invScaleMat.m[1][1] = 1.0 / s.y;
	invScaleMat.m[2][2] = 1.0 / s.z;

	inverseMat = inverseMat * invScaleMat;

	Matrix	scaleMat;

	scaleMat.m[0][0] = s.x;
	scaleMat.m[1][1] = s.y;
	scaleMat.m[2][2] = s.z;

	transformation = scaleMat * transformation;
}


// Scale
void Instance::scale(const double a, const double b, const double c) 
{
	Matrix	invScaleMat;

	invScaleMat.m[0][0] = 1.0 / a;
	invScaleMat.m[1][1] = 1.0 / b;
	invScaleMat.m[2][2] = 1.0 / c;

	inverseMat = inverseMat * invScaleMat;

	Matrix	scaleMat;

	scaleMat.m[0][0] = a;
	scaleMat.m[1][1] = b;
	scaleMat.m[2][2] = c;

	transformation = scaleMat * transformation;
}


// Translation
void Instance::translate(const Vector3D& trans)
{
	Matrix invTranslationMat;

	invTranslationMat.m[0][3] = -trans.x;
	invTranslationMat.m[1][3] = -trans.y;
	invTranslationMat.m[2][3] = -trans.z;

	inverseMat = inverseMat * invTranslationMat;

	Matrix translationMat;					// temporary translation matrix	

	translationMat.m[0][3] = trans.x;
	translationMat.m[1][3] = trans.y;
	translationMat.m[2][3] = trans.z;

	transformation = translationMat * transformation;
}


// Translation
void Instance::translate(const double dx, const double dy, const double dz)
{
	Matrix invTranslationMat;	

	invTranslationMat.m[0][3] = -dx;
	invTranslationMat.m[1][3] = -dy;
	invTranslationMat.m[2][3] = -dz;

	inverseMat = inverseMat * invTranslationMat;

	Matrix translationMat;

	translationMat.m[0][3] = dx;
	translationMat.m[1][3] = dy;
	translationMat.m[2][3] = dz;

	transformation = translationMat * transformation;
}

// Rotate about x-axis
void Instance::rotateX(const double angle)
{
	double sinAngle = sin(angle * PI_ON_180);
	double cosAngle = cos(angle * PI_ON_180);

	Matrix invXRotMat;

	invXRotMat.m[1][1] = cosAngle;
	invXRotMat.m[1][2] = sinAngle;
	invXRotMat.m[2][1] = -sinAngle;
	invXRotMat.m[2][2] = cosAngle;

	inverseMat = inverseMat * invXRotMat;

	Matrix xRotMat;

	xRotMat.m[1][1] = cosAngle;
	xRotMat.m[1][2] = -sinAngle;
	xRotMat.m[2][1] = sinAngle;
	xRotMat.m[2][2] = cosAngle;

	transformation = xRotMat * transformation;
}

// Rotate about y-axis
void Instance::rotateY(const double angle)
{
	double sinAngle = sin(angle * PI / 180.0);
	double cosAngle = cos(angle * PI / 180.0);

	Matrix invYRotMat;

	invYRotMat.m[0][0] = cosAngle;
	invYRotMat.m[0][2] = -sinAngle;
	invYRotMat.m[2][0] = sinAngle;
	invYRotMat.m[2][2] = cosAngle;

	inverseMat = inverseMat * invYRotMat;

	Matrix yRotMat;

	yRotMat.m[0][0] = cosAngle;
	yRotMat.m[0][2] = sinAngle;
	yRotMat.m[2][0] = -sinAngle;
	yRotMat.m[2][2] = cosAngle;

	transformation = yRotMat * transformation;
}

// Rotate about z-axis
void Instance::rotateZ(const double angle)
{
	double sinAngle = sin(angle * PI / 180.0);
	double cosAngle = cos(angle * PI / 180.0);

	Matrix invZRotMat;

	invZRotMat.m[0][0] = cosAngle;
	invZRotMat.m[0][1] = sinAngle;
	invZRotMat.m[1][0] = -sinAngle;
	invZRotMat.m[1][1] = cosAngle;

	inverseMat = inverseMat * invZRotMat;

	Matrix zRotMat;

	zRotMat.m[0][0] = cosAngle;
	zRotMat.m[0][1] = -sinAngle;
	zRotMat.m[1][0] = sinAngle;
	zRotMat.m[1][1] = cosAngle;

	transformation = zRotMat * transformation;
}

// Shear
void Instance::shear(const Matrix& s)
{
	Matrix invShearMat;

	// Discriminant
	double d = 1.0 - s.m[1][0] * s.m[0][1] -
					 s.m[2][0] * s.m[0][2] -
					 s.m[2][1] * s.m[1][2] +
					 s.m[1][0] * s.m[2][1] * s.m[0][2] +
					 s.m[2][0] * s.m[0][1] * s.m[2][1];

	// diagonals
	invShearMat.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	invShearMat.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	invShearMat.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	invShearMat.m[3][3] = d;

	// first row
	invShearMat.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	invShearMat.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];

	// second row
	invShearMat.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	invShearMat.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];

	// third row
	invShearMat.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	invShearMat.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2];

	// divide by discriminant
	invShearMat = invShearMat / d;
	inverseMat = inverseMat * invShearMat;
	transformation = s * transformation;
}