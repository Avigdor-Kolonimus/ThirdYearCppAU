#ifndef Point_HH
#define Point_HH
class ostream;
struct Point
{
    double X=0, Y=0;
    Point() = default;
    Point(const Point &) = default;
    Point(Point &&) = default;
    Point &operator=(const Point &p) = default;
    Point &operator=(Point &&p) = default;
    Point(double x, double y);
    Point &operator+=(const Point &p);
    Point &operator-=(const Point &p);
    Point operator+(const Point &p) const;
    Point operator-(const Point &p) const;
    double operator*(const Point &p) const;
    Point operator*(double f) const ;
};

Point operator*(double f, const Point &p);
//ostream &operator<<(ostream &os, const Point &p);


#endif

