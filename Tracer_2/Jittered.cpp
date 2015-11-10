#include "Jittered.h"

// Constructors
Jittered::Jittered()
	: Sampler()
{}

Jittered::Jittered(const int numSamples)
	: Sampler(numSamples) {
	generateSamples();
}

Jittered::Jittered(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {
	generateSamples();
}

Jittered::Jittered(const Jittered& js)
	: Sampler(js) {
	generateSamples();
}

// Assignment operator
Jittered& Jittered::operator= (const Jittered& j) {
	if (this == &j)
		return *this;

	Sampler::operator= (j);

	return *this;
}

// Clone
Jittered* Jittered::clone() const {
	return new Jittered(*this);
}

// Destructor
Jittered::~Jittered() {}


// Generate jittered samples
void Jittered::generateSamples() {
	// Gen n x n samples
	int n = (int)sqrt(numSamples);
	float inverseN = 1.0f / (float)n;

	for (int p = 0; p < numSets; p++){
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				Point2D sp((j + randFloat()) * inverseN, (i + randFloat()) * inverseN);
				samples.push_back(sp);
			}
		}
	}
}

