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
	int Position::getX() const {
		return x;
	}
	int Position::getY() const {
		return y;
	}
	void Position::move(int x, int y) {
		this->x = x;
		this->y = y;
	}
	bool Position::operator==(Position const& pos) {
		if (pos.getX() == this->getX() && pos.getY() == this->getY()){
			return true;
		}
		else{
			return false;
		}
	}
	Position::~Position(){
	}
}
