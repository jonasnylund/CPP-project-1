#ifndef GFKT_HPP
#define GFKT_HPP

#include "Matrix.hpp"
#include "Domain.hpp"
#include <memory>

class GFkt {
  private:
    Matrix u;
    std::shared_ptr<Domain> grid;
    GFkt du_dxi() const;
    GFkt du_deta() const;
    GFkt dphix_dxi() const;
    GFkt dphiy_dxi() const;
    GFkt dphix_deta() const;
    GFkt dphiy_deta() const;
    GFkt detJinv() const;

  public:
    GFkt(std::shared_ptr<Domain> _grid);
    GFkt(const GFkt& gf);

    GFkt& operator=(const GFkt& gf);
    
    const GFkt& operator+=(const GFkt& gf);
    const GFkt operator+(const GFkt& gf) const;

    const GFkt& operator-=(const GFkt& gf);
    const GFkt operator-(const GFkt& gf) const;

    const GFkt& operator*=(const double k);
    const GFkt operator*(const GFkt& gf) const;
    const GFkt operator*(const double k) const;
    const friend GFkt operator*(const double k, GFkt& gf);
    
    const GFkt& operator/=(const double k);
    const GFkt operator/(const double k) const;

    // ~GFkt(); not needed since we use std::shared_ptr<Domain> for grid

    void set_values(double (*f)(double x, double y));
    void set_values(Matrix _u);
    GFkt du_dx() const;
    GFkt du_dy() const;
    GFkt Laplace() const;
    Matrix get_values() const;

    void toFile(const char* filename) const;
};

#endif