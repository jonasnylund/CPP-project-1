#include "Domain.hpp"

bool Domain::closedDomain(Curvebase* curves[], int len){

	Curvebase *prev = curves[len-1];
	Curvebase *current = nullptr;
	for (int i = 0; i < len-1; ++i){
		current = curves[i];
		if (! (prev->x(1) == current->x(0) && prev->y(1) == current->y(0))){
			return false;
		}
	}
	return true;
}


Domain::Domain(Curvebase& c1, Curvebase& c2, Curvebase& c3, Curvebase& c4){

	Curvebase *arr[] = {&c1, &c2, &c3, &c4};
	if (!Domain::closedDomain(arr, 4)){
		return;
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


void Domain::generate_grid(int m, int n){



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


