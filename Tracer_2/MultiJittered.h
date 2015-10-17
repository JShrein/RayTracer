#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__

#include "Sampler.h"

class MultiJittered : public Sampler {
public:
	// Ctor
	MultiJittered(void);
	MultiJittered(const int numSamples);
	MultiJittered(const int numSamples, const int numSets);
	MultiJittered(const MultiJittered& mjs);

	// Assignment op
	MultiJittered& operator= (const MultiJittered& rhs);

	virtual MultiJittered* clone(void) const;
	void shuffleXCoords();

	// Dtor
	virtual ~MultiJittered(void);
private:
	virtual void generateSamples(void);
};

#endif // __MULTI_JITTERED__

