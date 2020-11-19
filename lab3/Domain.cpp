#include "Domain.hpp"
#include <stdexcept>
#include <cmath>
#include <cstdio>
// #include <iostream>
bool Domain::closedDomain(Curvebase* curves[], int len){

	Curvebase *prev = curves[len-1];
	Curvebase *current = nullptr;
	for (int i = 0; i < len-1; ++i){
		current = curves[i];
		if (! (abs(prev->x(1) - current->x(0)) < 0.001 && abs(prev->y(1) - current->y(0)) < 0.001)){
			return false;
		}
		prev = current;
	}
	return true;
}


Domain::Domain(Curvebase& c1, Curvebase& c2, Curvebase& c3, Curvebase& c4){

	Curvebase *arr[] = {&c1, &c2, &c3, &c4};
	if (!Domain::closedDomain(arr, 4)) {
		throw std::invalid_argument("Domain not consistent");
	}

	for (int i = 0; i < 4; ++i)
		this->boundary[i] = arr[i];
	
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
	// this->x_coor = new double[*(this.width+1)*(this.height+1)];
	// this->y_coor = new double[*(this.width+1)*(this.height+1)];

	// memcpy(this->x_coor, d.x_coor, sizeof(double)*(this.width+1)*(this.height+1));
	// memcpy(this->y_coor, d.y_coor, sizeof(double)*(this.width+1)*(this.height+1));
}
	
Domain& Domain::operator=(Domain& d){
	if (this == &d)
		return *this;

	// if (this->width != d.width || this->height != d.height){
	// 	delete[] this->x_coor;
	// 	delete[] this->y_coor;
	// 	this->width = d.width;
	// 	this->height = d.height;
	// 	this->x_coor = new double[(this.width+1)*(this.height+1)];
	// 	this->y_coor = new double[(this.width+1)*(this.height+1)];
	// }

	this->width = d.width;
	this->height = d.height;
	this->x_coor = d.x_coor;
	this->y_coor = d.y_coor;
	// memcpy(this->x_coor, d.x_coor, sizeof(double)*(this.width+1)*(this.height+1));
	// memcpy(this->y_coor, d.y_coor, sizeof(double)*(this.width+1)*(this.height+1));

	return *this;

}

Domain::~Domain(){
	// if (this->x_coor != nullptr)
	// 	// delete[] this->x_coor;
	// if (this->y_coor != nullptr)
	// 	// delete[] this->y_coor;
}

// Domain Domain::fromFile(FILE *file){
// 	// Ugh, Curvebases..??
// 	return NULL;
// }

void Domain::toFile(const char* filename){

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

void Domain::generate_grid(int m, int n) {
  if (m <= 0 || n <= 0) throw std::invalid_argument("m and n needs to be positive");
  else { // if a grid already exists, overwrite this
    this->height = m; this->width = n;
    this->x_coor.resize((this->height + 1)* (this->width + 1));
    this->y_coor.resize((this->height + 1)* (this->width + 1));
    double xi, eta;

    #pragma omp parallel for
    for (int i = 0; i < this->height + 1; ++i) {
      xi = i / (double) m;
			// phi1xi = phi1(xi); phi2xi = phi2(xi);
      for (int j = 0; j < this->width + 1; ++j) {
        eta = j / (double) n;
        this->x_coor[j + i*(this->width + 1)] = phi1(xi) * this->boundary[0]->x(1 - eta)
                      + phi2(xi) * this->boundary[2]->x(eta)
                      + phi1(eta) * (
                        this->boundary[1]->x(xi)
                        - phi1(xi) * this->boundary[1]->x(0)
                        - phi2(xi) * this->boundary[1]->x(1)
                      )
                      + phi2(eta) * (
                        this->boundary[3]->x(1 - xi)
                        - phi1(xi) * this->boundary[3]->x(1)
                        - phi2(xi) * this->boundary[3]->x(0)
                      );
        this->y_coor[j + i*(this->width + 1)] = phi1(xi) * this->boundary[0]->y(1 - eta)
                      + phi2(xi) * this->boundary[2]->y(eta)
                      + phi1(eta) * (
                        this->boundary[1]->y(xi)
                        - phi1(xi) * this->boundary[1]->y(0)
                        - phi2(xi) * this->boundary[1]->y(1)
                      )
                      + phi2(eta) * (
                        this->boundary[3]->y(1 - xi)
                        - phi1(xi) * this->boundary[3]->y(1)
                        - phi2(xi) * this->boundary[3]->y(0)
                      );
      }
    }
  }
}

void Domain::stretch(double delta_x, double delta_y){

	if(delta_x != 0.0){

		double x0, x1;
		double k;
		Point p;
		for (int row = 0; row < this->height+1; row++){
			x0 = this->getPoint(row, 0).x;
			x1 = this->getPoint(row, this->width).x;

			k = (x1-x0);
			for (int col = 1; col < this->width; col++){
				p = this->getPoint(row, col);
				p.x = x0 + k * (1.0 + tanh(delta_x * ((p.x-x0)/(x1-x0) - 1))/tanh(delta_x));
				this->setPoint(row, col, p);
			}
		}
	}

	if(delta_y != 0.0){

		double y0, y1;
		double k;
		Point p;
		for (int col = 0; col < this->width+1; col++){
			y0 = this->getPoint(0, col).y;
			y1 = this->getPoint(this->height, col).y;

			k = y1-y0;
			for (int row = 1; row < this->height; row++){
				p = this->getPoint(row, col);
				p.y = y0 + k * (1.0 + tanh(delta_y * ((p.y-y0)/(y1-y0) - 1))/tanh(delta_y));
				this->setPoint(row, col, p);
			}
		}
	}
}

inline Point Domain::getPoint(int row, int col){
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

std::vector<double> Domain::getX() {
  return this->x_coor;
}

std::vector<double> Domain::getY() {
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

