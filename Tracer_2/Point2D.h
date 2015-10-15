#ifndef __POINT_2D__
#define __POINT_2D__

class Point2D {
public:
	float x, y;

public:
	Point2D(void);										// default constructor
	Point2D(const float arg);							// constructor
	Point2D(const float x1, const float y1);			// constructor
	Point2D(const Point2D& p); 							// copy constructor
	~Point2D(void) {}									// destructor

	Point2D& operator= (const Point2D& rhs);			// assignment operator
	Point2D operator* (const float a);					// multiplication on right by scalar
};


// scales the point by the float a

inline Point2D Point2D::operator* (const float a) {
	return (Point2D(a * x, a * y));
}


#endif
