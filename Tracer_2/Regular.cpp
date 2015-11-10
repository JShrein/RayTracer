#include "Regular.h"

// Constructors
Regular::Regular()
	: Sampler()
{ }

Regular::Regular(const int numSamples)
	: Sampler(numSamples)
{
	generateSamples();
}

Regular::Regular(const Regular& u)
	: Sampler(u)
{
	generateSamples();
}

// Assignment operator
Regular& Regular::operator= (const Regular& reg)	{
	if (this == &reg)
		return *this;

	Sampler::operator= (reg);

	return *this;
}

// Clone
Regular* Regular::clone() const {
	return new Regular(*this);
}

// Destructor
Regular::~Regular() {}


// Generate regular samples
void Regular::generateSamples() {
	//int n = (int)sqrt((float)numSamples); // Stored at class level now as rootNumSamples
	float invRootNumSamples = 1.0f / (float)rootNumSamples;
	for (int j = 0; j < numSets; j++)
		for (int p = 0; p < rootNumSamples; p++)
			for (int q = 0; q < rootNumSamples; q++)
				samples.push_back(Point2D((q + 0.5f) * invRootNumSamples, (p + 0.5f) * invRootNumSamples));
}