CXX=c++
CXXFLAGS=-std=c++17

a.out: Card.cpp Card.h Player.cpp Player.h Game.cpp Game.h main.cpp
	$(CXX) $(CXXFLAGS) Card.cpp Player.cpp Game.cpp main.cpp -o a.out
	
run:	
	./a.out

clean:
	rm a.out