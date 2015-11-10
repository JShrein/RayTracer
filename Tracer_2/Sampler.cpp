#include <algorithm>

#include "Constants.h"
#include "Sampler.h"

// Constructors
Sampler::Sampler()
	: rootNumSamples(1),
	  numSamples(1),
	  numSets(101), // Default 101 sets, nice prime number
	  count(0),
	  jump(0) {
	  samples.reserve(numSamples * numSets);
	  setupShuffledIndices();
}

Sampler::Sampler(const int ns)
	: numSamples(ns),
	  numSets(101), // Default 101
	  count(0),
	  jump(0) 
{
	rootNumSamples = (int)sqrt(ns);
	samples.reserve(numSamples * numSets);
	setupShuffledIndices();
}


// ------------------------------------------------------------------ constructor

Sampler::Sampler(const int ns, const int nSets)
	: numSamples(ns),
	  numSets(nSets),
	  count(0),
	  jump(0)

{
	rootNumSamples = (int)sqrt(ns);
	samples.reserve(numSamples * numSets);
	setupShuffledIndices();
}


// ------------------------------------------------------------------ copy constructor

Sampler::Sampler(const Sampler& s)
	: rootNumSamples(s.rootNumSamples),
	  numSamples(s.numSamples),
	  numSets(s.numSets),
	  samples(s.samples),
	  shuffledIndices(s.shuffledIndices),
	  diskSamples(s.diskSamples),
	  hemisphereSamples(s.hemisphereSamples),
	  sphereSamples(s.sphereSamples),
	  count(s.count),
	  jump(s.jump)
{ }


// ------------------------------------------------------------------ assignment operator

Sampler& Sampler::operator= (const Sampler& s)	{
	if (this == &s)
		return *this;

	rootNumSamples = s.rootNumSamples;
	numSamples = s.numSamples;
	numSets = s.numSets;
	samples = s.samples;
	shuffledIndices = s.shuffledIndices;
	diskSamples = s.diskSamples;
	hemisphereSamples = s.hemisphereSamples;
	sphereSamples = s.sphereSamples;
	count = s.count;
	jump = s.jump;

	return *this;
}

Sampler::~Sampler() {}


// Set number of sets (of samples)
void Sampler::setNumSets(const int np) {
	numSets = np;
}


// get number of samples
int Sampler::getNumSamples() {
	return numSamples;
}

int Sampler::getRootNumSamples() {
	return rootNumSamples;
}

// Shuffle x coords
// shuffle the x coordinates of the points within each set
void Sampler::shuffleXCoords() {
	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < numSamples - 1; i++) {
			int setRange = p * numSamples;						// Specific set of samples out of entire vector
			int target = randInt() % numSamples + setRange;	// swap target
			int srcIdx = i + setRange + 1;						// swap source

			// Swap
			float temp = samples[srcIdx].x;
			samples[srcIdx].x = samples[target].x;
			samples[target].x = temp;
		}
	}
}


// Shuffle y coords
// shuffle the y coordinates of the points within set
void Sampler::shuffleYCoords() {
	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < numSamples - 1; i++) {
			int setRange = p * numSamples;						// Specific set of samples out of entire vector
			int target = randInt() % numSamples + setRange;	// swap target
			int srcIdx = i + setRange + 1;						// swap source

			// Swap
			float temp = samples[srcIdx].y;
			samples[srcIdx].y = samples[target].y;
			samples[target].y = temp;
		}
	}
}


// Setup shuffled indices
// sets up randomly shuffled indices for the samples array
void Sampler::setupShuffledIndices() {
	shuffledIndices.reserve(numSamples * numSets);
	vector<int> indices;

	for (int j = 0; j < numSamples; j++)
		indices.push_back(j);

	for (int p = 0; p < numSets; p++) {
		random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < numSamples; j++)
			shuffledIndices.push_back(indices[j]);
	}
}


// Map samples to unit disk
// Maps the 2D sample points in the square [-1,1] X [-1,1] to a unit disk
// [x] P. Shirley, K. Chiu. (1997). A Low Distortion Map Between Disk and Square. 
void Sampler::mapSamplesToUnitDisk() {
	int size = samples.size();
	float r, phi;		// polar coordinates
	Point2D sp; 		// sample point on unit disk

	diskSamples.reserve(size);

	for (int j = 0; j < size; j++) {
		// map sample point to [-1, 1] X [-1,1]
		sp.x = 2.0f * samples[j].x - 1.0f;
		sp.y = 2.0f * samples[j].y - 1.0f;

		if (sp.x > -sp.y) {			// sectors 1 and 2
			if (sp.x > sp.y) {		// sector 1
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {					// sector 2
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else {						// sectors 3 and 4
			if (sp.x < sp.y) {		// sector 3
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else {					// sector 4
				r = -sp.y;
				if (sp.y != 0.0)	// avoid division by zero at origin
					phi = 6 - sp.x / sp.y;
				else
					phi = 0.0f;
			}
		}

		phi *= (float)(PI / 4.0);

		diskSamples[j].x = r * cos(phi);
		diskSamples[j].y = r * sin(phi);
	}

	samples.erase(samples.begin(), samples.end());
}


// Map samples to hemisphere
// Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power
// density distribution in the polar angle
void Sampler::mapSamplesToHemisphere(const float exp) {
	int size = samples.size();
	hemisphereSamples.reserve(numSamples * numSets);

	for (int j = 0; j < size; j++) {
		float cos_phi = (float)cos(2.0 * PI * samples[j].x);
		float sin_phi = (float)sin(2.0 * PI * samples[j].x);
		float cos_theta = pow((1.0f - samples[j].y), 1.0f / (exp + 1.0f));
		float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;
		hemisphereSamples.push_back(Point3D(pu, pv, pw));
	}
}


// Map samples to sphere
// Maps the 2D sample points to 3D points on a unit sphere with a uniform density 
// distribution over the surface
// this is used for modelling a spherical light
void Sampler::mapSamplesToSphere() {
	float r1, r2;
	float x, y, z;
	float r, phi;

	sphereSamples.reserve(numSamples * numSets);

	for (int j = 0; j < numSamples * numSets; j++) {
		r1 = samples[j].x;
		r2 = samples[j].y;
		z = 1.0f - 2.0f * r1;
		r = sqrt(1.0f - z * z);
		phi = (float)(TWO_PI * r2);
		x = r * cos(phi);
		y = r * sin(phi);
		sphereSamples.push_back(Point3D(x, y, z));
	}
}


// Sample unit square
Point2D Sampler::sampleUnitSquare() {
	if (count % numSamples == 0)  									// start of a new pixel
		jump = (randInt() % numSets) * numSamples;				// random index jump initialised to zero in constructor

	return samples[jump + shuffledIndices[jump + count++ % numSamples]];
}

// Sample unit disk
Point2D Sampler::sampleUnitDisk() {
	if (count % numSamples == 0)  									// start of a new pixel
		jump = (randInt() % numSets) * numSamples;

	return diskSamples[jump + shuffledIndices[jump + count++ % numSamples]];
}

// Sample hemisphere
Point3D Sampler::sampleHemisphere() {
	if (count % numSamples == 0)  									// start of a new pixel
		jump = (randInt() % numSets) * numSamples;

	return hemisphereSamples[jump + shuffledIndices[jump + count++ % numSamples]];
}

// Sample sphere
Point3D Sampler::sampleSphere() {
	if (count % numSamples == 0)  									// start of a new pixel
		jump = (randInt() % numSets) * numSamples;

	return sphereSamples[jump + shuffledIndices[jump + count++ % numSamples]];
}



// Sample one set
// This is a specialised function called in LatticeNoise::init_vector_table
// DON'T SHUFFLE
Point2D Sampler::sampleOneSet() {
	return samples[count++ % numSamples];
}