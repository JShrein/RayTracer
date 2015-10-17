#ifndef __PINHOLE__
#define __PINHOLE__

#include "Camera.h"

class Pinhole : public Camera
{
public:
	virtual void renderScene(World& w);

};

#endif // __PINHOLE__