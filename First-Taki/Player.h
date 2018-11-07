/**
 *Header file of class  Player
 *Author Alexey Titov
 *Version 3.0
 *Date 10.2018
**/
//libraries
#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <string.h>
#include <vector>
//define
extern const string str3;
using namespace std;

class Player {
	private:
		string name;			//name of gamer
		int num_of_cards;		//number of cards
		vector<Card> cards; 	//vector of cards
		//The function allows the player to lay out additional cards 
		int taki_card(Card&);
	public:
		//Empty constructor
		Player();
		//Constructor 1
		Player(string, int);
		//Constructor 2
		Player(char*, int);
		//Copy constructor 
        Player(const Player&);
		//Overloading for '=' operator for player type!
        const Player& operator=(const Player&);
		//Destructor
		~Player();
		//The function return name of player
		string getName()const;
		//The function return size of vector<Card> cards
		int getCards()const;
		//The function prints cards that the player has
		void your_Turn()const;
		//The function return option for game
		int choice(Card&);
		//The function is responsible for the turn of the game, 
		//returns true if the player threw a card and false if the player took a card
		bool play(Card&);
};
#endif



