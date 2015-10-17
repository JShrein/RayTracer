#ifndef __N_ROOKS__
#define __N_ROOKS__

#include "Sampler.h"

class NRooks : public Sampler {
public:
	// Ctors
	NRooks(void);
	NRooks(const int numSamples);
	NRooks(const int numSamples, const int numSets);
	NRooks(const NRooks& nr);

	// Assign op
	NRooks& operator= (const NRooks& rhs);

	virtual NRooks* clone(void) const;

	// Dtor
	virtual ~NRooks(void);
private:
	virtual void generateSamples(void);
};

#endif // __N_ROOKS__

