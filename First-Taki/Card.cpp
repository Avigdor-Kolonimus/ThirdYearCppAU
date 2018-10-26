#include "Card.h"
//#define RANDOM
#define WINDOWS
#ifdef WINDOWS
#include <windows.h>
#endif
Card generate_card() {
#ifdef RANDOM
	return Card(color(rand() % 4 + 1), sign(rand() % 13 + 1));
#else
	static int counter = 0;
	counter++;
	return Card(color(counter % 2 + 1), sign(counter % 5 + 8));
#endif

}
bool Card::is_leggal(const Card& other) const {
	bool ret = false;
	ret |= (get_color() == other.get_color());
	ret |= (get_sign() == other.get_sign());
	return ret;
}
ostream& operator << (ostream &os, const Card &c) {
#ifdef WINDOWS
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	switch (c.clr) {
	case R:
		SetConsoleTextAttribute(hstdout, 0x7C);
		break;
	case G:
		SetConsoleTextAttribute(hstdout, 0x7A);
		break;
	case B:
		SetConsoleTextAttribute(hstdout, 0x79);
		break;
	case Y:
		SetConsoleTextAttribute(hstdout, 0x7E);
		break;
	default:
		os << c.clr << " error";
	}

	switch (c.s) {
	case PLUS:
		os << "+";
		break;
	case STOP:
		os << "STP";
		break;
	case CD:
		os << "-><-";
		break;
	case TAKI:
		os << "TAKI";
		break;
	default:
		os << c.s;
	}

	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
#else
	switch (c.clr) {
	case R:
		os << "R-";
		break;
	case G:
		os << "G-";
		break;
	case B:
		os << "B-";
		break;
	case Y:
		os << "Y-";
		break;
	default:
		os << c.clr << " error";
	}

	switch (c.s) {
	case PLUS:
		os << "+";
		break;
	case STOP:
		os << "STP";
		break;
	case CD:
		os << "-><-";
		break;
	case TAKI:
		os << "TAKI";
		break;
	default:
		os << c.s;
	}
#endif
	return os;
}
