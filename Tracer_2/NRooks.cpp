#include "NRooks.h"

// Constructorificationizer
NRooks::NRooks()
	: Sampler()
{ }

NRooks::NRooks(const int numSamples)
	: Sampler(numSamples) {
	generateSamples();
}

NRooks::NRooks(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {
	generateSamples();
}

NRooks::NRooks(const NRooks& nr)
	: Sampler(nr) {
	generateSamples();
}

// Ass op
NRooks& NRooks::operator= (const NRooks& rook) {
	if (this == &rook)
		return *this;

	Sampler::operator=(rook);

	return *this;
}

// Attack of the clone (singular)
NRooks* NRooks::clone() const {
	return new NRooks(*this);
}

// Destructorificationator		
NRooks::~NRooks()
{ }

// Generate Samples
void NRooks::generateSamples() {
	float invNumSamples = 1.0f / (float)numSamples;
	for (int p = 0; p < numSets; p++) {
		for (int j = 0; j < numSamples; j++) {
			Point2D sp((j + randFloat()) * invNumSamples, (j + randFloat()) * invNumSamples);
			samples.push_back(sp);
		}
	}

	shuffleXCoords();
	shuffleYCoords();
}