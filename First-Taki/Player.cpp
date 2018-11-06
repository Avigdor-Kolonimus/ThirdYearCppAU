/* Noa Hadad 305134694 */

#include "Player.h"

#include "Game.h"	//solution to the problem

Player::Player(char* name, int num_of_cards):num_of_cards(num_of_cards){
	this->name = new char[strlen(name) + 1];
	//GCC (or rather, glibc) does not support strcpy_s() and friends
	//strcpy_s(this->name, strlen(name) + 1, name);
	strncpy(this->name, name, strlen(name) + 1);
	for (int i=0;i<num_of_cards;i++)
	    cards.push_back(generate_card());
}

Player::Player(const Player& other) {
	num_of_cards = other.num_of_cards;
	delete name;
	name = new char[strlen(other.name) + 1];
	//GCC (or rather, glibc) does not support strcpy_s() and friends
	//strcpy_s(this->name, strlen(other.name) + 1, other.name);
	strncpy(this->name, other.name, strlen(other.name) + 1);

	cards.clear();
	vector<Card>::const_iterator iter = (other.cards).begin();
	for (int i = 0; i < other.num_of_cards; i++) {
		cards.push_back(*iter);
		iter++;
	}
}

const Player& Player::operator=(const Player& other) {
	num_of_cards = other.num_of_cards;
	delete name;
	name = new char[strlen(other.name) + 1];
	//GCC (or rather, glibc) does not support strcpy_s() and friends
	//strcpy_s(this->name, strlen(other.name) + 1, other.name);
	strncpy(this->name, other.name, strlen(other.name) + 1);
	
	cards.clear();
	vector<Card>::const_iterator iter = (other.cards).begin();
	for (int i = 0; i < other.num_of_cards; i++) {
		cards.push_back(*iter);
		iter++;
	}
	return *this;
}

char* Player::getName() const {
	return name;
}

int Player::getNumOfCards() const {
	return num_of_cards;
}

 const vector<Card>& Player::getCards() const{
	return cards;
}


bool Player::play(Card& current) {
	bool flag = true;
	do {
		int choice;
		cin >> choice;
		Game *game = Game::getInstance();
		if (choice <= 0 || choice > num_of_cards) {
			if ((*game).getDirection() == 0) (*game).turnPlus(1);
			else (*game).turnPlus(-1);
			cards.push_back(generate_card());
			num_of_cards++;
			return false;
		}
		vector<Card>::iterator itr_cards = cards.begin();
		for (int i = 1; i < choice; i++) itr_cards++;
		if ((*itr_cards).is_leggal(current)) {
			Card card = *itr_cards;
			cards.erase(itr_cards);
			num_of_cards--;
			if ((*game).getDirection() == 0) {
				if (card.get_sign() == STOP) { (*game).turnPlus(2); }
				else if (card.get_sign() == CD) { (*game).turnPlus(-1); (*game).changeDirection(); }
				else if (card.get_sign() != PLUS) { (*game).turnPlus(1); }
			}
			else {
				if (card.get_sign() == STOP) { (*game).turnPlus(-2); }
				else if (card.get_sign() == CD) { (*game).turnPlus(1); (*game).changeDirection(); }
				else if (card.get_sign() != PLUS) { (*game).turnPlus(-1); }
			}
			(*game).setCurrent(card);
			return true;
		}
		else {
			cout << "you can't put " << current << " on " << (*itr_cards) << endl;
		}
	} while (flag);
	return false;
}

bool Player::victory() const{
	return (num_of_cards == 0);
}

Player::~Player() {
	delete name;
	cards.clear();
}
