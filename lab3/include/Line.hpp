#ifndef LINE_HPP
#define LINE_HPP

#include "Curvebase.hpp"

class Line : public Curvebase {
  public:
    // (x0, y0) + t * (vx, vy)
    Line(double x0, double y0, double vx, double vy,
        double pmin, double pmax, bool rev);

  private:
    double _x0, _y0;
    double _vx, _vy;
    double xp(double p) const;
    double yp(double p) const;
    double dxp(double p) const;
    double dyp(double p) const;
};

#endif