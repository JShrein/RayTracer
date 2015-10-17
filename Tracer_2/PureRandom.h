#ifndef __PURE_RANDOM__
#define __PURE_RANDOM__

#include "Sampler.h"

class PureRandom : public Sampler {
public:
	// Ctors
	PureRandom();
	PureRandom(const int numSamples);
	PureRandom(const PureRandom& r);

	// Assign op
	PureRandom& operator= (const PureRandom& rhs);

	virtual PureRandom* clone() const;

	// Dtor
	virtual ~PureRandom();
private:
	virtual void generateSamples();
};

#endif