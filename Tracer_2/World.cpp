#include "World.h"
#include "Constants.h"

// Geometric Objects
#include "Plane.h"
#include "Sphere.h"

// Materials
#include "Matte.h"

// Lights
#include "Ambient.h"
#include "Point.h"
#include "Directional.h"

// Tracers
#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "Raycast.h"

// Cameras
#include "Pinhole.h"

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

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;

// Build output file
void writeImage(int width, int height);
bool file_exists(const string& name);

// Build functions

//#include "BuildRedSphere.cpp"


vector<RGBColor> image;// (0);
vector<RGBColor>::iterator it;

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
}

// NO LONGER RENDER HERE, RENDER WITH CAMERA OBJECT (USE PINHOLE)
// Render Scene
void World::renderScene() const {
	RGBColor pixelColor;
	Ray ray;
	float zw = 100.0;
	//double x, y;
	Point2D pp;
	rand_seed();

	int n = (int)(sqrt(vp.numSamples));

	//openWindow(vp.hres, vp.vres);
	ray.d = Vector3D(0, 0, -1);

	/*
	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++) {
			x = vp.s * (c - vp.hres/2.0 - 0.5);
			y = vp.s * (r - vp.vres/2.0 - 0.5);
			ray.o = Point3D(x, y, zw);
			pixelColor = tracer_ptr->traceRay(ray);
			displayPixel(r, c, pixelColor);
		}
	}
	*/
	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++) {
			pixelColor = black;

			// "Trace" a function
			/*
			for (int p = 0; p < vp.numSamples; p++)
			{
				//pp.x = vp.s * (c - 0.5f * vp.hres + randFloat());
				//pp.y = vp.s * (r - 0.5f * vp.vres + randFloat());
				pp.x = (c - 0.5f * vp.hres + randFloat()) * PI / 180;
				pp.y = (r - 0.5f * vp.vres + randFloat()) * PI / 180;
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
				pp.x = vp.s * (c - 0.5f * vp.hres + randFloat());
				pp.y = vp.s * (r - 0.5f * vp.vres + randFloat());
				ray.o = Point3D(pp.x, pp.y, zw);
				pixelColor += tracer_ptr->traceRay(ray);
			}
			
			/*
			for (int p = 0; p < n; p++){
				for (int q = 0; q < n; q++){
					pp.x = vp.s * (c - 0.5f * vp.hres + (q + 0.5f) / n);
					pp.y = vp.s * (r - 0.5f * vp.vres + (p + 0.5f) / n);
					ray.o = Point3D(pp.x, pp.y, zw);
					pixelColor += tracer_ptr->traceRay(ray);
					
				}
			}
			*/
			pixelColor /= (float)vp.numSamples;
			displayPixel(r, c, pixelColor);
		}
	}

	writeImage(vp.hres, vp.vres);
}

// NO LONGER RENDER HERE, RENDER WITH CAMERA OBJECT (USE PINHOLE)
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
	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++)
		{
			pixelColor = black;
			for (int j = 0; j < vp.numSamples; j++)
			{
				sample = vp.sampler_ptr->sampleUnitSquare();
				pixelSample.x = vp.s * (c - 0.5f * vp.hres + sample.x);
				pixelSample.y = vp.s * (r - 0.5f * vp.vres + sample.y);
				//ray.o = Point3D(pixelSample.x, pixelSample.y, eye);
				ray.d = Vector3D(pixelSample.x, pixelSample.y, -eye);
				/*ray.d = Vector3D(
					vp.s * (c - 0.5 * (vp.hres - 1.0)),
					vp.s * (r - 0.5 * (vp.vres - 1.0)),
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
	writeImage(vp.hres, vp.vres);
}

void World::displayPixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;
	
	if (vp.show_out_of_gamut)
		mapped_color = clampToColor(raw_color);
	else
		mapped_color = maxToOne(raw_color);

	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);

	int x = column;
	int y = vp.vres - row - 1;

	// THIS IS MEGA SLOW, DON'T DO IT!!!
	//it = image.begin();
	/*
	if (image.size() == 20000)
	{
		cout << "r = " << mapped_color.r << ", b = " << mapped_color.b << ", g = " << mapped_color.g << endl;
	}
	*/
	//image.insert(it, colorToRange(mapped_color, 255));
	//image.push_back(colorToRange(mapped_color, 255));

	// THIS IS MUCH FASTER 
	image[x + y * vp.vres] = colorToRange(mapped_color, 255);
}

// Hit objects
/*
void World::build() {
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	backgroundColor = black;
	tracer_ptr = new SingleSphere(this);

	sphere.set_center(0.0);
	sphere.set_radius(165.0);
}
*/


void World::build() {
    cout << "In build function\n";
	vp.set_hres(512);
	vp.set_vres(512);
    cout << "Instantiating new sampler\n";
	Sampler* s = new Jittered(25); 
    cout << "Sampler built, setting in viewplane\n";
    vp.setSampler(s);
	cout << "Creating image vector\n";
    image = vector<RGBColor>(vp.hres * vp.vres);
    cout << "Setting pixel size\n";
	vp.set_pixel_size(1.0f);
	//vp.set_samples(25);
    cout << "Setting vp gamma\n";
	vp.set_gamma(1.0);

    cout << "Setting ambient light source\n";
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.75);
	setAmbientLight(ambient_ptr);

	backgroundColor = black;

    cout << "Instantiating new tracer_ptr\n";
	tracer_ptr = new RayCast(this);// MultipleObjects(this);

    cout << "Instantiating new Pinhole camera\n";
	Pinhole* pinhole_ptr = new Pinhole();
	pinhole_ptr->setEyePos(0, 200, 1000);
	pinhole_ptr->setLookAt(0, 0, 0);
	pinhole_ptr->setDistance(750);
	pinhole_ptr->setRoll(0);
	pinhole_ptr->computeUVW();

    cout << "Setting camera\n";
	setCamera(pinhole_ptr);

    cout << "Creating new Point Light\n";
	Point* pointLight_ptr = new Point;
	pointLight_ptr->setPos(0, 100, 50);
	pointLight_ptr->scaleRadiance(2.0);
	pointLight_ptr->setColor(1, 1, 1);
	addLight(pointLight_ptr);

	cout << "Creating new Directional Light\n";
	Directional* dirLight_ptr = new Directional;
	dirLight_ptr->setDir(0, 1, 0);
	dirLight_ptr->scaleRadiance(3.0);
	addLight(dirLight_ptr);
	

	Matte* matte_ptr = new Matte;
	matte_ptr->setKA(0.25);
	matte_ptr->setKD(0.75);
	matte_ptr->setCD(1, 1, 0);


	// use accessors to set sphere center and radius
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(-100, 80, 0);
	sphere_ptr->set_radius(80);
	//sphere_ptr->set_color(1, 0, 0);
	sphere_ptr->setMat(matte_ptr);
	addObject(sphere_ptr);

	matte_ptr = new Matte;
	matte_ptr->setKA(0.25);
	matte_ptr->setKD(0.75);
	matte_ptr->setCD(0, 1, 1);

	sphere_ptr = new Sphere(Point3D(100, 60, 0), 60);
	//sphere_ptr->set_color(1, 1, 0);
	sphere_ptr->setMat(matte_ptr);
	addObject(sphere_ptr);

	matte_ptr = new Matte;
	matte_ptr->setKA(0.25);
	matte_ptr->setKD(0.75);
	matte_ptr->setCD(0.68, 0.45, 0.75);

	sphere_ptr = new Sphere(Point3D(70, 90, 0), 90);
	//sphere_ptr->set_color(0, 1, 1);
	sphere_ptr->setMat(matte_ptr);
	//addObject(sphere_ptr);

	matte_ptr = new Matte;
	matte_ptr->setKA(0.25);
	matte_ptr->setKD(0.75);
	matte_ptr->setCD(0, 0.45, 0);

	Plane* plane_ptr = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
	//plane_ptr->set_color(0.0f, 0.3f, 0.0f);
	plane_ptr->setMat(matte_ptr);
	addObject(plane_ptr);
}

ShadeRec World::hitBareBonesObject(const Ray& ray) {
	ShadeRec sr(*this);
	double t;
	double tmin = kHugeValue;
	int num_objects = objects.size();

	for (int i = 0; i < num_objects; i++)
	{
		if (objects[i]->hit(ray, t, sr) && (t < tmin)) {
			sr.hitAnObject = true;
			tmin = t;
			sr.color = objects[i]->get_color();
		}
	}

	return sr;
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
			sr.hit_point = ray.o + t * ray.d;
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

void World::openWindow(const int hres, const int vres) const
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
	World w;
    cout << "Created world object, entering build function\n";
	w.build();
    cout << "Build complete, rendering scene\n";
	//w.renderScene();
	//w.render_perspective();
	w.camera_ptr->renderScene(w);
    cout << "Scene rendered, writing to file\n";
	writeImage(w.vp.hres, w.vp.vres);
    cout << "Write to file complete, shutting down\n";

	return 0;
}


void writeImage(int width, int height)
{
	std::ofstream imageFile;
	std::stringstream ss;

	string fileName;
	string location = "../output/";
	string filePrefix = "multipleObj";
	int fileNum = 0;
	string extension = ".ppm";

	do
	{
		ss << location << filePrefix << fileNum++ << extension;

		fileName = ss.str();
		ss.str(string());

	} while (file_exists(fileName));

	imageFile.open(fileName);

	imageFile << "P3\n";
	imageFile << "# SpheresAndPlanes.ppm\n";
	imageFile << width << " " << height << "\n";
	imageFile << "255\n";

	for (unsigned int i = 0; i < image.size(); i++)
	{
		imageFile << " " << image[i].r << " " << image[i].g << " " << image[i].b << "\n";
	}

	imageFile.close();
    cout << "Image file closed\n";
}


bool file_exists(const string& name)
{
	struct stat buf;
	return (stat(name.c_str(), &buf) == 0);
}
