#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP

class Curvebase {
  protected:
    double _pmin;
    double _pmax;
    bool _rev; // direction of the curve 
    double length;
    virtual double xp(double p) const = 0;
    virtual double yp(double p) const = 0;
    virtual double dxp(double p) const = 0;
    virtual double dyp(double p) const = 0;
    // more members
    double integrate(double p) const; // arc length integral from pmin to p
    void validate_p(double p) const;
    double p_from_s(double p) const;
  public:
    Curvebase(double pmin, double pmax, bool rev);
    double x(double s) const; // arc length parametrization, s in [0,1]
    double y(double s) const; // arc length parametrization, s in [0,1]
    double getLength() const; 
};

#endif