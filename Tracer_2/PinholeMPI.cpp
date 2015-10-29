#include "Constants.h"
#include "PinholeMPI.h"


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
	// num rendering blocks = 16
	// block size = (2imageSize / MPISize)^2 (assuming square image for now)
	int blockSize = w.vp.hres / (size/4); // 512 / 16 = 32, 32*32 block size


	// for now, vertical and horizontal render range
	int vStart = rank/4 * blockSize;
	int vEnd = rank/4 * blockSize + blockSize;
    int hStart = rank % 4 * blockSize;
    int hEnd = rank%4 * blockSize + blockSize;;

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
	for (int r = vStart; r < vEnd; r++) {
		// horizontal image coord	
		for (int c = hStart; c < hEnd; c++) {
			pixelColor = black;
                
            for (int j = 0; j < vp.numSamples; j++)	
            {
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
