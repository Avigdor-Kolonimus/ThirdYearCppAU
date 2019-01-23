#ifndef Shape_HH
#define Shape_HH

#include <string>
#include "Point.h"
#include "MM.h"
extern MemoryManager mm;

class Shape
{
public:
    virtual void rotate(double)=0;
    virtual void translate(Point)=0;
    virtual double area() const =0;
    virtual double perimeter() const =0;
    inline std::string name() const { return nome; }
    virtual ~Shape () {}
    inline void* operator new(size_t size)
    {
        return mm.alloc(size);
    }
    inline void operator delete(void* object)
    {
        mm.free(object);
    }
protected:
    std::string nome;
};
#endif

