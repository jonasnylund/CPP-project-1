#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#include "Curvebase.hpp"
#include "Line.hpp"
#include "ExpBulge.hpp"
#include "Domain.hpp"

#define FILENAME_LEN 50

using namespace std;


int main(int argc, char const *argv[])
{

  int m = 50; int n = 30;
  double delta = 0.0;
  char *file = new char[FILENAME_LEN];
  strncpy(file, "myfile.bin", FILENAME_LEN);

  if (argc > 2){
    m = atoi(argv[1]);
    n = atoi(argv[2]);
  }
  if (argc > 3){
    delta = atof(argv[3]);
  }
  if (argc > 4){
    strncpy(file, argv[4], FILENAME_LEN);
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

  myDomain.toFile(file);
  printf("Grid outputted to %s\n", file);
  
  return 0;
}