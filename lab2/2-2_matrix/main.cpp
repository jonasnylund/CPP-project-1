#include "Matrix.hpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;
#include "r8mat_expm1.h"


int main(int argc, char const *argv[])
{

	srand(time(0));
	int dim = 5;

	double* exp;
	Matrix res(dim);

	Matrix mat = Matrix::random(dim);
	mat.print();

	printf("Matrix.exp()\n");
	mat.exp().print();
	printf("r8mat_expm1\n");
	exp = r8mat_expm1 ( dim, mat.transpose().getArray() );
	res.fillMatrix(exp, dim, dim, 0, 0);
	res.transpose().print();
	Matrix diff = mat.exp()-res.transpose();
	printf("Norm diff exp: %f\n", diff.norm());
	diff.print();

	return 0;
}