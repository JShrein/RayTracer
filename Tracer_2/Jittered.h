#ifndef __JITTERED__
#define __JITTERED__

#include "Sampler.h"

class Jittered : public Sampler {
public:
	Jittered();
	Jittered(const int numSamples);
	Jittered(const int numSamples, const int m);
	Jittered(const Jittered& u);
	Jittered& operator= (const Jittered& j);

	virtual Jittered* clone() const;
	virtual ~Jittered();
private:
	virtual void generateSamples();
};

#endif // __JITTERED__