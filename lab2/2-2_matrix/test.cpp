#include "Matrix.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#include "r8mat_expm1.h"


int main(int argc, char const *argv[])
{

	int dim = 5;

	// Matrix m(4, 3);
	// Matrix eye = Matrix::eye(3);
	// Matrix a(3,3);
	// double x[4] = {1,2,3,4};
	// m.fillMatrix(x, 2,2, 1,1);


	// eye = m;
	// eye = Matrix::eye(dim);
	// eye.printMatrix();
	// Matrix e = eye.exp();
	// e.printMatrix();

	double* exp;
	// exp = r8mat_expm1 ( dim, eye.transpose().getArray() );
	Matrix res(dim);
	// res.fillMatrix(exp, dim, dim, 0, 0);
	// printf("Difference exp: %f\n", (e-res.transpose()).norm());


	Matrix mat = Matrix::random(dim);
	printf("Matrix:\n");
	mat.printMatrix();

	// Matrix res(dim);
	printf("Matrix.exp()\n");
	mat.exp().printMatrix();
	printf("r8mat_expm1\n");
	exp = r8mat_expm1 ( dim, mat.transpose().getArray() );
	res.fillMatrix(exp, dim, dim, 0, 0);
	res.transpose().printMatrix();
	printf("Difference exp: %f\n", (mat.exp()-res.transpose()).norm());

	return 0;
}