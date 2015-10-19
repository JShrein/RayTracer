#include "PureRandom.h"

// Constructors
PureRandom::PureRandom()
	: Sampler()
{ }

PureRandom::PureRandom(const int numSamples)
	: Sampler(numSamples) {
	generateSamples();
}

PureRandom::PureRandom(const PureRandom& r)
	: Sampler(r) {
	generateSamples();
}

// Assignment Operator
PureRandom& PureRandom::operator= (const PureRandom& rhs) {
	if (this == &rhs)
		return *this;

	Sampler::operator=(rhs);

	return *this;
}

// Clone
PureRandom* PureRandom::clone() const {
	return new PureRandom(*this);
}

// Destructor
PureRandom::~PureRandom() {}


// Generate purely random samples
void PureRandom::generateSamples(void) {
	for (int p = 0; p < numSets; p++)
		for (int q = 0; q < numSamples; q++)
			samples.push_back(Point2D(randFloat(), randFloat()));
}


