#include "Matrix.h"

Matrix::Matrix()
{
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4; j++) 
			if (i == j)
				m[i][j] = 1.0;
			else
				m[i][j] = 0.0;
}

Matrix::Matrix(const Matrix& mat)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
				m[i][j] = mat.m[i][j];
}

Matrix::~Matrix()
{ }

Matrix& Matrix::operator=(const Matrix& mat)
{
	if (this == &mat)
		return *this;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = mat.m[i][j];

	return *this;
}

Matrix Matrix::operator*(const Matrix& mat) const
{
	Matrix product;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			double sum = 0.0;

			for (int k = 0; k < 4; k++)
			{
				sum += mat.m[j][k] * mat.m[k][i];
			}
			product.m[j][i] = sum;
		}
	}

	return product;
}

Matrix Matrix::operator/(const double c)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = m[i][j] / c;
		}
	}

	return *this;
}

void Matrix::set_identity()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j)
				m[i][j] = 1.0;
			else
				m[i][j] = 0.0;
}
