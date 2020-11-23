#include <iostream>
#include <iomanip>
#include <vector>

#include "Curvebase.hpp"
#include "Line.hpp"
#include "ExpBulge.hpp"
#include "Domain.hpp"

using namespace std;

int main() {
  Line top = Line(5, 3, -1, 0, 0, 15, false);
  Line left = Line(-10, 3, 0, -1, 0, 3, false);
  ExpBulge bottom = ExpBulge(-3, 6, -10, 5, 0, 1, false);
  Line right = Line(5, 0, 0, 1, 0, 3, false);

  Domain myDomain = Domain(top, left, bottom, right);
  // Domain myDomain = Domain(top, right, bottom, left); // if all curves are reversed
  
  int m = 50; int n = 30;
  myDomain.generate_grid(m, n);
  // vector<double> x_vect = myDomain.getX();
  // vector<double> y_vect = myDomain.getY();
  // for (int i = 0; i < m+1; ++i) {
  //   for (int j = 0; j < n+1; ++j) {
  //     printf("(%6.2f, %6.2f)\t", x_vect[j + i*(n + 1)], y_vect[j + i*(n + 1)]);
  //   }
  //   cout << endl;
  // }

  // Jonas version
  // myDomain.stretch(0.0, 2.0);

  myDomain.toFile("myfile.bin");
}