#include "Hammersley.h"
#include "Maths.h"

// Constructors
Hammersley::Hammersley()
	: Sampler()
{}

Hammersley::Hammersley(const int numSamples)
	: Sampler(numSamples) {
	generateSamples();
}

Hammersley::Hammersley(const Hammersley& h)
	: Sampler(h) {
	generateSamples();
}

// Assignment operator
Hammersley& Hammersley::operator= (const Hammersley& h) {
	if (this == &h)
		return *this;

	Sampler::operator=(h);

	return *this;
}

// Clone
Hammersley* Hammersley::clone() const {
	return new Hammersley(*this);
}

// Destructor
Hammersley::~Hammersley() 
{ }


// Calculate PHI
double Hammersley::phi(int j) {
	double x = 0.0;
	double f = 0.5;

	while (j) {
		x += f * (double)(j % 2);
		j /= 2;
		f *= 0.5;
	}

	return (x);
}

// Generate Samples override
void Hammersley::generateSamples() {
	for (int p = 0; p < numSets; p++) {
		for (int j = 0; j < numSamples; j++) {
			Point2D pv((float)j / (float)numSamples, (float)phi(j));
			samples.push_back(pv);
		}
	}
}