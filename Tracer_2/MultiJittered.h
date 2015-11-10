#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__

#include "Sampler.h"

class MultiJittered : public Sampler {
public:
	// Ctor
	MultiJittered();
	MultiJittered(const int numSamples);
	MultiJittered(const int numSamples, const int numSets);
	MultiJittered(const MultiJittered& mjs);

	// Assignment op
	MultiJittered& operator= (const MultiJittered& mj);

	virtual MultiJittered* clone() const;
	void shuffleXCoords();

	// Dtor
	virtual ~MultiJittered();
private:
	virtual void generateSamples();
};

#endif // __MULTI_JITTERED__

