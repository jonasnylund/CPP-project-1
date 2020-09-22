#include <iostream>
#include <cmath>

using namespace std;

double I_1(double al, double be, double (*f)(double)) {
  return (be - al)*(f(al) + 4 * f((al + be)/2) + f(be))/6;
}

double I_2(double al, double be, double (*f)(double)) {
  double gam = (al + be)/2;
  return I_1(al, gam, *f) + I_1(gam, be, *f);
}

double f(double x) {
  return 1 + sin(exp(3*x));
}

double ASI(double al, double be, double (*f)(double), double tol) {
  double I1 = I_1(al, be, *f);
  double I2 = I_2(al, be, *f);

  double errest = abs(I1 - I2);

  if (errest < 15*tol) return I2;
  return ASI(al, (al + be)/2, *f, tol/2) + ASI((al + be)/2, be, *f, tol/2);
}

int main()
{
  double true_val = 2.5008091103361667; // from WolframAlpha

  double al, be;
  cout << "alpha: ";
  cin >> al;
  cout << "beta: ";
  cin >> be;

  double tol_vals[] = {1e-2, 1e-3, 1e-4};
  for (double tol : tol_vals) {
    double res = ASI(al, be, *f, tol);
    cout << "tol = " << tol << "\t-->\t" << res << "\t";
    cout << "(error = " << abs(res - true_val) << ")" << endl;
  }

  return 0;
}
