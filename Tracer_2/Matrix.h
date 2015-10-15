#ifndef __MATRIX__
#define __MATRIX__

class Matrix {
public:
	double m[4][4];

	Matrix();
	Matrix(const Matrix& mat);
	~Matrix();

	Matrix& operator=(const Matrix& mat);
	
	Matrix operator*(const Matrix& mat) const;
	Matrix operator/(const double c);
	void set_identity();
};

#endif // __MATRIX__