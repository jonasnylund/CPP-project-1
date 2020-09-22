#include "math.h"
#include "stdio.h"
#include "stdlib.h"

double sinTaylor(const int N, const double x);
double cosTaylor(const int N, const double x);


int main(int argc, char const *argv[])
{

	int N = atoi(argv[1]);
	double x = atof(argv[2]);

	printf("N: %d, x: %f\n", N, x);
	printf("taylor sin(x) = %f\n", sinTaylor(N, x));
	printf("sin(x) = %f\n", sin(x));
	printf("Diff: %f\n", fabs(sinTaylor(N, x) - sin(x)));

	printf("taylor cos(x) = %f\n", cosTaylor(N, x));
	printf("cos(x) = %f\n", cos(x));
	printf("Diff: %f\n", fabs(cosTaylor(N, x)-cos(x)));

	/* code */
	return 0;
}

double sinTaylor(const int N, const double x){

	double res = 1;

	for(int n=N-1; n>0; n--){
		res = 1 - res * (x/(2*n+1)*(x/(2*n)));
	}
	res *= x;

	return res;

}

double cosTaylor(const int N, const double x){

	double res = 1;

	for(int n=N-1; n>0; n--){
		res = 1 - res * (x/(2*n)*(x/(2*n-1)));
	}

	return res;

}