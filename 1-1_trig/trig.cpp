#include <cmath>
#include <string>
#include <iostream>
#include "taylor.cpp"

int main(int argc, char const *argv[])
{

	if (argc >= 2) {
		int N = atoi(argv[1]);
		double x = atof(argv[2]);

		printf("N: %d, x: %f\n", N, x);
		printf("---------------\n");
		
		printf("taylor sin(x) = %f\n", sinTaylor(N, x));
		printf("sin(x) = %f\n", sin(x));
		printf("Diff: %f\n", fabs(sinTaylor(N, x) - sin(x)));
		printf("---------------\n");

		printf("taylor cos(x) = %f\n", cosTaylor(N, x));
		printf("cos(x) = %f\n", cos(x));
		printf("Diff: %f\n", fabs(cosTaylor(N, x)-cos(x)));
	}

	printf("\nPerform error check? y/n\t");
	std::string cont;
	std::cin >> cont;

	if (cont == "y") {
		unsigned bounded = 0;
		unsigned unbounded = 0;

		int N_vals[] = {3,5,10};
		double x_vals[] = {-1, 1, 2, 3, 5, 10};
		for (double x : x_vals) {
			for (int N : N_vals) {
				double sinTayl_curr = sinTaylor(N, x);
				double sinDiff = fabs(sinTayl_curr - sin(x));
				double sin_next_term = sinTaylor(N+1, x) - sinTayl_curr;

				double cosTayl_curr = cosTaylor(N, x);
				double cosDiff = fabs(cosTayl_curr - cos(x));
				double cos_next_term = cosTaylor(N+1, x) - cosTayl_curr;

				bool sinBounded = (sinDiff <= fabs(sin_next_term));
				bool cosBounded = (cosDiff <= fabs(cos_next_term));

				printf("N = %i\tx = %f\n", N, x);
				printf("--------------\n");
				printf("Diff sin: %f\n", sinDiff);
				printf("N+1st term: %f\n", sin_next_term);
				printf("|sinTaylor(N,x) - sin(x)| <= |term N+1|: ");
				printf("%s\n", sinBounded ? "true" : "false");
				printf("--------------\n");
				printf("Diff cos: %f\n", cosDiff);
				printf("N+1st term: %f\n", cos_next_term);
				printf("|cosTaylor(N,x) - cos(x)| <= |term N+1|: ");
				printf("%s\n", cosBounded ? "true" : "false");
				printf("==============\n");

				bounded += sinBounded;
				bounded += cosBounded;

				unbounded += !sinBounded;
				unbounded += !cosBounded;
			}
  	}

		printf("CHECK COMPLETE\n");
		printf("Bounded errors: %i\n", bounded);
		printf("Unbounded errors: %i\n", unbounded);
	}

	

	return 0;
}
