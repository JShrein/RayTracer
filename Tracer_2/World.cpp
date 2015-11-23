#include "World.h"
#include "Constants.h"

// Geometric Objects
#include "Plane.h"
#include "Disk.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "OpenCylinder.h"
#include "Box.h"
#include "Triangle.h"
#include "Instance.h"
#include "SolidCylinder.h"

// Materials
#include "Matte.h"
#include "Phong.h"
#include "Reflective.h"

// Lights
//#include "Ambient.h"
//#include "AmbientOccluder.h"
#include "PointLight.h"
#include "Directional.h"

// Tracers
#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "Raycast.h"
#include "Whitted.h"

// Cameras
#include "Pinhole.h"
#include "PinholeMPI.h"

// Utilities
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <sstream>
#include <stdio.h>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;

#define USEWIN 0
#define USEMPI 1

// TODO: Find a better way to do this
// If OS is linux, do the MPI stuff
//void initMPI(int argc, char *argv[]);
//void shutdownMPI();
int rank;
int size;

#if USEMPI
#include <mpi.h>
bool usingMPI = 1;
void initMPI(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
        cout << "MPI sub-system initialized\n";
}

void shutdownMPI()
{
	MPI_Finalize();
}
#else
bool usingMPI = 0;
void initMPI(int argc, char *argv[])
{ }

void shutdownMPI()
{ }
#endif


// Build output file
void writeImage(int width, int height, int rank);
bool file_exists(const string& name);

// Helper functions
void haltBeforeClose();

// Build functions

//#include "BuildRedSphere.cpp"


vector<RGBColor> image;// (0);
vector<RGBColor>::iterator it;

Point3D cameraPosition(0, 200, 500);

// Default Constructor
World::World()
	: backgroundColor(black),
	tracer_ptr(NULL),
	camera_ptr(NULL),
	ambient_ptr(new Ambient)
{ }

// Destructor
World::~World()
{
	if (tracer_ptr)
	{
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	if (camera_ptr)
	{
		delete camera_ptr;
		camera_ptr = NULL;
	}
	if (ambient_ptr)
	{
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
}

// NO LONGER RENDER HERE, RENDER WITH TRACER OBJ
// Render Scene
void World::renderScene() const {
	RGBColor pixelColor;
	Ray ray;
	float zw = 100.0;
	//double x, y;
	Point2D pp;
	rand_seed();

	int n = (int)(sqrt(vp.numSamples));

	//openWindow(vp.hRes, vp.vRes);
	ray.d = Vector3D(0, 0, -1);

	/*
	for (int r = 0; r < vp.vRes; r++)
	{
		for (int c = 0; c < vp.hRes; c++) {
			x = vp.s * (c - vp.hRes/2.0 - 0.5);
			y = vp.s * (r - vp.vRes/2.0 - 0.5);
			ray.o = Point3D(x, y, zw);
			pixelColor = tracer_ptr->traceRay(ray);
			displayPixel(r, c, pixelColor);
		}
	}
	*/
	for (int r = 0; r < vp.vRes; r++)
	{
		for (int c = 0; c < vp.hRes; c++) {
			pixelColor = black;

			// "Trace" a function
			/*
			for (int p = 0; p < vp.numSamples; p++)
			{
				//pp.x = vp.s * (c - 0.5f * vp.hRes + randFloat());
				//pp.y = vp.s * (r - 0.5f * vp.vRes + randFloat());
				pp.x = (c - 0.5f * vp.hRes + randFloat()) * PI / 180;
				pp.y = (r - 0.5f * vp.vRes + randFloat()) * PI / 180;
				//ray.o = Point3D(pp.x, pp.y, zw);
				float z = 1.0f / 2.0f * sin(1 + sin(pp.x*pp.x*pp.y*pp.y));
				//pixelColor += tracer_ptr->traceRay(ray);
				
				pixelColor = RGBColor(z, z, z);
			}
			*/
			// RANDOM SAMPLING NOW DONE THROUGH SAMPLING FRAMEWORK
			// Random sampling
			for (int p = 0; p < vp.numSamples; p++)
			{
				pp.x = vp.s * (c - 0.5f * vp.hRes + randFloat());
				pp.y = vp.s * (r - 0.5f * vp.vRes + randFloat());
				ray.o = Point3D(pp.x, pp.y, zw);
				pixelColor += tracer_ptr->traceRay(ray);
			}
			
			/*
			for (int p = 0; p < n; p++){
				for (int q = 0; q < n; q++){
					pp.x = vp.s * (c - 0.5f * vp.hRes + (q + 0.5f) / n);
					pp.y = vp.s * (r - 0.5f * vp.vRes + (p + 0.5f) / n);
					ray.o = Point3D(pp.x, pp.y, zw);
					pixelColor += tracer_ptr->traceRay(ray);
					
				}
			}
			*/
			pixelColor /= (float)vp.numSamples;
			displayPixel(r, c, pixelColor);
		}
	}

	writeImage(vp.hRes, vp.vRes, rank);
}

// NO LONGER RENDER HERE, RENDER WITH TRACER OBJ
void World::render_perspective() const
{
	RGBColor pixelColor;
	Ray ray;
	Point2D sample;
	Point2D pixelSample;

	float eye = 500.0f; // May need to move in the +-z direction to get a nice perspective

	// TODO: CREATE WINDOW HERE WHEN I CREATE THE GUI - JS

	ray.o = Point3D(0.0, -50.0, 750);
	//ray.d = Vector3D(0, 0, -1);
	for (int r = 0; r < vp.vRes; r++)
	{
		for (int c = 0; c < vp.hRes; c++)
		{
			pixelColor = black;
			for (int j = 0; j < vp.numSamples; j++)
			{
				sample = vp.sampler_ptr->sampleUnitSquare();
				pixelSample.x = vp.s * (c - 0.5f * vp.hRes + sample.x);
				pixelSample.y = vp.s * (r - 0.5f * vp.vRes + sample.y);
				//ray.o = Point3D(pixelSample.x, pixelSample.y, eye);
				ray.d = Vector3D(pixelSample.x, pixelSample.y, -eye);
				/*ray.d = Vector3D(
					vp.s * (c - 0.5 * (vp.hRes - 1.0)),
					vp.s * (r - 0.5 * (vp.vRes - 1.0)),
					eye
					);
				*/
				ray.d.normalize();
				pixelColor += tracer_ptr->traceRay(ray);
				//displayPixel(r, c, pixelColor);
			}
			pixelColor /= (float)vp.numSamples;
			displayPixel(r, c, pixelColor);
		}
	}
	writeImage(vp.hRes, vp.vRes, rank);
}

void World::displayPixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.showOutOfGamut)
		mapped_color = clampToColor(raw_color);
	else
		mapped_color = maxToOne(raw_color);

	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.invGamma);

	int x = column;
	int y = vp.vRes - row - 1;

#if USEMPI
    
    RGBColor c = colorToRange(mapped_color, 255);
    //cout << "rank: " << rank << " sending pixel info to rank 0\n";
	// sendBuf[] = {row, col, red, green, blue};
	int sendBuf[] = { x, y * vp.vRes, (int)c.r, (int)c.g, (int)c.b };

	int succ = MPI_Send(&sendBuf, 5, MPI_INT, 0, 0, MPI_COMM_WORLD);
    
    if(succ != MPI_SUCCESS)
    {
        cout << "ERROR: MPI_Send() failed, retrying...\n";
    }
}
#else
	image[x + y * vp.vRes] = colorToRange(mapped_color, 255);
}
#endif


/*
void World::build()
{
	cout << "Instantiating new Pinhole camera\n";
	Pinhole* pinhole_ptr = new Pinhole();
	pinhole_ptr->setEyePos(0, 200, 800);
	pinhole_ptr->setLookAt(0, 0, 0);
	pinhole_ptr->setDistance(500);
	pinhole_ptr->setRoll(0);
	pinhole_ptr->computeUVW();

	cout << "Setting camera\n";
	setCamera(pinhole_ptr);

	// If using MPI implementation, replace camera with distributed version of cam
	if (usingMPI)
	{
	PinholeMPI* distPinhole_ptr = new PinholeMPI(rank,size);
	distPinhole_ptr->setEyePos(0,200,800);
	distPinhole_ptr->setLookAt(0,0,0);
	distPinhole_ptr->setDistance(500);
	distPinhole_ptr->setRoll(0);
	distPinhole_ptr->computeUVW();
	setCamera(distPinhole_ptr);
	}


	cout << "In build function\n";
	vp.setHres(512);
	vp.setVres(512);
	cout << "Instantiating new sampler\n";
	Sampler* s = new Jittered(25);
	cout << "Sampler built, setting in viewplane\n";
	vp.setSampler(s);
	cout << "Creating image vector\n";
	image = vector<RGBColor>(vp.hRes * vp.vRes);
	cout << "Setting pixel size\n";
	vp.setPixelSize(1.0f);
	//vp.setSamples(25);
	cout << "Setting vp gamma\n";
	vp.setGamma(1.0);

	cout << "Setting ambient light source\n";

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.75);
	setAmbientLight(ambient_ptr);

	backgroundColor = black;

	cout << "Instantiating new tracer_ptr\n";
	tracer_ptr = new RayCast(this);// MultipleObjects(this);



	cout << "Creating new Point Light\n";
	PointLight* pointLight_ptr = new PointLight;
	pointLight_ptr->setPos(200, 200, 200);
	pointLight_ptr->scaleRadiance(0.01f);
	//pointLight_ptr->setColor(1, 0, 0);
	addLight(pointLight_ptr);

	cout << "Creating new Directional Light\n";
	Directional* dirLight_ptr = new Directional;
	dirLight_ptr->setDir(0, 1, 0);
	dirLight_ptr->scaleRadiance(3.0f);
	addLight(dirLight_ptr);


	Matte* matte_ptr = new Matte;
	matte_ptr->setKA(0.25);
	matte_ptr->setKD(0.75);
	matte_ptr->setCD(1, 1, 0);


	// use accessors to set sphere center and radius
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->setCenter(-100, 80, 0);
	sphere_ptr->setRadius(80);
	//sphere_ptr->set_color(1, 0, 0);
	sphere_ptr->setMat(matte_ptr);
	addObject(sphere_ptr);

	matte_ptr = new Matte;
	matte_ptr->setKA(0.25);
	matte_ptr->setKD(0.75);
	matte_ptr->setCD(0, 1, 1);

	Phong* phong_ptr = new Phong;
	phong_ptr->setKA(0.25);
	phong_ptr->setKD(0.75);
	phong_ptr->setKS(0.5);
	phong_ptr->setCD(cyan);
	phong_ptr->setEXP(1000);

	sphere_ptr = new Sphere(Point3D(100, 60, 0), 60);
	//sphere_ptr->set_color(1, 1, 0);
	sphere_ptr->setMat(phong_ptr);
	addObject(sphere_ptr);

	/*
	matte_ptr = new Matte;
	matte_ptr->setKA(0.25f);
	matte_ptr->setKD(0.75f);
	matte_ptr->setCD(0.9f, 0.1f, 0.0f);

	sphere_ptr = new Sphere(Point3D(0, 150, 0), 25);
	//sphere_ptr->set_color(0, 1, 1);
	sphere_ptr->setMat(matte_ptr);
	addObject(sphere_ptr);
	*/
/*
	matte_ptr = new Matte;
	matte_ptr->setKA(0.25f);
	matte_ptr->setKD(0.75f);
	matte_ptr->setCD(0.9f, 0.1f, 0.0f);

	sphere_ptr = new Sphere(Point3D(0, 40, 0), 25);
	//sphere_ptr->set_color(0, 1, 1);
	sphere_ptr->setMat(matte_ptr);
	addObject(sphere_ptr);

	matte_ptr = new Matte;
	matte_ptr->setKA(0.25f);
	matte_ptr->setKD(0.75f);
	matte_ptr->setCD(0.9f, 0.1f, 0.0f);

	Cylinder* cylinder_ptr = new Cylinder(Point3D(0, 0, 0), 25);
	cylinder_ptr->set_yRange(50.0, 75.0);
	cylinder_ptr->setMat(matte_ptr);
	addObject(cylinder_ptr);

	matte_ptr = new Matte;
	matte_ptr->setKA(0.25f);
	matte_ptr->setKD(0.75f);
	matte_ptr->setCD(0.0f, 0.45f, 0.0f);

	Plane* plane_ptr = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
	//plane_ptr->set_color(0.0f, 0.3f, 0.0f);
	plane_ptr->setMat(matte_ptr);
	addObject(plane_ptr);
}
*/

/*
void World::build() 
{    
	int numSamples = 256;

	vp.setHres(512);
	vp.setVres(512);
	vp.setSamples(numSamples);
	image = vector<RGBColor>(vp.hRes * vp.vRes);

	tracer_ptr = new RayCast(this);

	Jittered* sampler_ptr = new Jittered(numSamples);

	image = vector<RGBColor>(vp.hRes * vp.vRes);

	backgroundColor = black;
	tracer_ptr = new RayCast(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.5);
	//setAmbientLight(ambient_ptr);

	AmbientOccluder* occluder_ptr = new AmbientOccluder;
	occluder_ptr->scale_radiance(1.0);
	//occluder_ptr->setColor(white);
	occluder_ptr->setMinAmt(0.0);
	occluder_ptr->setSampler(sampler_ptr);
	setAmbientLight(occluder_ptr);

	PointLight* pointLight_ptr = new PointLight;
	pointLight_ptr->setPos(200, 50, 250);
	pointLight_ptr->scaleRadiance(0.01f);
	pointLight_ptr->attenuate = false;
	pointLight_ptr->p = 2;
	pointLight_ptr->setShadows(true);
	addLight(pointLight_ptr);

	Pinhole* pinhole_ptr = new Pinhole();
	pinhole_ptr->setEyePos(0, 100, 500);
	pinhole_ptr->setLookAt(-5, 0, 0);
	pinhole_ptr->setDistance(850);
	pinhole_ptr->setRoll(0);
	pinhole_ptr->computeUVW();
	setCamera(pinhole_ptr);

	Phong* phong_ptr = new Phong;
	phong_ptr->setKA(0.25);
	phong_ptr->setKD(0.75);
	phong_ptr->setKS(0.2);
	phong_ptr->setCD(gray);
	phong_ptr->setEXP(20);

	Sphere* sphere_ptr = new Sphere(Point3D(50, -22, 15), 10);
	sphere_ptr->setMat(phong_ptr);
	addObject(sphere_ptr);

	phong_ptr = new Phong;
	phong_ptr->setKA(0.25);
	phong_ptr->setKD(0.75);
	phong_ptr->setKS(0.2);
	phong_ptr->setCD(cyan);
	phong_ptr->setEXP(25);

	sphere_ptr = new Sphere(Point3D(10, -5, 0), 27);
	sphere_ptr->setMat(phong_ptr);
	addObject(sphere_ptr);

	phong_ptr = new Phong;
	phong_ptr->setKA(0.25);
	phong_ptr->setKD(0.75);
	phong_ptr->setKS(.1);
	phong_ptr->setCD(red);
	phong_ptr->setEXP(500);

	sphere_ptr = new Sphere(Point3D(-40, -5, -180), 27);
	sphere_ptr->setMat(phong_ptr);
	addObject(sphere_ptr);

	phong_ptr = new Phong;
	phong_ptr->setKA(0.25);
	phong_ptr->setKD(0.75);
	phong_ptr->setKS(.1);
	phong_ptr->setCD(green);
	phong_ptr->setEXP(5);

	Plane* plane_ptr = new Plane(Point3D(0, -32, 0), Normal(0, 1, 0));
	plane_ptr->setMat(phong_ptr);
	addObject(plane_ptr);
}

*/

//void World::build()
//{
//	int numSamples = 256;
//
//	vp.setHres(512);
//	vp.setVres(512);
//	vp.setSamples(numSamples);
//	vp.setMaxDepth(10);
//	image = vector<RGBColor>(vp.hRes * vp.vRes);
//
//	tracer_ptr = new Whitted(this);
//
//	MultiJittered* sampler_ptr = new MultiJittered(numSamples);
//
//	AmbientOccluder* occluder_ptr = new AmbientOccluder;
//	occluder_ptr->scale_radiance(1.0);
//	occluder_ptr->setColor(white);
//	occluder_ptr->setMinAmt(0.0);
//	occluder_ptr->setSampler(sampler_ptr);
//	setAmbientLight(occluder_ptr);
//
//	    
//    if (usingMPI)
//	{
//	    PinholeMPI* distPinhole_ptr = new PinholeMPI(rank,size);
//	    distPinhole_ptr->setEyePos(0,24,56);
//	    distPinhole_ptr->setLookAt(0,1,0);
//	    distPinhole_ptr->setDistance(5000);
//	    distPinhole_ptr->setRoll(0);
//	    distPinhole_ptr->computeUVW();
//	    setCamera(distPinhole_ptr);
//	}
//    else 
//    {
//        Pinhole* pinhole_ptr = new Pinhole();
//	    pinhole_ptr->setEyePos(0, 24, 56);
//	    pinhole_ptr->setLookAt(0, 2, 0);
//	    pinhole_ptr->setDistance(5000);
//	    pinhole_ptr->setRoll(0);
//	    pinhole_ptr->computeUVW();
//	    setCamera(pinhole_ptr);
//    }
//    
//	PointLight* pointLight_ptr = new PointLight;
//	pointLight_ptr->setPos(30, 30, 30);
//	pointLight_ptr->scaleRadiance(0.01f);
//	pointLight_ptr->setAttenuate(false);
//	pointLight_ptr->setAttenPower(2);
//	pointLight_ptr->setShadows(true);
//	addLight(pointLight_ptr);
//
//	/*
//	Phong* matte_ptr = new Phong;
//	matte_ptr->setKA(0.5);
//	matte_ptr->setKD(0.75);
//	matte_ptr->setKS(0.5f);
//	matte_ptr->setEXP(500);
//	matte_ptr->setCD(RGBColor(0.3f, 0.3f, 0.3f));
//	*/
//	/*
//	OpenCylinder* cylinder_ptr = new OpenCylinder(0, 1, 1);
//	cylinder_ptr->setCenter(0, 1, 0);
//	cylinder_ptr->setYRange(0, 4);
//	cylinder_ptr->setMat(matte_ptr);
//	addObject(cylinder_ptr);
//
//	Phong* phong_ptr = new Phong;
//	phong_ptr->setKA(0.5);
//	phong_ptr->setKD(0.75);
//	phong_ptr->setKS(0.1f);
//	phong_ptr->setEXP(500);
//	phong_ptr->setCD(RGBColor(0.4, 0.4, 0.4));
//
//	Box* box_ptr = new Box(-1,-1,-1,1,1,1);
//	box_ptr->setMat(phong_ptr);
//	addObject(box_ptr);
//
//	Sphere* sphere_ptr = new Sphere(Point3D(0, 4.5, 0), 1.25);
//	sphere_ptr->setMat(matte_ptr);
//	addObject(sphere_ptr);
//
//
//	Matte* matte_ptr = new Matte;
//	matte_ptr->setKA(0.75);
//	matte_ptr->setKD(0);
//	matte_ptr->setCD(yellow);
//
//	Cylinder* cylinder_ptr = new Cylinder();
//	cylinder_ptr->setCenter(0, 0, 0);
//	cylinder_ptr->setRadius(1);
//	cylinder_ptr->set_yRange(0, 5);
//	cylinder_ptr->setMat(matte_ptr);
//	addObject(cylinder_ptr);
//
//	Matte* matte_ptr2 = new Matte;
//	matte_ptr2->setKA(0.5);
//	matte_ptr2->setKD(0.75);
//	matte_ptr2->setCD(1.0);
//	*/
//
//	/*
//
//	Reflective* reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.9926f, 0.6784f, 0.6784f));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	Sphere* sphere_ptr = new Sphere(Point3D(0, 1, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(black));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	sphere_ptr = new Sphere(Point3D(2, 1, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.6784f, 0.6784f, 0.9926f));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	sphere_ptr = new Sphere(Point3D(-2, 1, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	Phong* phong_ptr = new Phong;
//	phong_ptr->setKA(0.5);
//	phong_ptr->setKD(0.75);
//	phong_ptr->setKS(0.1f);
//	phong_ptr->setEXP(500);
//	phong_ptr->setCD(RGBColor(0.6784f, 0.9926f, 0.6784f));
//
//	Phong* phong_ptr2 = new Phong;
//	phong_ptr2->setKA(0.25);
//	phong_ptr2->setKD(0.75);
//	phong_ptr2->setKS(0.1f);
//	phong_ptr2->setCD(green);
//	phong_ptr2->setEXP(500);
//
//	Triangle* tri_ptr = new Triangle(Point3D(-1, 1, 0), Point3D(-0.5, 1.5, 2.5), Point3D(1, 0, 1));
//	tri_ptr->setMat(phong_ptr);
//	//addObject(tri_ptr);
//	*/
//	/*
//	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
//	plane_ptr->setMat(phong_ptr2);
//	addObject(plane_ptr);
//	
//
//	Disk* disk_ptr = new Disk(Point3D(0), 3.0, Normal(0, 1, 0));
//	disk_ptr->setMat(phong_ptr2);
//	addObject(disk_ptr);
//	*/
//
//	Reflective* reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.1, 0.1, 0.1));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	//OpenCylinder* cylinder_ptr = new OpenCylinder(0, 1, 0.75);
//	//cylinder_ptr->setCenter(0, 0, -4);
//	//cylinder_ptr->setYRange(0, 3);
//	//cylinder_ptr->setMat(reflective_ptr);
//	//addObject(cylinder_ptr);
//
//	SolidCylinder* solidCylinder_ptr = new SolidCylinder(0, 2, 0.75);
//	solidCylinder_ptr->setMat(reflective_ptr);
//	addObject(solidCylinder_ptr);
//	
//	AABB a = solidCylinder_ptr->getAABB();
//
//	Phong* blackFloorPhong_ptr = new Phong;
//	blackFloorPhong_ptr->setKA(0.5);
//	blackFloorPhong_ptr->setKD(0.75);
//	blackFloorPhong_ptr->setKS(0.1f);
//	blackFloorPhong_ptr->setEXP(500);
//	blackFloorPhong_ptr->setCD(RGBColor(black));
//
//	Phong* whiteFloorPhong_ptr = new Phong;
//	whiteFloorPhong_ptr->setKA(0.5);
//	whiteFloorPhong_ptr->setKD(0.75);
//	whiteFloorPhong_ptr->setKS(0.1f);
//	whiteFloorPhong_ptr->setEXP(500);
//	whiteFloorPhong_ptr->setCD(RGBColor(white));
//	
//	Box* box_ptr;
//
//	for (int i = -20; i < 21; i++)
//	{
//		for (int j = -20; j < 21; j++)
//		{
//			if (i % 2 == 0)
//			{
//				if (j % 2 == 0)
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(blackFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//				else
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(whiteFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//			}
//			else
//			{
//				if (j % 2 == 0)
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(whiteFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//				else
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(blackFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//			}
//		}
//	}
//	
//
//	reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(red));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(1.0);
//
//	Sphere* sphere_ptr = new Sphere(Point3D(0, 3.15, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	//Instance* ellipsoid_ptr = new Instance(new Sphere(Point3D(0,0,-16), 1));
//	//ellipsoid_ptr->setMat(phong_ptr2);
//	//ellipsoid_ptr->scale(2, 3, 1);
//	//ellipsoid_ptr->rotateX(-45.0);
//	//addObject(ellipsoid_ptr);
//
//	reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.4, 0.4, 0.4));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(1.0);
//
//	Normal norm(1, 0, 2);
//
//	Triangle* tri_ptr = new Triangle(Point3D(-4, 0, 1), Point3D(1, 0, -3), Point3D(-1.5, 5.8, -0.5));
//	tri_ptr->setMat(reflective_ptr);
//	addObject(tri_ptr);
//
//	/*
//	Plane* plane_ptr3 = new Plane(Point3D(-1.5, 5, -1.5), norm);
//	plane_ptr3->setMat(reflective_ptr);
//	addObject(plane_ptr3);
//	*/
//}

//void World::build()
//{
//	int numSamples = 16;
//
//	vp.setHres(512);
//	vp.setVres(512);
//	vp.setSamples(numSamples);
//	vp.setMaxDepth(0);
//	image = vector<RGBColor>(vp.hRes * vp.vRes);
//
//	tracer_ptr = new RayCast(this);//new Whitted(this);
//
//	MultiJittered* sampler_ptr = new MultiJittered(numSamples);
//
//	AmbientOccluder* occluder_ptr = new AmbientOccluder;
//	occluder_ptr->scale_radiance(1.0);
//	occluder_ptr->setColor(white);
//	occluder_ptr->setMinAmt(0.0);
//	occluder_ptr->setSampler(sampler_ptr);
//	setAmbientLight(occluder_ptr);
//
//
//	if (usingMPI)
//	{
//		PinholeMPI* distPinhole_ptr = new PinholeMPI(rank, size);
//		distPinhole_ptr->setEyePos(0, 24, 56);
//		distPinhole_ptr->setLookAt(0, 1, 0);
//		distPinhole_ptr->setDistance(5000);
//		distPinhole_ptr->setRoll(0);
//		distPinhole_ptr->computeUVW();
//		setCamera(distPinhole_ptr);
//	}
//	else
//	{
//		Pinhole* pinhole_ptr = new Pinhole();
//		pinhole_ptr->setEyePos(0, 24, 56);
//		pinhole_ptr->setLookAt(0, 2, 0);
//		pinhole_ptr->setDistance(5000);
//		pinhole_ptr->setRoll(0);
//		pinhole_ptr->computeUVW();
//		setCamera(pinhole_ptr);
//	}
//
//	PointLight* pointLight_ptr = new PointLight;
//	pointLight_ptr->setPos(30, 30, 30);
//	pointLight_ptr->scaleRadiance(0.01f);
//	pointLight_ptr->setAttenuate(false);
//	pointLight_ptr->setAttenPower(2);
//	pointLight_ptr->setShadows(true);
//	addLight(pointLight_ptr);
//
//	/*
//	Phong* matte_ptr = new Phong;
//	matte_ptr->setKA(0.5);
//	matte_ptr->setKD(0.75);
//	matte_ptr->setKS(0.5f);
//	matte_ptr->setEXP(500);
//	matte_ptr->setCD(RGBColor(0.3f, 0.3f, 0.3f));
//	*/
//	/*
//	OpenCylinder* cylinder_ptr = new OpenCylinder(0, 1, 1);
//	cylinder_ptr->setCenter(0, 1, 0);
//	cylinder_ptr->setYRange(0, 4);
//	cylinder_ptr->setMat(matte_ptr);
//	addObject(cylinder_ptr);
//
//	Phong* phong_ptr = new Phong;
//	phong_ptr->setKA(0.5);
//	phong_ptr->setKD(0.75);
//	phong_ptr->setKS(0.1f);
//	phong_ptr->setEXP(500);
//	phong_ptr->setCD(RGBColor(0.4, 0.4, 0.4));
//
//	Box* box_ptr = new Box(-1,-1,-1,1,1,1);
//	box_ptr->setMat(phong_ptr);
//	addObject(box_ptr);
//
//	Sphere* sphere_ptr = new Sphere(Point3D(0, 4.5, 0), 1.25);
//	sphere_ptr->setMat(matte_ptr);
//	addObject(sphere_ptr);
//
//
//	Matte* matte_ptr = new Matte;
//	matte_ptr->setKA(0.75);
//	matte_ptr->setKD(0);
//	matte_ptr->setCD(yellow);
//
//	Cylinder* cylinder_ptr = new Cylinder();
//	cylinder_ptr->setCenter(0, 0, 0);
//	cylinder_ptr->setRadius(1);
//	cylinder_ptr->set_yRange(0, 5);
//	cylinder_ptr->setMat(matte_ptr);
//	addObject(cylinder_ptr);
//
//	Matte* matte_ptr2 = new Matte;
//	matte_ptr2->setKA(0.5);
//	matte_ptr2->setKD(0.75);
//	matte_ptr2->setCD(1.0);
//	*/
//
//	/*
//
//	Reflective* reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.9926f, 0.6784f, 0.6784f));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	Sphere* sphere_ptr = new Sphere(Point3D(0, 1, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(black));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	sphere_ptr = new Sphere(Point3D(2, 1, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.6784f, 0.6784f, 0.9926f));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	sphere_ptr = new Sphere(Point3D(-2, 1, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	Phong* phong_ptr = new Phong;
//	phong_ptr->setKA(0.5);
//	phong_ptr->setKD(0.75);
//	phong_ptr->setKS(0.1f);
//	phong_ptr->setEXP(500);
//	phong_ptr->setCD(RGBColor(0.6784f, 0.9926f, 0.6784f));
//
//	Phong* phong_ptr2 = new Phong;
//	phong_ptr2->setKA(0.25);
//	phong_ptr2->setKD(0.75);
//	phong_ptr2->setKS(0.1f);
//	phong_ptr2->setCD(green);
//	phong_ptr2->setEXP(500);
//
//	Triangle* tri_ptr = new Triangle(Point3D(-1, 1, 0), Point3D(-0.5, 1.5, 2.5), Point3D(1, 0, 1));
//	tri_ptr->setMat(phong_ptr);
//	//addObject(tri_ptr);
//	*/
//	/*
//	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
//	plane_ptr->setMat(phong_ptr2);
//	addObject(plane_ptr);
//
//
//	Disk* disk_ptr = new Disk(Point3D(0), 3.0, Normal(0, 1, 0));
//	disk_ptr->setMat(phong_ptr2);
//	addObject(disk_ptr);
//	*/
//
//	Reflective* reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.1, 0.1, 0.1));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(0.75);
//
//	Phong* phong_ptr = new Phong;
//	phong_ptr->setKA(0.5);
//	phong_ptr->setKD(0.75);
//	phong_ptr->setKS(0.1f);
//	phong_ptr->setEXP(500);
//	phong_ptr->setCD(green);
//
//	//OpenCylinder* cylinder_ptr = new OpenCylinder(0, 1, 0.75);
//	//cylinder_ptr->setCenter(0, 0, -4);
//	//cylinder_ptr->setYRange(0, 3);
//	//cylinder_ptr->setMat(reflective_ptr);
//	//addObject(cylinder_ptr);
//
//	//SolidCylinder* solidCylinder_ptr = new SolidCylinder(0, 2, 0.75);
//	//solidCylinder_ptr->setMat(phong_ptr);
//	//addObject(solidCylinder_ptr);
//
//	//AABB a = solidCylinder_ptr->getAABB();
//
//	/*
//	Phong* blackFloorPhong_ptr = new Phong;
//	blackFloorPhong_ptr->setKA(0.5);
//	blackFloorPhong_ptr->setKD(0.75);
//	blackFloorPhong_ptr->setKS(0.1f);
//	blackFloorPhong_ptr->setEXP(500);
//	blackFloorPhong_ptr->setCD(RGBColor(black));
//	
//	Phong* whiteFloorPhong_ptr = new Phong;
//	whiteFloorPhong_ptr->setKA(0.5);
//	whiteFloorPhong_ptr->setKD(0.75);
//	whiteFloorPhong_ptr->setKS(0.1f);
//	whiteFloorPhong_ptr->setEXP(500);
//	whiteFloorPhong_ptr->setCD(RGBColor(white));
//
//	Box* box_ptr;
//
//	for (int i = -20; i < 21; i++)
//	{
//		for (int j = -20; j < 21; j++)
//		{
//			if (i % 2 == 0)
//			{
//				if (j % 2 == 0)
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(blackFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//				else
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(whiteFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//			}
//			else
//			{
//				if (j % 2 == 0)
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(whiteFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//				else
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(blackFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//			}
//		}
//	}
//	*/
//	/*
//	reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(red));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(1.0);
//
//	*/
//
//	/*phong_ptr = new Phong;
//	phong_ptr->setKA(0.5);
//	phong_ptr->setKD(0.75);
//	phong_ptr->setKS(0.1f);
//	phong_ptr->setEXP(500);
//	phong_ptr->setCD(red);
//
//	Sphere* sphere_ptr = new Sphere(Point3D(0, 3.15, 0), 1);
//	sphere_ptr->setMat(phong_ptr);
//	addObject(sphere_ptr);*/
//
//	//Instance* ellipsoid_ptr = new Instance(new Sphere(Point3D(0,0,-16), 1));
//	//ellipsoid_ptr->setMat(phong_ptr2);
//	//ellipsoid_ptr->scale(2, 3, 1);
//	//ellipsoid_ptr->rotateX(-45.0);
//	//addObject(ellipsoid_ptr);
//
//	/*reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(RGBColor(0.4, 0.4, 0.4));
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(1.0);*/
//
//	/*phong_ptr = new Phong;
//	phong_ptr->setKA(0.5);
//	phong_ptr->setKD(0.75);
//	phong_ptr->setKS(0.1f);
//	phong_ptr->setEXP(500);
//	phong_ptr->setCD(blue);
//
//	Normal norm(1, 0, 2);
//
//	Triangle* tri_ptr = new Triangle(Point3D(-4, 0, 1), Point3D(1, 0, -3), Point3D(-1.5, 5.8, -0.5));
//	tri_ptr->setMat(phong_ptr);
//	addObject(tri_ptr);*/
//
//	/*
//	Plane* plane_ptr3 = new Plane(Point3D(-1.5, 5, -1.5), norm);
//	plane_ptr3->setMat(reflective_ptr);
//	addObject(plane_ptr3);
//	*/
//}

//void World::build()
//{
//	int numSamples = 256;
//	
//	vp.setHres(350);
//	vp.setVres(350);
//	vp.setPixelSize(1);
//	vp.setSamples(numSamples);
//	vp.setMaxDepth(0);
//
//	image = vector<RGBColor>(vp.hRes * vp.vRes);
//	
//	tracer_ptr = new RayCast(this);//new Whitted(this);
//	
//	MultiJittered* sampler_ptr = new MultiJittered(numSamples);
//	
//	AmbientOccluder* occluder_ptr = new AmbientOccluder;
//	occluder_ptr->scale_radiance(1.0);
//	occluder_ptr->setColor(white);
//	occluder_ptr->setMinAmt(0.0);
//	occluder_ptr->setSampler(sampler_ptr);
//	occluder_ptr->setShadows(false);
//	setAmbientLight(occluder_ptr);
//
//	PointLight* pointLight_ptr = new PointLight;
//	pointLight_ptr->setPos(100, 100, 30);
//	pointLight_ptr->scaleRadiance(0.009f);
//	pointLight_ptr->setAttenuate(false);
//	pointLight_ptr->setAttenPower(2);
//	pointLight_ptr->setShadows(true);
//	addLight(pointLight_ptr);
//	
//	
//	if (usingMPI)
//	{
//		PinholeMPI* distPinhole_ptr = new PinholeMPI(rank, size);
//		distPinhole_ptr->setEyePos(0, 24, 56);
//		distPinhole_ptr->setLookAt(0, 1, 0);
//		distPinhole_ptr->setDistance(5000);
//		distPinhole_ptr->setRoll(0);
//		distPinhole_ptr->computeUVW();
//		setCamera(distPinhole_ptr);
//	}
//	else
//	{
//		Pinhole* pinhole_ptr = new Pinhole();
//		pinhole_ptr->setEyePos(25, 20, 45);
//		pinhole_ptr->setLookAt(0, 1, 0);
//		pinhole_ptr->setDistance(5000);
//		pinhole_ptr->setRoll(0);
//		pinhole_ptr->computeUVW();
//		setCamera(pinhole_ptr);
//	}
//
//	Reflective* reflective_ptr = new Reflective;
//	reflective_ptr->setKA(0.5);
//	reflective_ptr->setKD(0.75);
//	reflective_ptr->setKS(0.1f);
//	reflective_ptr->setEXP(500);
//	reflective_ptr->setCD(yellow);
//	reflective_ptr->setCR(white);
//	reflective_ptr->setKR(1.0);
//
//	Sphere* sphere_ptr = new Sphere(Point3D(0, 1, 0), 1);
//	sphere_ptr->setMat(reflective_ptr);
//	addObject(sphere_ptr);
//
//	Phong* matte_ptr2 = new Phong;
//	matte_ptr2->setKA(0.75);
//	matte_ptr2->setKD(0);
//	matte_ptr2->setKS(0);
//	matte_ptr2->setEXP(0);
//	matte_ptr2->setCD(cyan);
//
//	Phong* blackFloorPhong_ptr = new Phong;
//	blackFloorPhong_ptr->setKA(0.5);
//	blackFloorPhong_ptr->setKD(0.75);
//	blackFloorPhong_ptr->setKS(0.1f);
//	blackFloorPhong_ptr->setEXP(500);
//	blackFloorPhong_ptr->setCD(RGBColor(black));
//		
//	Phong* whiteFloorPhong_ptr = new Phong;
//	whiteFloorPhong_ptr->setKA(0.5);
//	whiteFloorPhong_ptr->setKD(0.75);
//	whiteFloorPhong_ptr->setKS(0.1f);
//	whiteFloorPhong_ptr->setEXP(500);
//	whiteFloorPhong_ptr->setCD(RGBColor(white));
//	
//	Box* box_ptr;
//	
//	for (int i = -5; i < 6; i++)
//	{
//		for (int j = -5; j < 6; j++)
//		{
//			if (i % 2 == 0)
//			{
//				if (j % 2 == 0)
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(blackFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//				else
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(whiteFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//			}
//			else
//			{
//				if (j % 2 == 0)
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(whiteFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//				else
//				{
//					box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
//					box_ptr->setMat(blackFloorPhong_ptr);
//					addObject(box_ptr);
//				}
//			}
//		}
//	}
//}



void World::build()
{
    int numSamples = 256;

    vp.setHres(512);
    vp.setVres(512);
    vp.setPixelSize(1);
    vp.setSamples(numSamples);
    vp.setMaxDepth(10);

    image = vector<RGBColor>(vp.hRes * vp.vRes);

    tracer_ptr = new Whitted(this);

    MultiJittered* sampler_ptr = new MultiJittered(numSamples);

    AmbientOccluder* occluder_ptr = new AmbientOccluder;
    occluder_ptr->scale_radiance(1.0);
    occluder_ptr->setColor(white);
    occluder_ptr->setMinAmt(0.0);
    occluder_ptr->setSampler(sampler_ptr);
    occluder_ptr->setShadows(false);
    setAmbientLight(occluder_ptr);

    PointLight* pointLight_ptr = new PointLight;
    pointLight_ptr->setPos(100, 100, 30);
    pointLight_ptr->scaleRadiance(0.009f);
    pointLight_ptr->setAttenuate(false);
    pointLight_ptr->setAttenPower(2);
    pointLight_ptr->setShadows(true);
    addLight(pointLight_ptr);


    if (usingMPI)
    {
        PinholeMPI* distPinhole_ptr = new PinholeMPI(rank, size);
        distPinhole_ptr->setEyePos(0, 24, 56);
        distPinhole_ptr->setLookAt(0, 1, 0);
        distPinhole_ptr->setDistance(5000);
        distPinhole_ptr->setRoll(0);
        distPinhole_ptr->computeUVW();
        setCamera(distPinhole_ptr);
    }
    else
    {
        Pinhole* pinhole_ptr = new Pinhole();
        pinhole_ptr->setEyePos(0, 24, 56);
        pinhole_ptr->setLookAt(0, 1, 0);
        pinhole_ptr->setDistance(5000);
        pinhole_ptr->setRoll(0);
        pinhole_ptr->computeUVW();
        setCamera(pinhole_ptr);
    }

    Reflective* reflective_ptr = new Reflective;
    reflective_ptr->setKA(0.5);
    reflective_ptr->setKD(0.75);
    reflective_ptr->setKS(0.1f);
    reflective_ptr->setEXP(500);
    reflective_ptr->setCD(yellow);
    reflective_ptr->setCR(white);
    reflective_ptr->setKR(1.0);

    Sphere* sphere_ptr = new Sphere(Point3D(0, 1, 0), 1);
    sphere_ptr->setMat(reflective_ptr);
    addObject(sphere_ptr);

    Phong* matte_ptr2 = new Phong;
    matte_ptr2->setKA(0.75);
    matte_ptr2->setKD(0);
    matte_ptr2->setKS(0);
    matte_ptr2->setEXP(0);
    matte_ptr2->setCD(cyan);

    Phong* blackFloorPhong_ptr = new Phong;
    blackFloorPhong_ptr->setKA(0.5);
    blackFloorPhong_ptr->setKD(0.75);
    blackFloorPhong_ptr->setKS(0.1f);
    blackFloorPhong_ptr->setEXP(500);
    blackFloorPhong_ptr->setCD(RGBColor(black));

    Phong* whiteFloorPhong_ptr = new Phong;
    whiteFloorPhong_ptr->setKA(0.5);
    whiteFloorPhong_ptr->setKD(0.75);
    whiteFloorPhong_ptr->setKS(0.1f);
    whiteFloorPhong_ptr->setEXP(500);
    whiteFloorPhong_ptr->setCD(RGBColor(white));

    
    Box* box_ptr;

    for (int i = -5; i < 6; i++)
    {
        for (int j = -5; j < 6; j++)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0)
                {
                    box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
                    box_ptr->setMat(blackFloorPhong_ptr);
                    addObject(box_ptr);
                }
                else
                {
                    box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
                    box_ptr->setMat(whiteFloorPhong_ptr);
                    addObject(box_ptr);
                }
            }
            else
            {
                if (j % 2 == 0)
                {
                    box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
                    box_ptr->setMat(whiteFloorPhong_ptr);
                    addObject(box_ptr);
                }
                else
                {
                    box_ptr = new Box(Point3D(i, -1, j), Point3D(i + 1, 0, j + 1));
                    box_ptr->setMat(blackFloorPhong_ptr);
                    addObject(box_ptr);
                }
            }
        }
    }
}



ShadeRec World::hitObjects(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	Normal normal;
	Point3D localHitPoint;
	double tMin = kHugeValue;
	int numObjects = objects.size();

	for (int i = 0; i < numObjects; i++)
	{
		if (objects[i]->hit(ray, t, sr) && (t < tMin))
		{
			sr.hitAnObject = true;
			tMin = t;
			sr.mat_ptr = objects[i]->getMat();
			sr.hitPoint = ray.o + t * ray.d;
			normal = sr.normal;
			localHitPoint = sr.localHitPoint;
		}
		if (sr.hitAnObject)
		{
			sr.t = tMin;
			sr.normal = normal;
			sr.localHitPoint = localHitPoint;
		}
	}
	return sr;
}

void World::openWindow(const int hRes, const int vRes) const
{

}

RGBColor World::maxToOne(const RGBColor& c) const {
	float max_value = (float)max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return c / max_value;
	else
		return c;
}

RGBColor World::clampToColor(const RGBColor& raw_color) const {
	RGBColor c(raw_color);

	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0;
		c.g = 0.0;
		c.b = 0.0;
	}
	return c;
}

RGBColor World::colorToRange(const RGBColor& c, int max) const {
	return ((float)max) * RGBColor(c);
}

int main()
{
	// Note*** initMPI() and shutdownMPI() are simply defined as empty functions in Windows
	// MPI_Init(NULL, NULL);

	// MPI_Init() wrapped up in this function to facilitate multi-platform development
	initMPI(NULL, NULL);
	World w;
	w.build();
#if USEMPI
    // cout << "Rank " << rank << " reports build complete, rendering scene\n";
#endif
    //w.renderScene();
	//w.render_perspective();
    const int NUM_IMAGES = 145;

    double angle = 2.5;
	//double translationAmt = 0;
	for (int j = 0; j < NUM_IMAGES; j++)
	{

	//	translationAmt++;
	//	Instance* box = (Instance*)w.objects[0];

	//	if (i < 80)
	//	{
	//		box->translate(0, 0, 0.25);
	//	}
	//	else
	//	{
	//		box->translate(0, 0, -0.25);
	//	}

		//Point3D lightPos = w.lights[0]->getPos();

		//double rx = lightPos.x * cos(toRads(angle)) - lightPos.z * sin(toRads(angle));
		//double rz = lightPos.x * sin(toRads(angle)) + lightPos.z * cos(toRads(angle));

		//cameraPosition.x = rx;
		//cameraPosition.z = rz;

		//w.camera_ptr->setEyePos(cameraPosition);
		//w.camera_ptr->setLookAt(0, 0, 0);
		
		//w.lights[0]->setPos(rx, lightPos.y, rz);
		
#if USEMPI
        int totalNumPixels = w.vp.hRes * w.vp.vRes;

		if(rank == 0)
        {
			MPI_Status status;
			int inBuf[5];

            int received = 0;
			for (int i = 0; i < totalNumPixels; i++)
			{
                int succ = MPI_Recv(&inBuf, 5, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
				
                if (succ != MPI_SUCCESS)
                {
                    cout << "ERROR: MPI_Recv() failed\n";
                }
                
                image[inBuf[0] + inBuf[1]] = RGBColor(inBuf[2], inBuf[3], inBuf[4]);
            }
            cout << "Writing image " << j << " of " << NUM_IMAGES << "\n";      
            writeImage(w.vp.hRes, w.vp.vRes, rank);//w.rank);
        }
		else
		{
			w.camera_ptr->renderScene(w);
		}

#else
        
        w.camera_ptr->renderScene(w);
        writeImage(w.vp.hRes, w.vp.vRes, rank);
#endif
    }

	// MPI_Finalize() wrapped in shutdownMPI()
	shutdownMPI();

    if(USEWIN)
    {
	    haltBeforeClose();
    }

	return 0;
}


void writeImage(int width, int height, int rank)
{
    cout << "Rank: " << rank << " is writing an image\n";
	std::ofstream imageFile;
	std::stringstream ss;

	string fileName;
	string location = "./output/";
	string filePrefix = "multipleObj";
	int fileNum = rank;//0;
	string extension = ".ppm";

	do
	{
		ss << location << filePrefix << fileNum++ << extension;

		fileName = ss.str();
		ss.str(string());

	} while (file_exists(fileName));

	imageFile.open(fileName);

	imageFile << "P3\n";
	imageFile << "# RedSphere.ppm\n";
	imageFile << width << " " << height << "\n";
	imageFile << "255\n";

	for (unsigned int i = 0; i < image.size(); i++)
	{
		imageFile << " " << image[i].r << " " << image[i].g << " " << image[i].b << "\n";
	}

	imageFile.close();
}


bool file_exists(const string& name)
{
	struct stat buf;
	return stat(name.c_str(), &buf) == 0;
}


void haltBeforeClose()
{
	std::cin.sync();
	std::cin.ignore();
}
