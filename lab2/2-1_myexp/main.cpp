#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "myexp.hpp"

int main(int argc, char const *argv[])
{
  double x = atof(argv[1]);
  double tol = atof(argv[2]);
  double res = myexp(x, tol);
  std::cout << "exp(x) = " << res << std::endl;
  std::cout << "error = " << abs(exp(x) - res) << std::endl;
  return 0;
}
