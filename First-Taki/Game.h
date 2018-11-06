/* Noa Hadad 305134694 */
#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include <list>
#include <vector>

//libraries if you want use string
#include <stdio.h>
#include <string.h>

class Game {
private:
	//private members and functions
	//VERY BAD
	// Game();
	Game(const Game& other)=delete;
	const Game& operator=(const Game& other)=delete;
	
	int turn;
	int direction;
	Card current;
	list<Player> pl;
	static Game g;

public:
	//public members and functions
	//THIS IS GOOD
	Game();
	// Game(const Game& other)=delete;
	// const Game& operator=(const Game& other)=delete;
	//
	static Game* getInstance();
	Card getCurrent() const;
	void setCurrent(Card current);
	void turnPlus(int plus);
	int getTurn() const;
	void changeDirection();
	int getDirection() const;
	void start();

};
#endif



