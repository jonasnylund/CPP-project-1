#include "Domain.hpp"
#include <stdexcept>
#include <cmath>
#include <cstdio>
#include <memory>

// #include <iostream>

bool Domain::closedDomain(std::shared_ptr<Curvebase> curves[], int len){
	std::shared_ptr<Curvebase> prev = curves[len-1];
	std::shared_ptr<Curvebase> current = nullptr;
	for (int i = 0; i < len-1; ++i){
		current = curves[i];
		// std::cout << "("<< prev->x(0) << ", " << prev->y(0) << ") (" << prev->x(1) << ", " << prev->y(1) << ")" << std::endl;
		// std::cout << "("<< current->x(0) << ", " << current->y(0) << ") (" << current->x(1) << ", " << current->y(1) << ")" << std::endl;
		if (! (abs(prev->x(1) - current->x(0)) < 0.001 && abs(prev->y(1) - current->y(0)) < 0.001)){
			return false;
		}
		prev = current;
	}
	return true;
}


Domain::Domain(Curvebase& c1, Curvebase& c2, Curvebase& c3, Curvebase& c4){

	// for (int i = 0; i < 4; ++i)
	// this->boundary[i] = arr[i];
	this->boundary[0] = std::shared_ptr<Curvebase>(&c1);
	this->boundary[1] = std::shared_ptr<Curvebase>(&c2);
	this->boundary[2] = std::shared_ptr<Curvebase>(&c3);
	this->boundary[3] = std::shared_ptr<Curvebase>(&c4);

	if (!Domain::closedDomain(this->boundary, 4)) {
		throw std::invalid_argument("Domain not consistent");
	}
	
	this->width = 0;
	this->height = 0;

	this->x_coor = std::vector<double>((this->width+1)*(this->height+1));
	this->y_coor = std::vector<double>((this->width+1)*(this->height+1));

}

Domain::Domain(const Domain& d) :
	width(d.width), height(d.height){

	if (d.width == 0 || d.height == 0){
		return;
	}

	this->x_coor = d.x_coor;
	this->y_coor = d.y_coor;
}
	
Domain& Domain::operator=(Domain& d){
	if (this == &d)
		return *this;

	this->width = d.width;
	this->height = d.height;
	this->x_coor = d.x_coor;
	this->y_coor = d.y_coor;

	return *this;

}

bool Domain::operator==(Domain& d) const {
	for (int i = 0; i < 4; ++i) {
		if (boundary[i] != d.boundary[i]) return false;
	}
	if (!(width == d.width && height == d.height)) return false;
	std::vector<double> x_coor_d = d.getX();
	for (int j = 0; j < width; ++j) {
		if (x_coor[j] != x_coor_d[j]) return false;
	}
	std::vector<double> y_coor_d = d.getY();
	for (int i = 0; i < height; ++i) {
		if (y_coor[i] != y_coor_d[i]) return false;
	}
	return true;
} 

void Domain::toFile(const char * filename) const {

	FILE *file;
	file = fopen(filename, "wb");

	fwrite(&this->width, sizeof(int), 1, file);
	fwrite(&this->height, sizeof(int), 1, file);
	for (int i = 0; i < (this->width+1)*(this->height+1); ++i){
		fwrite(&this->x_coor[i], sizeof(double), 1, file);
		fwrite(&this->y_coor[i], sizeof(double), 1, file);
	}

	fclose(file);
}

void Domain::generate_grid(const int m, const int n, const double delta) {
  if (m <= 0 || n <= 0) throw std::invalid_argument("m and n needs to be positive");
  else { // if a grid already exists, overwrite this
    this->height = m; this->width = n;
    this->x_coor.resize((this->height + 1)* (this->width + 1));
    this->y_coor.resize((this->height + 1)* (this->width + 1));
		double xi, eta;

    #pragma omp parallel for private(xi, eta)
    for (int i = 0; i < this->height + 1; ++i) {
      // use 1 - i/m since matrices are indexed top -> bottom
			eta = Domain::stretch(1 - i / (double) m, delta);
      for (int j = 0; j < this->width + 1; ++j) {
				xi = j / (double) n;
        this->x_coor[j + i*(this->width + 1)] = phi1(xi) * this->boundary[1]->x(1 - eta)
                      + phi2(xi) * this->boundary[3]->x(eta)
                      + phi1(eta) * (
                        this->boundary[2]->x(xi)
                        - phi1(xi) * this->boundary[2]->x(0)
                        - phi2(xi) * this->boundary[2]->x(1)
                      )
                      + phi2(eta) * (
                        this->boundary[0]->x(1 - xi)
                        - phi1(xi) * this->boundary[0]->x(1)
                        - phi2(xi) * this->boundary[0]->x(0)
                      );
        this->y_coor[j + i*(this->width + 1)] = 
											phi1(xi) * this->boundary[1]->y(1 - eta)
                      + phi2(xi) * this->boundary[3]->y(eta)
                      + phi1(eta) * (
                        this->boundary[2]->y(xi)
                        - phi1(xi) * this->boundary[2]->y(0)
                        - phi2(xi) * this->boundary[2]->y(1)
                      )
                      + phi2(eta) * (
                        this->boundary[0]->y(1 - xi)
                        - phi1(xi) * this->boundary[0]->y(1)
                        - phi2(xi) * this->boundary[0]->y(0)
											);
      }
    }
  }
}

inline double Domain::stretch(const double sigma, const double delta) {
	if (delta == 0)
		return sigma;
	return 1 + tanh(delta * (sigma - 1))/tanh(delta);
}

Point Domain::getPoint(int row, int col) const{
	if (row < 0 || this->height < row)
		throw std::invalid_argument("row argument must be between 0 and this->height+1");
	if (col < 0 || this->width < col)
		throw std::invalid_argument("col argument must be between 0 and this->width+1");


	Point p;
	p.x = this->x_coor[row * (this->width+1) + col];
	p.y = this->y_coor[row * (this->width+1) + col];

	return p;
}
inline void Domain::setPoint(int row, int col, double x, double y){
	if (row < 0 || this->height < row)
		throw std::invalid_argument("row argument must be between 0 and this->height+1");
	if (col < 0 || this->width < col)
		throw std::invalid_argument("col argument must be between 0 and this->width+1");
	
	this->x_coor[row * (this->width+1) + col] = x;
	this->y_coor[row * (this->width+1) + col] = y;
}

inline void Domain::setPoint(int row, int col, Point p){
	this->setPoint(row, col, p.x, p.y);
}

std::vector<double> Domain::getX() const {
  return this->x_coor;
}

std::vector<double> Domain::getY() const {
  return this->y_coor;
}

inline double Domain::phi1(const double s) {
  // from 1 to 0 when s goes from 0 to 1
	return 1.0 - s;
}

inline double Domain::phi2(const double s) {
  // from 0 to 1 when s goes from 0 to 1
	return s;
}

int Domain::xsize() const { return this->width; }
int Domain::ysize() const { return this->height; }

bool Domain::grid_valid() { return this->width != 0; }
