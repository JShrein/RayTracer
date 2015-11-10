#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "Phong.h"
#include "PerfectSpecular.h"

class Reflective : public Phong 
{
public:
	Reflective();
	Reflective(const Reflective& rm);
	~Reflective(void);

	Reflective& operator= (const Reflective& r);
	virtual Reflective* clone() const;

	void setKR(const float k);
	void setCR(const RGBColor& c);
	void setCR(const float r, const float g, const float b);
	void setCR(const float c);

	virtual RGBColor shade(ShadeRec& s);

private:
	PerfectSpecular* reflectiveBRDF;
};


// set reflection coefficient

inline void 
Reflective::setKR(const float k) {
	reflectiveBRDF->setKR(k);
}


// set color

inline void  Reflective::setCR(const RGBColor& c) {
	reflectiveBRDF->setCR(c);

}


// set color
inline void Reflective::setCR(const float r, const float g, const float b) {
	reflectiveBRDF->setCR(r, g, b);
}


// set color
inline void Reflective::setCR(const float c)
{
	reflectiveBRDF->setCR(c);
}

#endif // REFLECTIVE_H