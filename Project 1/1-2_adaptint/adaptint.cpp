#include <cmath>
#include <iostream>

double func(const double &x);
double I2(double (*const f)(const double&),
	const double &x0,
	const double &x1);

double I1(double (*const f)(const double&),
	const double &x0,
	const double &x1);

double ASI(double (*const f)(const double&),
	const double &a,
	const double &b,
	const double &tol);


int main(int argc, char const *argv[])
{
	double true_val = 2.5008091103361667; // from WolframAlpha	
	int tol_powers[] = {-2, -3, -4};
	
	for (int tol_power : tol_powers) {
		double tol = pow(10, tol_power);
		double res = ASI(func, -1, 1, tol);
		printf("Tolerance: %f\n", tol);
		printf("Result: %f\n", res);
		printf("Error: %f\n", fabs(res - true_val));
		printf("--------------\n");
	}

	return 0;
}


double func(const double &x){
	return 1 + sin(exp(3*x));
}

double I1(double (*const f)(const double&),
	const double &x0,
	const double &x1){
	return (x1-x0)/6 * (f(x0) + 4*f((x0+x1)/2) + f(x1));
}

double I2(double (*const f)(const double&),
	const double &x0,
	const double &x1){
	return I1(f, x0, (x0+x1)/2) + I1(f, (x0+x1)/2, x1);
}

double ASI(double (*const f)(const double&),
	const double &a,
	const double &b,
	const double &tol){

	double i1 = I1(f,a,b);
	double i2 = I2(f,a,b);

	if(fabs(i1-i2) < 15*tol)
		return i2;

	return ASI(f, a, (a+b)/2, tol/2) + ASI(f, (a+b)/2, b, tol/2);
}