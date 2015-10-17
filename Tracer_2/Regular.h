#ifndef __REGULAR__
#define __REGULAR__

#include "Sampler.h"

class Regular : public Sampler {
public:
	//Ctors
	Regular();
	Regular(const int numSamples);
	Regular(const Regular& u);

	// Assign op
	Regular& operator= (const Regular& rhs);

	virtual Regular* clone() const;

	// Dtor
	virtual ~Regular();
private:
	virtual void generateSamples();
};

#endif

