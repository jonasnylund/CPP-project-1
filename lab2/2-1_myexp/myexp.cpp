#include <iostream>
#include <cmath>
#include "myexp.hpp"

double myexp(const double &x, const double tol) {
  if (x < 0) return 1/myexp(-x, tol);
  int N = 1;
  double err = pow(x, N+2)/2;
  while (err > tol) {
    ++N;
    err *= (x/(N+1));
  }
  std::cout << "N: " << N << std::endl;
  double res = 1;
  for (int i = N; i > 0; --i) {
    res = 1 + res * x / i;
  }
  return res;
}