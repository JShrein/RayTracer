#include "Camera.h"
#include "Matrix.h"
#include "Maths.h"
#include <cmath>

// Declare static transformation matrix
Matrix Camera::transformation;

Camera::Camera()
	: eyePos(0, 0, 500),
	  lookAt(0, 0, 0),
	  up(0, 1, 0),
	  u(1, 0, 0),
	  v(0, 1, 0),
	  w(0, 0, 1),
	  exposureTime(1.0),
      inverseMat()
{
	transformation.setIdentity();
}

Camera::Camera(Point3D eye, Point3D look)
	: eyePos(eye),
	  lookAt(look),
	  up(0, 1, 0),
	  u(1, 0, 0),
	  v(0, 1, 0),
	  w(0, 0, 1),
      exposureTime(1.0),
      inverseMat()
{
	transformation.setIdentity();
}

Camera::Camera(const Camera& c)
	: eyePos(c.eyePos),
	  lookAt(c.lookAt),
	  up(c.up),
	  u(c.u),
	  v(c.v),
	  w(c.w),
	  exposureTime(1.0),
      inverseMat(c.inverseMat)
{
	transformation.setIdentity();
}


Camera& Camera::operator=(const Camera& cam)
{
	if (this == &cam)
		return *this;
	eyePos = cam.eyePos;
	lookAt = cam.lookAt;
	roll = cam.roll;
	u = cam.u;
	v = cam.v;
	w = cam.w;
	exposureTime = cam.exposureTime;
    inverseMat = cam.inverseMat;

	return *this;
}

Camera::~Camera()
{ }


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


// Translation
void Camera::translate(const Vector3D& trans)
{
	Matrix invTranslationMat;

	invTranslationMat.m[0][3] = -trans.x;
	invTranslationMat.m[1][3] = -trans.y;
	invTranslationMat.m[2][3] = -trans.z;

	inverseMat = inverseMat * invTranslationMat;

	Matrix translationMat;					// temporary translation matrix	

	translationMat.m[0][3] = trans.x;
	translationMat.m[1][3] = trans.y;
	translationMat.m[2][3] = trans.z;

	transformation = translationMat * transformation;
}


// Translation
void Camera::translate(const double dx, const double dy, const double dz)
{
	Matrix invTranslationMat;	

	invTranslationMat.m[0][3] = -dx;
	invTranslationMat.m[1][3] = -dy;
	invTranslationMat.m[2][3] = -dz;

	inverseMat = inverseMat * invTranslationMat;

	Matrix translationMat;

	translationMat.m[0][3] = dx;
	translationMat.m[1][3] = dy;
	translationMat.m[2][3] = dz;

	transformation = translationMat * transformation;
}

// Rotate about x-axis
void Camera::rotateX(const double angle)
{
	double sinAngle = sin(angle * PI_ON_180);
	double cosAngle = cos(angle * PI_ON_180);

	Matrix invXRotMat;

	invXRotMat.m[1][1] = cosAngle;
	invXRotMat.m[1][2] = sinAngle;
	invXRotMat.m[2][1] = -sinAngle;
	invXRotMat.m[2][2] = cosAngle;

	inverseMat = inverseMat * invXRotMat;

	Matrix xRotMat;

	xRotMat.m[1][1] = cosAngle;
	xRotMat.m[1][2] = -sinAngle;
	xRotMat.m[2][1] = sinAngle;
	xRotMat.m[2][2] = cosAngle;

	transformation = xRotMat * transformation;
}

// Rotate about y-axis
void Camera::rotateY(const double angle)
{
	double sinAngle = sin(angle * PI / 180.0);
	double cosAngle = cos(angle * PI / 180.0);

	Matrix invYRotMat;

	invYRotMat.m[0][0] = cosAngle;
	invYRotMat.m[0][2] = -sinAngle;
	invYRotMat.m[2][0] = sinAngle;
	invYRotMat.m[2][2] = cosAngle;

	inverseMat = inverseMat * invYRotMat;

	Matrix yRotMat;

	yRotMat.m[0][0] = cosAngle;
	yRotMat.m[0][2] = sinAngle;
	yRotMat.m[2][0] = -sinAngle;
	yRotMat.m[2][2] = cosAngle;

	transformation = yRotMat * transformation;
}

// Rotate about z-axis
void Camera::rotateZ(const double angle)
{
	double sinAngle = sin(angle * PI / 180.0);
	double cosAngle = cos(angle * PI / 180.0);

	Matrix invZRotMat;

	invZRotMat.m[0][0] = cosAngle;
	invZRotMat.m[0][1] = sinAngle;
	invZRotMat.m[1][0] = -sinAngle;
	invZRotMat.m[1][1] = cosAngle;

	inverseMat = inverseMat * invZRotMat;

	Matrix zRotMat;

	zRotMat.m[0][0] = cosAngle;
	zRotMat.m[0][1] = -sinAngle;
	zRotMat.m[1][0] = sinAngle;
	zRotMat.m[1][1] = cosAngle;

	transformation = zRotMat * transformation;
}
