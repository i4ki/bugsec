#ifndef CURVE_H
#define CURVE_H

#include "point.h"
#include <vector>

class Curve
{
public:
    Curve();
    void addPoint(Point p);
    void addPointByArray(std::vector<Point> p);
    std::vector<Point> getPoints() const { return points; }
    std::vector<double> getElementsX();
    std::vector<double> getElementsY();
    void clear() { points.clear(); }
    Curve & operator=(const Curve & otherCurve);

protected:
    std::vector<Point> points;
};

#endif // CURVE_H
