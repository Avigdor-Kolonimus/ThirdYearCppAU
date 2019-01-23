#include "Circle.h"
#include <cmath>
const double pi = acos(-1);

Circle::Circle(double rad, const Point & p) : r{rad}, c{p} 
{
    nome="circle";
}

double Circle::area() const 
{
    return pi*r*r;
}

double Circle::perimeter() const
{
    return 2*pi*r;
}

void Circle::rotate(double phi) {phi=0;}

void Circle::translate(Point p) 
{
    c += p;
}

