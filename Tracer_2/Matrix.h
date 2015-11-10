#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	double m[4][4];

	Matrix();
	Matrix(const Matrix& mat);
	~Matrix();

	Matrix& operator=(const Matrix& mat);
	
	Matrix operator*(const Matrix& mat) const;
	Matrix operator/(const double c);
	void setIdentity();
};

#endif // MATRIX_H
