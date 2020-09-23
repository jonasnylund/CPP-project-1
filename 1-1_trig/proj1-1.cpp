#include <cmath>
#include <iostream>
#include "sinTaylor.cpp"

using namespace std;

int main() {
  int N_vals[] = {3,5,10,20};
  double x_vals[] = {-1, 1, 2, 3, 5, 10};
  for (double x : x_vals) {
    for (int N : N_vals) {
      cout << "|sin(" << x << ") - sin(" << N << ", "<< x << ")| = " <<
        abs(sinTaylor(N, x) - sin(x)) << endl;
    }
  }
}