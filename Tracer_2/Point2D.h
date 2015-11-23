#ifndef POINT2D_H
#define POINT2D_H

class Point2D {
public:
	float x, y;

public:
	// Constructors/Destructor
	Point2D();
	Point2D(const float arg);
	Point2D(const float x1, const float y1);
	Point2D(const Point2D& p);
	~Point2D() {}

	// operator overloads
	Point2D& operator= (const Point2D& p);
	Point2D operator* (const float a);
};


// Point * scalar
inline Point2D Point2D::operator* (const float a) 
{
	return Point2D(a * x, a * y);
}


#endif // POINT2D_H
