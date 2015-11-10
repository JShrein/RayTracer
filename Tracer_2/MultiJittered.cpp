#include "MultiJittered.h"

// ---------------------------------------------------------------- default constructor

MultiJittered::MultiJittered()
	: Sampler()
{}


// ---------------------------------------------------------------- constructor

MultiJittered::MultiJittered(const int numSamples)
	: Sampler(numSamples) {
	generateSamples();
}


// ---------------------------------------------------------------- constructor

MultiJittered::MultiJittered(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {
	generateSamples();
}


// ---------------------------------------------------------------- copy constructor

MultiJittered::MultiJittered(const MultiJittered& mjs)
	: Sampler(mjs)
{
	generateSamples();
}

// Assignment operator
MultiJittered& MultiJittered::operator= (const MultiJittered& mj)	{
	if (this == &mj)
		return *this;

	Sampler::operator=(mj);

	return *this;
}

// Clone
MultiJittered* MultiJittered::clone() const {
	return new MultiJittered(*this);
}

// ---------------------------------------------------------------- destructor			

MultiJittered::~MultiJittered() {}


// Shuffle x Coords
void MultiJittered::shuffleXCoords() {
	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < rootNumSamples; i++) {
			for (int j = 0; j < rootNumSamples; j++) {
				int k = (int)(randInt(j, rootNumSamples - 1));
				int srcIdx = i * rootNumSamples + j + p * numSamples;
				int tgtIdx = i * rootNumSamples + k + p * numSamples;

				// Swap
				float t = samples[srcIdx].x;
				samples[srcIdx].x = samples[tgtIdx].x;
				samples[tgtIdx].x = t;
			}
		}
	}
}




// Generate Samples
// K. Chiu, P. Shirley, C. Wang. (1994). Multi-Jittered Sampling. Graphics Gems IV. Academic Press, Inc.
void
MultiJittered::generateSamples() {
	// numSamples = rootNumSamples * rootNumSamples

	//int n = (int)sqrt(numSamples);
	float subcellWidth = 1.0f / ((float)numSamples);

	Point2D fill_point;
	for (int j = 0; j < numSamples * numSets; j++)
		samples.push_back(fill_point);

	// distribute points in the initial patterns

	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < rootNumSamples; i++) {
			for (int j = 0; j < rootNumSamples; j++) {
				int index = i * rootNumSamples + j + p * numSamples;
				samples[index].x = (i * rootNumSamples + j) * subcellWidth + randFloat(0, (int)subcellWidth);
				samples[index].y = (j * rootNumSamples + i) * subcellWidth + randFloat(0, (int)subcellWidth);
			}
		}
	}

	// Shuffle function shuffles over all sets numSets * numSamples without overlap
	// Example numSets = 4, numSamples = 4, rootNumSamples = 2
	// i + rootNumSamples + j + p * numSamples
	// A=[0,1,2,3], B=[4,5,6,7], C=[8,9,10,11], D=[12,13,14,15]
	// p=   0            1            2               3
	// i= 0   1        0   1        0   1          0     1
	// j= 0 1 0 1      0 1 0 1      0 1 0  1       0  1  0  1

	// Shuffled
	// A=[3,0,2,1], B=[6,4,5,7], C=[8,11,10,9], D=[13,15,12,14] 


	// shuffle x coordinates
	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < rootNumSamples; i++) {
			for (int j = 0; j < rootNumSamples; j++) {
				int k = (int)randInt(j, rootNumSamples - 1);
				int srcIdx = i * rootNumSamples + j + p * numSamples;
				int tgtIdx = i * rootNumSamples + k + p * numSamples;
				float t = samples[srcIdx].x;
				samples[srcIdx].x = samples[tgtIdx].x;
				samples[tgtIdx].x = t;
			}
		}
	}

	// shuffle y coordinates
	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < rootNumSamples; i++) {
			for (int j = 0; j < rootNumSamples; j++) {
				int k = (int)randInt(j, rootNumSamples - 1);
				int srcIdx = j * rootNumSamples + i + p * numSamples;
				int tgtIdx = k * rootNumSamples + i + p * numSamples;
				float t = samples[srcIdx].y;
				samples[srcIdx].y = samples[tgtIdx].y;
				samples[tgtIdx].y = t;
			}
		}
	}
}


