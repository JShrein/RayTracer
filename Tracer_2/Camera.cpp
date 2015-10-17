#include "Camera.h"

Camera::Camera()
	: eyePos(0, 0, 500),
	  lookAt(0),
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

void Camera::computeUVW()
{
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