#include <iostream>
#include <cmath>
#include "myexp.hpp"

double myexp(const double &x, const double tol) {
  if (x < 0) return 1/myexp(-x, tol);
  int N = 0;
  double err = (x / 2) * (1 + (x * (x + 1)) / (x + 2));
  while (err > tol) {
    ++N;
    err *= (x/(N+1));
  }
  if (N < x) N = ceil(x); // make sure N >= x
  std::cout << "Summing up to n = " << N << std::endl;
  double res = 1;
  for (int i = N; i > 0; --i) {
    res = 1 + res * x / i;
  }
  return res;
}