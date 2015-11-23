#include "Constants.h"
#include "PinholeMPI.h"
#include <ctime>
#include <iostream>


PinholeMPI::PinholeMPI(int _rank, int _size)
	: Camera(),
	d(500),
	zoom(1.0),
	rank(_rank),
	size(_size)
{ }

PinholeMPI::PinholeMPI(const Point3D& eye, const Point3D& look, int _rank, int _size)
	: Camera(eye, look),
	d(500),
	zoom(1.0),
	rank(_rank),
	size(_size)
{ }

PinholeMPI::PinholeMPI(const Point3D& eye, const Point3D& look, const float dist, int _rank, int _size)
	: Camera(eye, look),
	d(dist),
	zoom(1.0),
	rank(_rank),
	size(_size)
{ }

PinholeMPI::PinholeMPI(const Point3D& eye, const Point3D& look, const float dist, const float zf, int _rank, int _size)
	: Camera(eye, look),
	d(dist),
	zoom(zf),
	rank(_rank),
	size(_size)
{ }

PinholeMPI::PinholeMPI(const PinholeMPI& p)
	: Camera(p),
	d(p.d),
	zoom(p.zoom),
	rank(p.rank),
	size(p.size)
{ }

Camera* PinholeMPI::clone() const
{
	return new PinholeMPI(*this);
}

PinholeMPI& PinholeMPI::operator=(const PinholeMPI& p)
{
	if (this == &p)
		return *this;

	Camera::operator=(p);
	d = p.d;
	zoom = p.zoom;
	rank = p.rank;
	size = p.size;

	return *this;
}

PinholeMPI::~PinholeMPI()
{ }

// Setters/Getters
Vector3D PinholeMPI::getDir(const Point2D& p) const
{
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();

	return dir;
}

void PinholeMPI::renderScene(World& w)
{
	int pixelsToRender = w.vp.hRes * w.vp.vRes;

	// Each process will render this number of pixels
	int pixelsPerProcess = pixelsToRender / (size - 1);
	// head node renders remaining pixels (possibly [0..pixlesToRender-1] to render)
	int remainderPixels = pixelsToRender % (size - 1);

	for (int i = 0; i < remainderPixels; i++)
	{
		pixelsPerProcess++;
	}

	// Whatever rank I am, I start here
	int start = rank * pixelsPerProcess;
	// and I end here
	int end = rank * pixelsPerProcess + pixelsPerProcess;

	// Need to translate start & end to 2D range
	int vStart = start / w.vp.hRes;
	int hStart = start % w.vp.hRes;
	int vEnd = end / w.vp.hRes;
	int hEnd = end % w.vp.hRes;

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

	vp.s /= zoom;
	ray.o = eyePos;

	// Start timer
	startTime = clock();

	// vertical image coord
	for (int r = vStart; r < vEnd; r++) {
		// horizontal image coord	
		for (int c = hStart; c < hEnd; c++) {
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
		}
	}

	// stop clock
	endTime = clock();
	totalTime = ((float)(endTime - startTime)) / CLOCKS_PER_SEC;

	std::cout << "Rank: " << rank << " reports render completed in " << totalTime << " ms" << std::endl;
}
