#ifndef __MM_H_
#define __MM_H_
#include <stddef.h>
#include <set>
#define POOL_SIZE 1000

class MemoryManager{
public:
    MemoryManager();
    ~MemoryManager( );
    void* alloc(size_t);
    void  free(void*);
    int   free_circles();
    int   free_triangles();
private:
    char* CirclePool;
    char* TrianglePool;
    std::set<int> CircleSet;
    std::set<int> TriangleSet;
};
#endif
