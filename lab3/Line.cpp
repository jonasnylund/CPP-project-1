#include "Line.hpp"
#include <stdexcept>

    // (x0, y0) + p * (vx, vy)
Line::Line(double x0, double y0, double vx, double vy,
    double pmin, double pmax, bool rev) : 
      Curvebase(pmin, pmax, rev),
      _x0(x0), _y0(y0), _vx(vx), _vy(vy) {
        if (vx == 0 && vy == 0) throw std::invalid_argument("direction vector of line cannot be (0, 0)");
      }
      
inline double Line::xp(double p) {
  validate_p(p);
  return this->_x0 + p * this->_vx;
}
inline double Line::yp(double p) {
  validate_p(p);
  return this->_y0 + p * this->_vy;
}
inline double Line::dxp(double p) {
  validate_p(p);
  return this->_vx;
}
inline double Line::dyp(double p) {
  validate_p(p);
  return this->_vy;
}