#ifndef EXPBULGE_HPP
#define EXPBULGE_HPP

#include "Curvebase.hpp"

class ExpBulge : public Curvebase {
  public:
    // (1/2)*(1/(1 + exp(a*(x + b)))), x in [x0, a)
    // (1/2)*(1/(1 + exp(-a*x))), x in [a, x1]
    ExpBulge(double a, double b, double x0, double x1,
        double pmin, double pmax, bool rev);

  private:
    double xp(double p);
    double yp(double p);
    double dxp(double p);
    double dyp(double p);
    double _a, _b;
    double _x0, _x1;

};

#endif