#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "myexp.hpp"

int main(int argc, char const *argv[])
{
  double x = atof(argv[1]);
  double tol = atof(argv[2]);
  double res; 
  if (tol == 0) res = myexp(x); // use default tol if no tol given, or tol == 0 (impossible to achieve)
  else res = myexp(x, tol);
  std::cout << "exp(x) = " << res << std::endl;
  std::cout << "error = " << abs(exp(x) - res) << std::endl;
  return 0;
}
