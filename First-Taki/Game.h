/**
 *Header file of class Game
 *Author Alexey Titov
 *Version 3.0
 *Date 10.2018
**/
//libraries
#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Card.h"
#include <string.h>
#include <vector>
using namespace std;
//defines
extern const string str1;  
extern const string str2;

class Game{
	private:
		int num_cards;				//number of cards
		int num_players;			//number of players
		vector<Player> players; 	//vector of players
		//The function sets the number of cards
		void num_Cards();
		//The function sets the number of players
		void num_Players();
		//The function returns the name of the player
		string name_Player(int)const;
		//The function retruns index of player
		int index_Player(int, int)const;
		//Constructor
		Game(int _num_cards, int _num_players);
		//Copy constructor 
        Game(const Game& g);
		//Overloading for '=' operator for Game type!
        const Game& operator=(const Game& other);
		//The function does not use Player::play(Card&)
		void NoUsePlayStart();
		//The function uses Player::play(Card&)
		void UsePlayStart();
	public:
		//Empty constructor
		Game();
		//Destructor
		~Game();
		//The function creates a game
		void start();
};
#endif




