#ifndef Circle_HH
#define Circle_HH
#include "Point.h"
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle() = default; 
    Circle(double rad, const Point & p);
    Circle(const Circle &cir) = default;
    Circle(Circle &&cir) = default;
    Circle &operator=(const Circle &cir) = default;
    Circle &operator=(Circle &&cir) = default;
    void rotate(double phi) override;
    void translate(Point p) override;
    double area() const override; 
    double perimeter() const override;
    inline double circumference() const { return perimeter(); }
private:
    double r=1.0;
    Point c{}; // Use default constructor of class Point to create c
};

#endif

