#ifndef CARD_H
#define CARD_H
#include<string>
#include<iostream>
#include <random>
#include <time.h>
using namespace std;
enum color { NAC, R, G, B, Y }; //enumartion of colors. NAC - is not avaiable color
enum sign { NAS, N1, N2, N3, N4, N5, N6, N7, N8, N9, PLUS, STOP, CD, TAKI }; //enumartion of signs. NAS - is not avaiable sign
class Card {
	color clr;
	sign s;
public:
	Card(color clr = NAC, sign s = NAS) : clr(clr), s(s) {}; //default construtor and init list constructor
	Card(const Card& card) {clr = card.clr; s = card.s;}; //copy constructor
	Card operator=(const Card& card) {clr = card.clr; s = card.s; return *this;}; //operator=
	bool is_leggal(const Card& other_card) const; //check if other card is leggal on this card. if same color or sign retrun true, else return false.
	sign get_sign() const { return s; }
	color get_color() const { return clr; }
	friend ostream& operator << (ostream &os, const Card &c); //operator << for Card. print the sign, colored.
};
Card generate_card(); //return random card
#endif






