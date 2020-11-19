#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "Curvebase.hpp"
#include <cstdio>
#include <vector>

class Domain {

public:

	static bool closedDomain(Curvebase* curves[], int len);
	// static Domain fromFile(FILE *file);

	Domain(Curvebase& c1, Curvebase& c2, Curvebase& c3, Curvebase& c4);
	Domain(const Domain& d);
	Domain& operator=(Domain& d);

	~Domain();
	void generate_grid(int m, int n);
	void toFile(const char* filename);
	std::vector<double> getX();
  std::vector<double> getY();
private:
	Curvebase *boundary[4];

	std::vector<double> x_coor;
	std::vector<double> y_coor;

	int width; // n
	int height; // m

	double phi1(const double s); // from 1 to 0
	double phi2(const double s); // from 0 to 1
};


#endif //DOMAIN_HPP





