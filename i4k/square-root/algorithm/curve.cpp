#include "curve.h"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

Curve::Curve()
{

}

Curve & Curve::operator=(const Curve & otherCurve)
{
    points.clear();
    points = otherCurve.getPoints();

    return *this;
}

void Curve::addPoint(Point p)
{
    points.push_back(p);    
}

void Curve::addPointByArray(std::vector<Point> p)
{
    for (unsigned int i = 0; i < p.size(); i++)
		points.push_back(p[i]);	
}

vector<double> Curve::getElementsX()
{
    vector<double> point_x(points.size());
	
	for (unsigned int i = 0; i < points.size(); i++)
	    point_x[i] = points[i].getX();
	
    return point_x;
}

vector<double> Curve::getElementsY()
{
    vector<double> y(points.size());

    for (unsigned int i = 0; i < points.size(); i++)
        y[i] = points[i].getY();

    return y;
}

