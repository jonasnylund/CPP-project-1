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


void Domain::toFile(const char* filename) const{

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
	// if a grid already exists, overwrite this
	this->height = m; this->width = n;
	this->x_coor.resize((this->height + 1)* (this->width + 1));
	this->y_coor.resize((this->height + 1)* (this->width + 1));
	double xi, eta;

	#pragma omp parallel for private(xi, eta)
	for (int i = 0; i < this->height + 1; ++i) {
		// use 1 - i/m since matrices are indexed top -> bottom
		eta = Domain::stretch(1 - i / (double) m, delta);
	
		#pragma GCC ivdep
		for (int j = 0; j < this->width + 1; ++j) {
			xi = j / (double) n;
			this->x_coor[j + i*(this->width + 1)] = this->phi1(xi) * this->boundary[1]->x(1 - eta)
										+ this->phi2(xi) * this->boundary[3]->x(eta)
										+ this->phi1(eta) * (
											this->boundary[2]->x(xi)
											- this->phi1(xi) * this->boundary[2]->x(0)
											- this->phi2(xi) * this->boundary[2]->x(1)
										)
										+ this->phi2(eta) * (
											this->boundary[0]->x(1 - xi)
											- this->phi1(xi) * this->boundary[0]->x(1)
											- this->phi2(xi) * this->boundary[0]->x(0)
										);
			this->y_coor[j + i*(this->width + 1)] = 
										this->phi1(xi) * this->boundary[1]->y(1 - eta)
										+ this->phi2(xi) * this->boundary[3]->y(eta)
										+ this->phi1(eta) * (
											this->boundary[2]->y(xi)
											- this->phi1(xi) * this->boundary[2]->y(0)
											- this->phi2(xi) * this->boundary[2]->y(1)
										)
										+ this->phi2(eta) * (
											this->boundary[0]->y(1 - xi)
											- this->phi1(xi) * this->boundary[0]->y(1)
											- this->phi2(xi) * this->boundary[0]->y(0)
										);
		}
	}
}

double Domain::stretch(const double sigma, const double delta) {
	if (delta == 0)
		return sigma;
	return 1 + tanh(delta * (sigma - 1))/tanh(delta);
}

Point Domain::getPoint(int row, int col) const {
	if (row < 0 || this->height < row)
		throw std::invalid_argument("row argument must be between 0 and this->height+1");
	if (col < 0 || this->width < col)
		throw std::invalid_argument("col argument must be between 0 and this->width+1");

	Point p;
	p.x = this->x_coor[row * (this->width+1) + col];
	p.y = this->y_coor[row * (this->width+1) + col];

	return p;
}

void Domain::setPoint(int row, int col, double x, double y){
	if (row < 0 || this->height < row)
		throw std::invalid_argument("row argument must be between 0 and this->height+1");
	if (col < 0 || this->width < col)
		throw std::invalid_argument("col argument must be between 0 and this->width+1");
	
	this->x_coor[row * (this->width+1) + col] = x;
	this->y_coor[row * (this->width+1) + col] = y;
}

void Domain::setPoint(int row, int col, Point p){
	this->setPoint(row, col, p.x, p.y);
}

double Domain::getX(int row, int col) const{
	return this->x_coor[row * (this->width+1) + col];
}
double Domain::getY(int row, int col) const{
	return this->y_coor[row * (this->width+1) + col];
}

std::vector<double> Domain::getX() const {
	return this->x_coor;
}

std::vector<double> Domain::getY() const {
	return this->y_coor;
}

double Domain::phi1(const double s) {
	// from 1 to 0 when s goes from 0 to 1
	return 1.0 - s;
}

double Domain::phi2(const double s) {
	// from 0 to 1 when s goes from 0 to 1
	return s;
}

int Domain::xsize() const { return this->width; }
int Domain::ysize() const { return this->height; }

bool Domain::grid_valid() { return this->width != 0; }
