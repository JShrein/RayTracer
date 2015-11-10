#ifndef __SAMPLER__
#define __SAMPLER__

#include <vector>
#include <cmath>

#include "Point2D.h"
#include "Point3D.h"
#include "Maths.h"

using std::vector;

class Sampler 
{
public:
	// Constructors
	Sampler();
	Sampler(const int numSamples);
	Sampler(const int numSamples, const int numSets);
	Sampler(const Sampler& s);

	// Assignment operator
	Sampler& operator=(const Sampler& s);

	// Clone
	virtual Sampler* clone() const = 0;
	
	// Destructor
	virtual ~Sampler();

	// Setters/Getters
	void setNumSets(const int np);
	int getNumSamples();
	int getRootNumSamples();

	void shuffleXCoords();
	void shuffleYCoords();
	void setupShuffledIndices();
	void shuffleSamples();

	virtual void generateSamples() = 0;

	void mapSamplesToUnitDisk();
	void mapSamplesToHemisphere(const float p);
	void mapSamplesToSphere();
	
	Point2D sampleUnitSquare();
	Point2D sampleUnitDisk();
	Point3D sampleHemisphere();
	Point3D sampleSphere();
	Point2D sampleOneSet();
protected:
	int rootNumSamples; // rootNumSamples * rootNumSamples = numSamples
	int numSamples; // rootNumSamples^2
	int numSets; // We store multiple sets of samples
	vector<int> shuffledIndices;
	vector<Point2D> samples;
	vector<Point2D> diskSamples;
	vector<Point3D> hemisphereSamples;
	vector<Point3D> sphereSamples;
	unsigned long count;
	int jump;
};

#endif // __SAMPLER__