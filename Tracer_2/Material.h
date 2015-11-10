#ifndef MATERIAL_H
#define MATERIAL_H

#include "World.h"
#include "RGBColor.h"
#include "ShadeRec.h"

class Material {
public:

	Material();
	Material(const Material& material);

	virtual Material* clone() const = 0;

	virtual ~Material();

	virtual RGBColor shade(ShadeRec& sr);
	//virtual RGBColor shadeAreaLight(ShadeRec& sr);
	//virtual RGBColor shadeWhitted(ShadeRec& sr);
	//virtual RGBColor shadePath(ShadeRec& sr);

protected:
	Material& operator= (const Material& mat);
};

#endif // MATERIAL_H
