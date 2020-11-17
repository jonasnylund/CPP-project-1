#include <iostream>
#include "Curvebase.hpp"
#include "Line.hpp"
#include "ExpBulge.hpp"
#include <iomanip>

using namespace std;

int main() {
  Line testLine = Line(-10, 0, 0, 1, 0, 3, false);
  // cout << testLine.x(0.6) << endl;
  // cout << testLine.y(0.6) << endl;
  ExpBulge testBulge = ExpBulge(-3, 6, -10, 5, 0, 1, false);
  // cout << setprecision(16) << testBulge.x(0.2) << " | "<< testBulge.y(0.2) << endl;
  // cout << testBulge.x(0.25) << " | "<< testBulge.y(0.25) << endl;
  // cout << testBulge.x(0.3) << " | "<< testBulge.y(0.3) << endl;
  // cout << testBulge.x(0.35) << " | "<< testBulge.y(0.35) << endl;
  // cout << testBulge.p_from_s(0.2) << " " << testBulge.p_from_s(0.3) << std::endl; 
  cout << setprecision(10) << testLine.getLength() << " " << testBulge.getLength() << std::endl;
  // double a = 0.2;
  // double b = 15*a;
  // cout << setprecision(10) << testBulge.xp(a) << std::endl;
  // cout << setprecision(10) << testBulge.yp(a) << std::endl;
  // cout << setprecision(10) << testBulge.dxp(a) << std::endl;
  // cout << setprecision(10) << testBulge.dyp(a) << std::endl;
}