#include "SingleSphere.h"
#include "World.h"
#include "ShadeRec.h"

// Constructors
SingleSphere::SingleSphere(void)
	: Tracer()
{}

SingleSphere::SingleSphere(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// Destructor
SingleSphere::~SingleSphere(void) {}


// Trace Ray
RGBColor SingleSphere::traceRay(const Ray& ray) const {
	ShadeRec	sr(*world_ptr); 	// not used
	double    	t;  				// not used

	if (world_ptr->sphere.hit(ray, t, sr))
	{
		return red;
	}
	else
		return black;
}

RGBColor SingleSphere::traceRay(const Ray ray, const int depth) const
{
	ShadeRec	sr(*world_ptr); 	// not used
	double    	t;  				// not used

	if (world_ptr->sphere.hit(ray, t, sr))
	{
		return red;
	}
	else
		return black;
}


