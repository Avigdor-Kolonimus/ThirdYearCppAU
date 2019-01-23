#ifndef Triangle_HH
#define Triangle_HH
#include "Polygon.h"

class Triangle : public Polygon
{
public:
    Triangle();
    Triangle(Point p1, Point p2, Point p3);
    Triangle(const Triangle &)=default;
    Triangle(Triangle &&)=default;
    Triangle & operator=(const Triangle &)=default;
    Triangle & operator=(Triangle &&)=default;
    double area() const override;
};

#endif
