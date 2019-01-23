#include "Point.h"
#include <iostream>

Point::Point(double x, double y) : X{x}, Y{y} {}

Point & Point::operator+=(const Point &p)
{
    X+=p.X;
    Y+=p.Y;
    return *this;
}

Point & Point::operator-=(const Point &p)
{
    X-=p.X;
    Y-=p.Y;
    return *this;
}

Point Point::operator+(const Point &p) const 
{
    return {X+p.X,Y+p.Y};
}

Point Point::operator-(const Point &p) const 
{
    return {X-p.X,Y-p.Y};
}

double Point::operator*(const Point &p) const 
{
    return (X*p.X+Y*p.Y);
}

Point Point::operator*(double f) const
{
    return {f*X, f*Y};
}

Point operator*(double f, const Point &p)
{
    return {f*p.X, f*p.Y};
}

std::ostream & operator<<(std::ostream &os, const Point &p)
{
    os << "(" << p.X << ", " << p.Y << ")";
    return os;
}

