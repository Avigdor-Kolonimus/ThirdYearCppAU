/* Noa Hadad 305134694 */
#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <vector>
//#include "Game.h"   it is prohibited, problem with libraries

////libraries if you want use string
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

class Player {
private:
	//private members
	char* name;
	int num_of_cards;
	vector<Card> cards;//vector of cards

public:
	//public members
	Player(char* name, int num_of_cards);
	Player(const Player& other);
	const Player& operator=(const Player& other);
	char* getName() const;
	int getNumOfCards() const;
	const vector<Card>& getCards() const ;
	bool play(Card&);
	bool victory() const;
	~Player();
};
#endif
