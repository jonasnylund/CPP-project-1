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
    inline void set_values(Matrix _u) { u = _u; }
    inline GFkt du_dx() const {
      if (grid->xsize() < 2 || grid->ysize() < 2) {
        exit(-1);
      }
      GFkt tmp = detJinv() * (du_dxi() * dphiy_deta() - du_deta() * dphiy_dxi());
      return tmp;
    }

    inline GFkt du_dy() const {
      if (grid->xsize() < 2 || grid->ysize() < 2) {
        exit(-1);
      }
      GFkt tmp = detJinv() * (du_deta() * dphix_dxi() - du_dxi() * dphix_deta());
      return tmp;
    }

    inline GFkt Laplace() const {
      GFkt ddxx = (this->du_dx()).du_dx();
      GFkt ddyy = (this->du_dy()).du_dy();
      return ddxx + ddyy;  
    }

    inline Matrix get_values() const { return this->u; }

    void toFile(const char* filename) const;
};

#endif