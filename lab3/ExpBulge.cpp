#include "ExpBulge.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

// (1/2)*(1/(1 + exp(a*(x + b)))), x in [x0, a)
// (1/2)*(1/(1 + exp(-a*x))), x in [a, x1]
ExpBulge::ExpBulge(double a, double b, double x0, double x1,
        double pmin, double pmax, bool rev) :
          Curvebase(pmin, pmax, rev), _a(a), _b(b), _x0(x0), _x1(x1)
        {
          if (x0 >= x1) throw std::invalid_argument("x0 should be smaller than x1");
          if (a <= x0 || a > x1) throw std::invalid_argument("a should be in (x0, x1]");
        }

double ExpBulge::xp(double p) {
  validate_p(p);
  return ((p - _pmin)/(_pmax - _pmin)) * (_x1 - _x0) +  _x0;
}

double ExpBulge::yp(double p) {
  const double X = xp(p);
  if (X < _a) {
    return 0.5*(1.0/(1.0 + exp(_a*(X + _b))));
  }
  return 0.5*(1.0/(1.0 + exp(-_a*X)));
}

double ExpBulge::dxp(double p) {
  return (_x1 - _x0) / (_pmax - _pmin);
}

double ExpBulge::dyp(double p) {
  const double X = xp(p);
  if (X < _a) {
    return 0.5*(-_a*dxp(p)*exp(_a*(X + _b))/pow(1.0 + exp(_a*(X + _b)), 2));
  }
  return 0.5*(_a*dxp(p)*exp(-_a*X)/pow(1.0 + exp(-_a*X), 2));
}
