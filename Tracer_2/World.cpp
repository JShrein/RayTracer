#include "World.h"
#include "Constants.h"

// Geometric Objects

#include "Sphere.h"
#include "Plane.h"
#include "MultipleObjects.h"

// Tracers

#include "SingleSphere.h"

// Utilities

#include "Vector3D.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Ray.h"


//#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <sstream>

using std::vector;
using std::cout;
using std::endl;
using std::string;

// Build output file
void writeImage(int width, int height);
bool file_exists(const string& name);

// Build functions

//#include "BuildRedSphere.cpp"


vector<RGBColor> image;// (0);
vector<RGBColor>::iterator it;

// Default Constructor
World::World()
	: background_color(black),
	tracer_ptr(NULL)
{ }

// Destructor
World::~World()
{
	if (tracer_ptr)
	{
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
}

// Render Scene
void World::render_scene() const {
	RGBColor pixel_color;
	Ray ray;
	float zw = 100.0;
	//double x, y;
	Point2D pp;
	rand_seed();

	int n = (int)(sqrt(vp.num_samples));

	//open_window(vp.hres, vp.vres);
	ray.d = Vector3D(0, 0, -1);

	/*
	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++) {
			x = vp.s * (c - vp.hres/2.0 - 0.5);
			y = vp.s * (r - vp.vres/2.0 - 0.5);
			ray.o = Point3D(x, y, zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}
	}
	*/
	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++) {
			pixel_color = black;

			// "Trace" a function
			/*
			for (int p = 0; p < vp.num_samples; p++)
			{
				//pp.x = vp.s * (c - 0.5f * vp.hres + rand_float());
				//pp.y = vp.s * (r - 0.5f * vp.vres + rand_float());
				pp.x = (c - 0.5f * vp.hres + rand_float()) * PI / 180;
				pp.y = (r - 0.5f * vp.vres + rand_float()) * PI / 180;
				//ray.o = Point3D(pp.x, pp.y, zw);
				float z = 1.0f / 2.0f * sin(1 + sin(pp.x*pp.x*pp.y*pp.y));
				//pixel_color += tracer_ptr->trace_ray(ray);
				
				pixel_color = RGBColor(z, z, z);
			}
			*/
			
			// Random sampling
			for (int p = 0; p < vp.num_samples; p++)
			{
				pp.x = vp.s * (c - 0.5f * vp.hres + rand_float());
				pp.y = vp.s * (r - 0.5f * vp.vres + rand_float());
				ray.o = Point3D(pp.x, pp.y, zw);
				pixel_color += tracer_ptr->trace_ray(ray);
			}
			
			/*
			for (int p = 0; p < n; p++){
				for (int q = 0; q < n; q++){
					pp.x = vp.s * (c - 0.5f * vp.hres + (q + 0.5f) / n);
					pp.y = vp.s * (r - 0.5f * vp.vres + (p + 0.5f) / n);
					ray.o = Point3D(pp.x, pp.y, zw);
					pixel_color += tracer_ptr->trace_ray(ray);
					
				}
			}
			*/
			pixel_color /= vp.num_samples;
			display_pixel(r, c, pixel_color);
		}
	}

	writeImage(vp.hres, vp.vres);
}

void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	mapped_color = max_to_one(raw_color);

	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);

	int x = column;
	int y = vp.vres - row - 1;

	//it = image.begin();
	/*
	if (image.size() == 20000)
	{
		cout << "r = " << mapped_color.r << ", b = " << mapped_color.b << ", g = " << mapped_color.g << endl;
	}
	*/
	//image.insert(it, color_to_range(mapped_color, 255));
	//image.push_back(color_to_range(mapped_color, 255));
	image[x + y * vp.vres] = color_to_range(mapped_color, 255);
}

// Hit objects
/*
void World::build() {
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	background_color = black;
	tracer_ptr = new SingleSphere(this);

	sphere.set_center(0.0);
	sphere.set_radius(165.0);
}
*/

void World::build() {
	vp.set_hres(400);
	vp.set_vres(400);
	image = vector<RGBColor>(vp.hres * vp.vres);
	vp.set_pixel_size(1.0);
	vp.set_samples(100);
	vp.set_gamma(1.0);

	background_color = black;
	tracer_ptr = new MultipleObjects(this);

	// use accessors to set sphere center and radius
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80);
	sphere_ptr->set_color(1, 0, 0);
	add_object(sphere_ptr);

	sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr->set_color(1, 1, 0);
	add_object(sphere_ptr);

	sphere_ptr = new Sphere(Point3D(-30, 30, 0), 90);
	sphere_ptr->set_color(0, 1, 1);
	add_object(sphere_ptr);

	Plane* plane_ptr = new Plane(Point3D(0, 0, 0), Normal(0, 1, 1));
	plane_ptr->set_color(0.0f, 0.3f, 0.0f);
	add_object(plane_ptr);
}

ShadeRec World::hit_bare_bones_object(const Ray& ray) {
	ShadeRec sr(*this);
	double t;
	double tmin = kHugeValue;
	int num_objects = objects.size();

	for (int i = 0; i < num_objects; i++)
	{
		if (objects[i]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[i]->get_color();
		}
	}

	return sr;
}

void World::open_window(const int hres, const int vres) const
{

}

RGBColor World::max_to_one(const RGBColor& c) const {
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return c / max_value;
	else
		return c;
}

RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);

	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0;
		c.g = 0.0;
		c.b = 0.0;
	}
	return c;
}

RGBColor World::color_to_range(const RGBColor& c, int max) const {
	return max * RGBColor(c);
}


int main()
{
	World w;
	w.build();
	w.render_scene();

	return 0;
}


void writeImage(int width, int height)
{
	std::ofstream imageFile;
	std::stringstream ss;

	string fileName;
	string location = "./output/";
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
	return (stat(name.c_str(), &buf) == 0);
}
