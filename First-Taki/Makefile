#
# My makefile for first assignment 
# Author Alexey Titov
# Version 3.0
# Date 10.2018
#
CXX=g++
CXXFLAGS=-std=c++0x

a.out: Game.cpp Game.h Player.cpp Player.h Card.cpp Card.h
	$(CXX) $(CXXFLAGS) *.cpp -o a.out

clean:
	rm a.out