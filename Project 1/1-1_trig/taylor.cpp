#include "taylor.hpp"

double sinTaylor(const int &N, const double &x) {
  double x_sq = x*x;
  double res = 1; // init to 1 as a result of using Horner's alg

  for (int i = N; i > 0; --i ) {
    res = 1 - res * x_sq/(2*i * (2*i+1));
  }
  // finally multiply with x
  res *= x;

  return res;
}

double cosTaylor(const int &N, const double &x){

	double res = 1;

	for(int n=N-1; n>0; n--){
		res = 1 - res * (x/(2*n)*(x/(2*n-1)));
	}

	return res;

}