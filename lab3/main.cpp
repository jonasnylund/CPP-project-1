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

  // cout << setprecision(10) << "top: " << top.getLength() << std::endl;
  // cout << setprecision(10) << "left: " << left.getLength() << std::endl;
  // cout << setprecision(10) << "bottom: " << bottom.getLength() << std::endl;
  // cout << setprecision(10) << "right: " << right.getLength() << std::endl;

  Domain myDomain = Domain(top, left, bottom, right);
  int m = 20; int n = 20;
  myDomain.generate_grid(m, n);
  myDomain.stretch(0.0, 2.0);


  myDomain.toFile("myfile.bin");
}