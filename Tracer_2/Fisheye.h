#ifndef __FISHEYE__
#define __FISHEYE__

#include "Camera.h"

class Fisheye : public Camera
{
public:
	virtual void renderScene(World& w);

};

#endif // __FISHEYE__