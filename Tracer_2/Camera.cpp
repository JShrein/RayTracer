#include "Camera.h"
#include "Matrix.h"
#include "Maths.h"
#include <cmath>

Camera::Camera()
	: eyePos(0, 0, 500),
	  lookAt(0, 0, 0),
	  up(0, 1, 0),
	  u(1, 0, 0),
	  v(0, 1, 0),
	  w(0, 0, 1),
	  exposureTime(1.0)
{ }

Camera::Camera(Point3D eye, Point3D look)
	: eyePos(eye),
	  lookAt(look),
	  up(0, 1, 0),
	  u(1, 0, 0),
	  v(0, 1, 0),
	  w(0, 0, 1),
	  exposureTime(1.0)
{ }

Camera::Camera(const Camera& c)
	: eyePos(c.eyePos),
	  lookAt(c.lookAt),
	  up(c.up),
	  u(c.u),
	  v(c.v),
	  w(c.w),
	  exposureTime(1.0)
{ }

Camera& Camera::operator=(const Camera& rhs)
{
	if (this == &rhs)
		return *this;
	eyePos = rhs.eyePos;
	lookAt = rhs.lookAt;
	roll = rhs.roll;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;
	exposureTime = rhs.exposureTime;

	return *this;
}

Camera::~Camera()
{ }

void Camera::setRoll(const float rollAngle)
{
	roll = rollAngle;
}

void Camera::computeUVW()
{
	Vector3D upRotated(0, 0, 0);
	double rollAngle = toRads(-roll);
	upRotated.x = up.x * cos(rollAngle) - up.y * sin(rollAngle);
	upRotated.y = up.x * sin(rollAngle) + up.y * cos(rollAngle);
	upRotated.z = up.z;

	up = upRotated;

	w = eyePos - lookAt;
	w.normalize();
	u = up ^ w;
	u.normalize();
	v = w ^ u;

	// Looking down y axis
	if (eyePos.x == lookAt.x && eyePos.z == lookAt.z && eyePos.y > lookAt.y)
	{
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}

	// Looking up y axis
	if (eyePos.x == lookAt.x && eyePos.z == lookAt.z && eyePos.y < lookAt.y)
	{
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}