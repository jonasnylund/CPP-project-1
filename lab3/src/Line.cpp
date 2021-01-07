#include "Line.hpp"
#include <stdexcept>

    // (x0, y0) + p * (vx, vy)
Line::Line(double x0, double y0, double vx, double vy,
    double pmin, double pmax, bool rev) : 
      Curvebase(pmin, pmax, rev),
      _x0(x0), _y0(y0), _vx(vx), _vy(vy) {
        if (vx == 0 && vy == 0) throw std::invalid_argument("direction vector of line cannot be (0, 0)");
      }
      
double Line::xp(double p) const {
  validate_p(p);
  return this->_x0 + p * this->_vx;
}
double Line::yp(double p) const {
  validate_p(p);
  return this->_y0 + p * this->_vy;
}
double Line::dxp(double p) const {
  validate_p(p);
  return this->_vx;
}
double Line::dyp(double p) const {
  validate_p(p);
  return this->_vy;
}