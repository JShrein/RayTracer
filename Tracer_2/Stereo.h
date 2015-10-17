#ifndef __STEREO__
#define __STEREO__

#include "Camera.h"

class Stereo : public Camera
{
public:
	virtual void renderScene(World& w);

};

#endif // __STEREO__