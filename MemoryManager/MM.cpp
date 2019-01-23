/**
*Cpp file of class MemoryManager
*Author Alexey Titov
*Version 1.0
*Date 01.2019
**/
//libraries
#include <iostream>
#include "MM.h"
#include "Triangle.h"
#include "Circle.h"
using namespace std;
MemoryManager mm;
//constructor of Memmory Manager class, POOL_SIZE=1000 
MemoryManager::MemoryManager(){
    CirclePool = (char *) malloc (POOL_SIZE * sizeof(Circle));
    //add items to the Circle set
    for(int i = 0; i < POOL_SIZE; i++) {
        CircleSet.insert(i);
    }
    TrianglePool = (char *) malloc (POOL_SIZE * sizeof(Triangle));
    //add items to the Triangle set
    for(int i = 0; i < POOL_SIZE; i++) {
        TriangleSet.insert(i);
    }
}
//destructor of Memory Manager class
MemoryManager::~MemoryManager( ){
    CircleSet.clear();
    free(CirclePool);
    CirclePool = nullptr;
    TriangleSet.clear();
    free(TrianglePool);
    TrianglePool = nullptr;
}
//this function alloc memory for shape
void* MemoryManager::alloc(size_t needblock){
    size_t sizeOFcircle = sizeof(Circle);
    size_t sizeOFtriangle = sizeof(Triangle);
    //create Circle
    if (sizeOFcircle == needblock && !CircleSet.empty()){
        auto someElementIterator = CircleSet.begin();
        int index = *someElementIterator;
        CircleSet.erase(someElementIterator);
        return CirclePool + (index * sizeof(Circle));
    }
    //create Trinagle
    if (sizeOFtriangle == needblock && !TriangleSet.empty()){
        auto someElementIterator = TriangleSet.begin();
        int index = *someElementIterator;
        TriangleSet.erase(someElementIterator);
        return TrianglePool + (index * sizeof(Triangle));
    }
    //size of needblock is incorrect or memory pool is empty
    cerr << "out of memory" << endl;
	throw bad_alloc();
}
//this function free memory
void MemoryManager::free(void* m){
    // Check for null pointer
    if(!m) 
        return;
    // Assume it was created in the pool
	// Calculate which block number it is:
	unsigned long int blockC = (unsigned long int) m - (unsigned long int) CirclePool;
	blockC /= sizeof(Circle);
    unsigned long int blockT = (unsigned long int) m - (unsigned long int) TrianglePool;
	blockT /= sizeof(Triangle);
    if (blockC >= 0 && blockC < POOL_SIZE){
        CircleSet.insert(blockC);
        return;
    }
    if (blockT >= 0 && blockT < POOL_SIZE){
        TriangleSet.insert(blockT);
    }
}
//this function get number of free circles
int MemoryManager::free_circles(){
    return CircleSet.size();
}
//this function get number of free triangles
int MemoryManager::free_triangles(){
    return TriangleSet.size();
}
