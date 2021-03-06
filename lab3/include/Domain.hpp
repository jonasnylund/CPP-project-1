#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "Curvebase.hpp"
#include <cstdio>
#include <vector>


typedef struct {
	double x;
	double y;
} Point;



class Domain {

public:

	static bool closedDomain(Curvebase* curves[], int len);
	// static Domain fromFile(FILE *file);

	Domain(Curvebase& c1, Curvebase& c2, Curvebase& c3, Curvebase& c4);
	Domain(const Domain& d);
	Domain& operator=(Domain& d);

	bool operator==(Domain& d) const;
	bool operator!=(Domain& d) const;

	void generate_grid(const int m, const int n, const double delta=0.0);
	void toFile(const char* filename) const;

	Point getPoint(int row, int col) const;
	double getX(int row, int col) const;
	double getY(int row, int col) const;

	std::vector<double> getX() const;
	std::vector<double> getY() const;

	int xsize() const;
	int ysize() const;

	bool grid_valid();
	
private:
	Curvebase *boundary[4];

	std::vector<double> x_coor;
	std::vector<double> y_coor;

	int width; // n
	int height; // m

	static double phi1(const double s); // from 1 to 0
	static double phi2(const double s); // from 0 to 1
	static double stretch(const double sigma, const double delta);
	void setPoint(int row, int col, double x, double y);
	void setPoint(int row, int col, Point p);
};

#endif //DOMAIN_HPP





