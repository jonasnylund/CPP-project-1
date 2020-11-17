#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP

class Curvebase {
  protected:
    double _pmin;
    double _pmax;
    bool _rev; // direction of the curve
    double length;
    virtual double xp(double p) = 0;
    virtual double yp(double p) = 0;
    virtual double dxp(double p) = 0;
    virtual double dyp(double p) = 0;
    // more members
    double integrate(double p); // arc length integral from pmin to p
    void validate_p(double p);
    double p_from_s(double p);
  public:
    Curvebase(double pmin, double pmax, bool rev);
    double x(double s); // arc length parametrization, s in [0,1]
    double y(double s); // arc length parametrization, s in [0,1]
    double getLength();
};

#endif