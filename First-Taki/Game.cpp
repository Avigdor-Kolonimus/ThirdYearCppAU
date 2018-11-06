/* Noa Hadad 305134694 */

#include "Game.h"


Game::Game() {
	turn = 1;
	current = generate_card();
	direction = 0;
}

Game Game::g;

Game* Game::getInstance() {
	return &g;
}

Card Game::getCurrent() const {
	return current;
}

void Game::setCurrent(Card current) {
	this->current = current;
}

void Game::turnPlus(int plus) {
	turn = turn + plus;
}

int Game::getTurn() const {
	return turn;
}

void Game::changeDirection() {
	if (direction == 0) direction = 1;
	else direction = 0;
}
int Game::getDirection() const {
	return direction;
}

void Game::start() {

	int numOfPlayers, numOfCards;
	cout << "How many players?" << endl;
	cin >> numOfPlayers;
	cout << "How many cards?" << endl;
	cin >> numOfCards;
	char name1[100];
	Player** p = new Player*[numOfPlayers];
	for (int i = 1; i <= numOfPlayers; i++) {
		cout << "Player number " << i << " name?" << endl;
		cin >> name1;
		p[i - 1] = new Player(name1, numOfCards);
		pl.push_back(*(p[i - 1]));
	}
	list<Player>::iterator itr_player = pl.begin();
	bool flag = false;
	while (!flag) {
		if (direction == 0) {
			if (turn > numOfPlayers) turn = turn % numOfPlayers;
			itr_player = pl.begin();
			for (int i = 1; i < turn; i++) itr_player++;
		}
		else {
			if (turn <= 0) turn = turn + numOfPlayers;
			itr_player = pl.begin();
			for (int i = 1; i < turn; i++) itr_player++;
		}
		cout << "current: " << current << endl;
		cout << (*itr_player).getName() << ", your turn -" << endl;
		cout << "Your cards: ";
		vector<Card>::const_iterator itr_cards = (*itr_player).getCards().begin();
		for (int i = 1; i <= (*itr_player).getNumOfCards(); i++) {
			cout << "(" << i << ")" << (*itr_cards) << " ";
			itr_cards++;
		}
		cout << endl;
		if ((*itr_player).play(current)) {
			if ((*itr_player).victory()) {
				cout << (*itr_player).getName() << " wins!" << endl;
				flag = true;
			}
		}

	}

}