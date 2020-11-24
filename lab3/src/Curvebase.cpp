#include "Curvebase.hpp"
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>

Curvebase::Curvebase(double pmin, double pmax, bool rev) :
  _pmin(pmin), _pmax(pmax), _rev(rev) {
    if (pmin >= pmax) throw std::invalid_argument("pmin needs to be smaller than pmax");
}

double Curvebase::integrate(double p) const {
  // std::cout << p << " " << this->_pmin << " " << this->_pmax << std::endl; 
  validate_p(p);
  const int N = 1000; // number of points in the discretization
  const double delta_p = (p - this->_pmin) / N;
  if (delta_p == 0) return 0;
  double res = 0;
  double p_i = 0;
  for (int i = 1; i < N; ++i) {
    p_i = i * delta_p + _pmin;
    res += sqrt(pow(this->dxp(p_i), 2) + pow(this->dyp(p_i), 2));
  }
  res += sqrt(pow(this->dxp(this->_pmin), 2) + pow(this->dyp(this->_pmin), 2)) / 2;
  res += sqrt(pow(this->dxp(p), 2) + pow(this->dyp(p), 2)) / 2;

  return delta_p * res;
}

double Curvebase::p_from_s(double s) const {
  if (s < 0 || s > 1) throw std::invalid_argument("s must be within [0, 1]");
  if (this->_rev) s = 1 - s;
  const double tol = 0.0001;
  const int maxiter = 100;
  double p = this->_pmin + s*(this->_pmax - this->_pmin); // choose p_0
  double pp = p;
  double diff = 2 * tol;
  const double arcLength = this->getLength();
  double f_prime = 0;
  int numIt = 0;
  while (diff > tol && numIt < maxiter) {
    p = pp; // p = p_i; pp = p_{i+1}
    // p_{i+1} = p_i - f(p_i)/f'(p_i)
    // with f(p) = integrate(p) - s * integrate(pmax)
    // f'(p) = \sqrt(dxp(p)^2 + dyp(p)^2) - \sqrt(dxp(pmin)^2 + dyp(pmin)^2) 
    f_prime = sqrt(pow(this->dxp(p), 2) + pow(this->dyp(p), 2));
    pp = p - ((this->integrate(p) - s * arcLength)/f_prime);
    ++numIt;
    diff = abs(p - pp);
  } 
  if (numIt >= maxiter) std::cerr << "TOO MANY ITERATIONS, NO CONVERGENCE: double Curvebase::p_from_s(double s)" << std::endl;

  return pp;
}

double Curvebase::x(double s) const {
  return this->xp(this->p_from_s(s));
}

double Curvebase::y(double s) const {
  return this->yp(this->p_from_s(s));
}

void Curvebase::validate_p(double p) const {
  if (p < this->_pmin || p > this->_pmax) {
    std::cerr << "(p, pmin, pmax) = (" << p << ", " << _pmin << ", " << _pmax << ")" << std::endl;
    throw std::invalid_argument("p must be within [pmin, pmax]");
  }
}

double Curvebase::getLength() const {return this->integrate(this->_pmax);}