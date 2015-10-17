#ifndef __ORTHOGRAPHIC__
#define __ORTHOGRAPHIC__

#include "Camera.h"

class Orthographic : public Camera
{
public:
	virtual void renderScene(World& w);

};

#endif // __ORTHOGRAPHIC__