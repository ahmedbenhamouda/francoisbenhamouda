#include "Position.h"
#include <cmath>

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
	bool Position::operator==(Position const& pos) {
		if (pos.getX() == this->getX() && pos.getY() == this->getY()){
			return true;
		}
		else{
			return false;
		}
	}
	int Position::operator-(Position const& pos) {
		int res;
		res = std::abs(pos.getX()-this->getX()) + std::abs(pos.getY()-this->getY());
		return (res);
	}
	bool Position::operator<(Position const& pos) {
		return (this->getX() + this->getY() < pos.getX() + pos.getY());
	}
	Position::~Position(){
	}
}
