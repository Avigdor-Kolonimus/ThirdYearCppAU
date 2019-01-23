#ifndef Polygon_HH
#define Polygon_HH
#include "Shape.h"
#include <vector>

class Polygon : public Shape
{
public:
    Polygon();
    Polygon(size_t nvtx);
    Polygon(const Polygon &) = default;
    Polygon(Polygon &&) = default;
    Polygon & operator=(const Polygon &pg)=default;
    Polygon & operator=(Polygon &&)=default;

    double perimeter() const override final;
    void translate(Point p) override final;
    void rotate(double phi) override;
protected:
    std::vector<Point> vertex;
    size_t npt=0;
};

#endif

