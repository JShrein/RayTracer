#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.h"
#include "ShadeRec.h"
#include "RGBColor.h"

class Light
{
public:
	Light();
	Light(const Light& light);
	Light& operator= (const Light& light);

	// Clone
	virtual Light* clone() const = 0;
	
	//Destructor
	virtual ~Light();
	
	virtual Vector3D getDir(ShadeRec& sr) = 0;
	virtual RGBColor L(ShadeRec& sr);
protected:
	bool shadows;
};

#endif // __LIGHT__
