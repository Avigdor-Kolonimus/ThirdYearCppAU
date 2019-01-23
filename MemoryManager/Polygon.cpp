#include "Polygon.h"
#include <cmath>

Polygon::Polygon()
{
    nome="Polygon";
}

Polygon::Polygon(size_t nvtx) : npt(nvtx)
{
    vertex.resize(nvtx);
    nome="PolygonOf"+std::to_string(nvtx)+"Vertexes";
}

double Polygon::perimeter() const 
{
    double ans=0;
    if (vertex.empty()) return 0;
    for (size_t i=1;i<vertex.size();++i) {
        ans+=sqrt((vertex[i]-vertex[i-1])*(vertex[i]-vertex[i-1]));
    }
    ans+=sqrt((vertex.front()-vertex.back())*(vertex.front()-vertex.back()));
    return ans;
}

void Polygon::translate(Point p)
{
    for (auto & pt : vertex) pt += p;
}

void Polygon::rotate(double phi)
{
    Point center;
    for (auto pt : vertex) center += pt;
    center = (1.0/npt)*center;
    double ct=cos(phi),st=sin(phi);
    for (auto & pt : vertex) {
        auto rel = pt - center;
        pt = center + Point(ct*rel.X + st*rel.Y, -st*rel.X+ct*rel.Y);
    }
}

