#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <memory>
#include <cmath>

#include "Curvebase.hpp"
#include "Line.hpp"
#include "ExpBulge.hpp"
#include "Domain.hpp"
#include "GFkt.hpp"

#define FILENAME_LEN 50

using namespace std;

double u(double x, double y) {
  return std::sin(pow(x/10, 2))*cos(x/10) + y;
}

int main(int argc, char const *argv[])
{

  int m = 50; int n = 20;
  // int m = 10; int n = 6;
  double delta = 0.0;

  if (argc > 2){
    m = atoi(argv[1]);
    n = atoi(argv[2]);
  }
  if (argc > 3){
    delta = atof(argv[3]);
  }

  printf("Generating %dx%d grid\n", m, n);

  Line top = Line(5, 3, -1, 0, 0, 15, false);
  Line left = Line(-10, 3, 0, -1, 0, 3, false);
  ExpBulge bottom = ExpBulge(-3, 6, -10, 5, 0, 1, false);
  Line right = Line(5, 0, 0, 1, 0, 3, false);

  // Test of the basic classes: integrate their length 
  // printf("len of top boundary %f\n", top.getLength());
  // printf("len of left boundary %f\n", left.getLength());
  // printf("len of right boundary %f\n", right.getLength());
  // printf("len of bottom boundary %f\n", bottom.getLength());

  Domain myDomain = Domain(top, left, bottom, right);
  // Domain myDomain = Domain(top, right, bottom, left); // if all curves are reversed
  
  myDomain.generate_grid(m, n, delta);

  // myDomain.toFile(file);
  // printf("Grid output to %s\n", file);
  

  GFkt myGFkt_1 = GFkt(std::make_shared<Domain>(myDomain));
  // GFkt myGFkt_2 = GFkt(std::make_shared<Domain>(myDomain));

  // cout << (myGFkt_1.u == myGFkt_2.u) << endl;

  // GFkt add = myGFkt_1 + myGFkt_2;
  // GFkt subtract = myGFkt_1 - myGFkt_2;
  // GFkt mult1 = myGFkt_1 * 3.0;
  // GFkt mult2 = 3.0 * myGFkt_1;
  // GFkt mult3 = myGFkt_1 * myGFkt_2;
  // GFkt divide = myGFkt_1 / 5.0;
  
  myGFkt_1.set_values(u);
  // myGFkt_1.get_values().print();
  GFkt xder = myGFkt_1.du_dx();
  GFkt yder = myGFkt_1.du_dy();
  GFkt Lapl = myGFkt_1.Laplace();
  // Lapl.get_values().print();

  myGFkt_1.toFile("u.txt");
  xder.toFile("xder.txt");
  yder.toFile("yder.txt");
  Lapl.toFile("Laplace.txt");

  // TODO: inline relevant member functions

  return 0;
} 