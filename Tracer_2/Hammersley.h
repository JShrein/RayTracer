#ifndef __HAMMERSLEY__
#define __HAMMERSLEY__

#include "Sampler.h"

class Hammersley : public Sampler {
public:
	// Ctors
	Hammersley();
	Hammersley(const int numSamples);
	Hammersley(const Hammersley& r);
	
	// Assignment op
	Hammersley& operator= (const Hammersley& h);

	virtual Hammersley* clone() const;

	// Dtor
	virtual ~Hammersley();

	double phi(int j);
private:
	virtual void generateSamples();
};

#endif // __HAMMERSLEY__

