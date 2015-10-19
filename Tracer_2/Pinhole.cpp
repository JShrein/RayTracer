#include "Constants.h"
#include "Pinhole.h"


Pinhole::Pinhole()
	: Camera(),
	  d(500),
	  zoom(1.0)
{ }

Pinhole::Pinhole(const Point3D& eye, const Point3D& look)
	: Camera(eye, look),
 	  d(500),
	  zoom(1.0)
{ }

Pinhole::Pinhole(const Point3D& eye, const Point3D& look, const float dist)
	: Camera(eye, look),
	  d(dist),
	  zoom(1.0)
{ }

Pinhole::Pinhole(const Point3D& eye, const Point3D& look, const float dist, const float zf)
	: Camera(eye, look),
	  d(dist),
	  zoom(zf)
{ }

Pinhole::Pinhole(const Pinhole& p)
	: Camera(p),
	  d(p.d),
	  zoom(p.zoom)
{ }

Camera* Pinhole::clone() const
{
	return new Pinhole(*this);
}

Pinhole& Pinhole::operator=(const Pinhole& p)
{
	if (this == &p)
		return *this;
	
	Camera::operator=(p);
	d = p.d;
	zoom = p.zoom;
	return *this;
}

Pinhole::~Pinhole() 
{ }

// Setters/Getters
Vector3D Pinhole::getDir(const Point2D& p) const
{
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();

	return dir;
}

void Pinhole::renderScene(World& w)
{
	RGBColor	pixelColor;
	ViewPlane	vp(w.vp);
	Ray			ray;
	int 		depth = 0;
	Point2D		sample;
	Point2D 	pp;		// sample point on a pixel
	int n = vp.rootNumSamples;// (int)sqrt((float)vp.numSamples);

	vp.s /= zoom;
	ray.o = eyePos;

	// vertical image coord
	for (int r = 0; r < vp.vres; r++) {
		// horizontal image coord	
		for (int c = 0; c < vp.hres; c++) {	
			pixelColor = black;

			for (int j = 0; j < vp.numSamples; j++)	{
				sample = vp.sampler_ptr->sampleUnitSquare();
				pp.x = vp.s * (c - 0.5f * vp.hres + sample.x);
				pp.y = vp.s * (r - 0.5f * vp.vres + sample.y);
				ray.d = getDir(pp);
				pixelColor += w.tracer_ptr->traceRay(ray, depth);
			}

			pixelColor /= (float)vp.numSamples;
			pixelColor *= exposureTime;
			w.displayPixel(r, c, pixelColor);
		}
	}
}