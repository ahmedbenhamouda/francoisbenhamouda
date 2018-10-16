#include "Position.h"

namespace state {
	// Constructeur par defaut
	Position::Position() {
		x = 0;
		y = 0;
	}
	Position::Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int Position::getX() {
		return x;
	}
	int Position::getY() {
		return y;
	}
	void Position::move(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Position::~Position() {
	}
}
