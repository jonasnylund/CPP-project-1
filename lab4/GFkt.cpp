#include "GFkt.hpp"
#include "Matrix.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <iomanip>

GFkt::GFkt(std::shared_ptr<Domain> _grid) : u(_grid->ysize()+1, _grid->xsize()+1),
                                            grid(_grid) { } 
GFkt::GFkt(const GFkt& gf) : u(gf.u), grid(gf.grid) { }

GFkt GFkt::detJinv() const {
  GFkt tmp = (dphix_dxi() * dphiy_deta()) - (dphiy_dxi() * dphix_deta());
  Matrix vals = tmp.get_values();
  for (int i = 0; i < vals.getRows(); ++i) {
    for (int j = 0; j < vals.getCols(); ++j) {
      if (vals[i][j] == 0.0) {
        vals[i][j] = 0.000001; // avoid division by 0
      }
      vals[i][j] = 1.0 / vals[i][j];
    }
  }
  tmp.set_values(vals); 
  return tmp;
}

GFkt& GFkt::operator=(const GFkt& gf) {
  if (this == &gf) {
    return *this;
  }
  u = gf.u;
  grid = gf.grid;
  return *this;
}

const GFkt& GFkt::operator+=(const GFkt& gf) {
  u += gf.u;
  return *this;
}

const GFkt GFkt::operator+(const GFkt& gf) const {
  if (*grid == *(gf.grid)) { // defined on the same grid
    GFkt res(gf);
    res.u = u + gf.u;
    return res;
  } else throw std::invalid_argument("Addition of grid functions require identical grids.");
}

const GFkt& GFkt::operator-=(const GFkt& gf) {
  u -= gf.u;
  return *this;
}

const GFkt GFkt::operator-(const GFkt& gf) const {
  if (*grid == *(gf.grid)) { // defined on the same grid
    GFkt res(gf);
    res.u = u - gf.u;
    return res;
  } else throw std::invalid_argument("Subtraction of grid functions require identical grids.");
}

const GFkt& GFkt::operator*=(const double k) {
  u *= k;
  return *this;
}

const GFkt GFkt::operator*(const GFkt& gf) const {
  if (*grid == *(gf.grid)) { // defined on the same grid
    GFkt res(grid);
    for (int i = 0; i < grid->ysize() + 1; ++i) {
      for (int j = 0; j < grid->xsize() + 1; ++j) {
        res.u[i][j] = u[i][j] * gf.u[i][j];
      }
    }
    return res;
  } else throw std::invalid_argument("Multiplication of grid functions require identical grids.");
}

const GFkt GFkt::operator*(const double k) const {
  GFkt res(*this);
  res *= k;
  return res;
}

const GFkt operator*(const double k, GFkt& gf) {
  return gf * k;
}

const GFkt& GFkt::operator/=(const double k) {
  u /= k;
  return *this;
}

const GFkt GFkt::operator/(const double k) const {
  GFkt res(*this);
  res /= k;
  return res; 
}

void GFkt::set_values(double (*f)(double x, double y)) {
  for (int i = 0; i < grid->ysize() + 1; ++i) {
    for (int j = 0; j < grid->xsize() + 1; ++j) {
      u[i][j] = f(grid->getPoint(i, j).x, grid->getPoint(i, j).y);
    }
  }
}

GFkt GFkt::dphix_dxi() const {
  // assume constant step size in xi
  GFkt tmp(grid);
  double h = 1.0 / grid->xsize();
  for (int i = 0; i < grid->ysize() + 1; ++i) {
    // j == 0
    // tmp.u[i][0] = (1/h) * (grid->getPoint(i, 1).x - grid->getPoint(i, 0).x);
    tmp.u[i][0] =  (3*grid->getPoint(i, 0).x - 4*grid->getPoint(i, 1).x + grid->getPoint(i, 2).x) / (3 * h);
    for (int j = 1; j < grid->xsize(); ++j) {
      tmp.u[i][j] = (1/(2*h)) * (grid->getPoint(i, j+1).x - grid->getPoint(i, j-1).x);
    }
    // j == grid->xsize()
    // tmp.u[i][grid->xsize()] = (1/h) * (grid->getPoint(i, grid->xsize()).x - grid->getPoint(i, grid->xsize() - 1).x);
    tmp.u[i][grid->xsize()] = (3*grid->getPoint(i, grid->xsize()).x
                              -4*grid->getPoint(i, grid->xsize() - 1).x
                              +  grid->getPoint(i, grid->xsize() - 2).x) / (3 * h);
  }
  return tmp;
}

GFkt GFkt::dphiy_dxi() const {
  // assume constant step size in xi
  GFkt tmp(grid);
  double h = 1.0 / grid->xsize();
  for (int i = 0; i < grid->ysize() + 1; ++i) {
    // j == 0
    // tmp.u[i][0] = (1/h) * (grid->getPoint(i, 1).y - grid->getPoint(i, 0).y);
    tmp.u[i][0] =  (3*grid->getPoint(i, 0).y - 4*grid->getPoint(i, 1).y + grid->getPoint(i, 2).y) / (3 * h);
    for (int j = 1; j < grid->xsize(); ++j) {
      tmp.u[i][j] = (1/(2*h)) * (grid->getPoint(i, j+1).y - grid->getPoint(i, j-1).y);
    }
    // j == grid->xsize()
    // tmp.u[i][grid->xsize()] = (1/h) * (grid->getPoint(i, grid->xsize()).y - grid->getPoint(i, grid->xsize() - 1).y);
    tmp.u[i][grid->xsize()] = (3*grid->getPoint(i, grid->xsize()).y
                              -4*grid->getPoint(i, grid->xsize() - 1).y
                              +  grid->getPoint(i, grid->xsize() - 2).y) / (3 * h);
  }
  return tmp;
}

GFkt GFkt::dphix_deta() const {
  // assume constant step size in eta
  GFkt tmp(grid);
  double h = 1.0 / grid->ysize();
  for (int j = 0; j < grid->xsize() + 1; ++j) {
    // i == 0
    // tmp.u[0][j] = (1/h) * (grid->getPoint(1, j).x - grid->getPoint(0, j).x);
    tmp.u[0][j] =  (3*grid->getPoint(0, j).x - 4*grid->getPoint(1, j).x + grid->getPoint(2, j).x) / (3 * h);
    for (int i = 1; i < grid->ysize(); ++i) {
      tmp.u[i][j] = (1/(2*h)) * (grid->getPoint(i+1, j).x - grid->getPoint(i-1, j).x);
    }
    // i == grid->ysize()
    // tmp.u[grid->ysize()][j] = (1/h) * (grid->getPoint(grid->ysize(), j).x - grid->getPoint(grid->ysize() - 1, j).x);
    tmp.u[grid->ysize()][j] = (3*grid->getPoint(grid->ysize(), j).x
                              -4*grid->getPoint(grid->ysize() - 1, j).x
                              +  grid->getPoint(grid->ysize() - 2, j).x) / (3 * h);
  }
  return tmp;
}

GFkt GFkt::dphiy_deta() const {
  // assume constant step size in eta
  GFkt tmp(grid);
  double h = 1.0 / grid->ysize();
  for (int j = 0; j < grid->xsize() + 1; ++j) {
    // i == 0
    // tmp.u[0][j] = (1/h) * (grid->getPoint(1, j).y - grid->getPoint(0, j).y);
    tmp.u[0][j] =  (3*grid->getPoint(0, j).y - 4*grid->getPoint(1, j).y + grid->getPoint(2, j).y) / (3 * h);
    for (int i = 1; i < grid->ysize(); ++i) {
      tmp.u[i][j] = (1/(2*h)) * (grid->getPoint(i+1, j).y - grid->getPoint(i-1, j).y);
    }
    // i == grid->ysize()
    // tmp.u[grid->ysize()][j] = (1/h) * (grid->getPoint(grid->ysize(), j).y - grid->getPoint(grid->ysize() - 1, j).y);
    tmp.u[grid->ysize()][j] = (3*grid->getPoint(grid->ysize(), j).y
                          -4*grid->getPoint(grid->ysize() - 1, j).y
                          +  grid->getPoint(grid->ysize() - 2, j).y) / (3 * h);
  }
  return tmp;
}


GFkt GFkt::du_dxi() const {
  // assume constant step size in xi
  GFkt tmp(grid);
  double h = 1.0 / grid->xsize();
  for (int i = 0; i < grid->ysize() + 1; ++i) {
    // j == 0
    // tmp.u[i][0] = (1/h) * (u[i][1] - u[i][0]);
    tmp.u[i][0] = (3*u[i][0] - 4*u[i][1] + u[i][2]) / (3 * h);
    for (int j = 1; j < grid->xsize(); ++j) {
      tmp.u[i][j] = (1/(2*h)) * (u[i][j+1] - u[i][j-1]);
    }
    //j == grid->xsize()
    // tmp.u[i][grid->xsize()] = (1/h) * (u[i][grid->xsize()] - u[i][grid->xsize()-1]);
    tmp.u[i][grid->xsize()] = (3*u[i][grid->xsize()]
                              - 4*u[i][grid->xsize() - 1]
                              + u[i][grid->xsize() - 2]) / (3 * h);
  }
  return tmp;
}

GFkt GFkt::du_deta() const {
  // assume constant step size in eta
  GFkt tmp(grid);
  double h = 1.0 / grid->ysize();
  for (int j = 0; j < grid->xsize() + 1; ++j) {
    // i == 0
    // tmp.u[0][j] = (1/h) * (u[1][j] - u[0][j]);
    tmp.u[0][j] = (3*u[0][j] - 4*u[1][j] + u[2][j]) / (3 * h);
    for (int i = 1; i < grid->ysize(); ++i) {
      tmp.u[i][j] = (1/(2*h)) * (u[i+1][j] - u[i-1][j]);
    }
    //i == grid->ysize()
    // tmp.u[grid->ysize()][j] = (1/h) * (u[grid->ysize()][j] - u[grid->ysize() - 1][j]);
    tmp.u[grid->ysize()][j] = (3*u[grid->ysize()][j]
                              - 4*u[grid->ysize() - 1][j]
                              + u[grid->ysize() - 2][j]) / (3 * h);
  }
  return tmp;
}

void GFkt::toFile(const char* filename) const {
  std::ofstream ofile;
  ofile.open(filename);
  if (!ofile) {
    std::cerr << "Error opening output file!";
    exit(1);
  }
  ofile << grid->ysize() << ", ";
  ofile << grid->xsize() << "\n";
  const std::vector<double> xvals = grid->getX();
  const std::vector<double> yvals = grid->getY();
  const double* zvals = u.getArray();
  for (int i = 0; i < (grid->ysize() + 1)*(grid->xsize() + 1); ++i) {
    ofile << xvals[i] << ", ";
    ofile << yvals[i] << ", ";
    ofile << zvals[i] << "\n";
  }
}
