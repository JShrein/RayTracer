#include "Constants.h"
#include "Pinhole.h"
#include <stdio.h>
#include <ctime>
#include <iostream>

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
	clock_t		startTime;
	clock_t		currentTime;
	clock_t		endTime;
	float		totalTime;

	RGBColor	pixelColor;
	ViewPlane	vp(w.vp);
	Ray			ray;
	int 		depth = 0;
	Point2D		sample;
	Point2D 	pp;		// sample point on a pixel
	int n = vp.rootNumSamples;// (int)sqrt((float)vp.numSamples);

	int numPixels = vp.vRes * vp.hRes;

	vp.s /= zoom;
	ray.o = eyePos;


	// Start timer
	startTime = clock();

	// vertical image coord
	for (int r = 0; r < vp.vRes; r++) {
		// horizontal image coord	
		for (int c = 0; c < vp.hRes; c++) {	
			pixelColor = black;

			for (int j = 0; j < vp.numSamples; j++)	
			{
				sample = vp.sampler_ptr->sampleUnitSquare();
				pp.x = vp.s * (c - 0.5f * vp.hRes + sample.x);
				pp.y = vp.s * (r - 0.5f * vp.vRes + sample.y);
				ray.d = getDir(pp);
				pixelColor += w.tracer_ptr->traceRay(ray, depth);
			}

			pixelColor /= (float)vp.numSamples;
			pixelColor *= exposureTime;
			w.displayPixel(r, c, pixelColor);

			// Update interactive timer
			totalTime = ((float)(clock() - startTime)) / CLOCKS_PER_SEC;
			//fprintf(stderr, "\rRender Time: %f s", totalTime);
			
		}
        fprintf(stderr, "\rRendering... %5.2f %%", 100.0 * r/(vp.vRes-1));
	}
	printf("\n");

	// stop clock
	endTime = clock();
	totalTime = ((float)(endTime - startTime)) / CLOCKS_PER_SEC;
	
    std::cout << "\rRender completed in " << totalTime << " s" << std::endl;
}
