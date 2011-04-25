#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point() { }
    Point(double x, double y);
    void setX(double x);
    void setY(double y);
    double getX() const { return _x; }
    double getY() const { return _y; }

protected:
    double _x;
    double _y;
};

#endif // POINT_H
