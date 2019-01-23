#include "Triangle.h"
#include <cmath>
// A "static" function in a source file (not a static member function of a class)
// is meant to be visible only in the same translation unit, most often just that
// source file. 
static inline double sqr(Point p) { return p*p; }

Triangle::Triangle() : Polygon(3)
{
    nome="Triangle";
}

Triangle::Triangle(Point p1, Point p2, Point p3) : Polygon(3)
{
    nome="Triangle";
    vertex[0]=p1;
    vertex[1]=p2;
    vertex[2]=p3;
}

double Triangle::area() const 
{
    double s=0.5*perimeter();
    double a=sqrt(sqr(vertex[0]-vertex[1]));
    double b=sqrt(sqr(vertex[0]-vertex[2]));
    double c=sqrt(sqr(vertex[1]-vertex[2]));
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

