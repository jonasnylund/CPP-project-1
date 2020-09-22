#include "stdio.h"
#include "math.h"

double func(double x);
double I1(double(*const f)(double),double x0, double x1);
double I2(double(*const f)(double),double x0, double x1);

double ASI(double (*const f)(double), const double a, const double b);
double ASI(double (*const f)(double), const double a, const double b, const double tol);


int main(int argc, char const *argv[])
{
	
	int n = atoi(argv[1]);
	double tol = pow(10, -n);
	printf("Tolerance: %f\n", tol);
	printf("%f\n", ASI(func, -1, 1, tol));

	return 0;
}


double func(double x){
	return 1 + sin(exp(3*x));
}

double I1(double (*const f)(double), const double x0, const double x1){
	return (x1-x0)/6 * (f(x0) + 4*f((x0+x1)/2) + f(x1));
}

double I2(double (*const f)(double), const double x0, const double x1){
	return I1(f, x0, (x0+x1)/2) + I1(f, (x0+x1)/2, x1);
}

double ASI(double (*const f)(double), const double a, const double b){
	return ASI(f,a,b,1e-4);
}

double ASI(double (*const f)(double), const double a, const double b, const double tol){

	double i1 = I1(f,a,b);
	double i2 = I2(f,a,b);

	if(fabs(i1-i2) < 15*tol)
		return i2;

	return ASI(f, a, (a+b)/2, tol/2) + ASI(f, (a+b)/2, b, tol/2);
}