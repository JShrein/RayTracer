#ifndef __N_ROOKS__
#define __N_ROOKS__

#include "Sampler.h"

class NRooks : public Sampler {
public:
	// Ctors
	NRooks();
	NRooks(const int numSamples);
	NRooks(const int numSamples, const int numSets);
	NRooks(const NRooks& nr);

	// Assign op
	NRooks& operator= (const NRooks& rook);

	virtual NRooks* clone() const;

	// Dtor
	virtual ~NRooks();
private:
	virtual void generateSamples();
};

#endif // __N_ROOKS__

