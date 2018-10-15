#include "Tank.h"
#include "Unite.h"

namespace state {
	Tank::Tank(){	
	}
	Tank::Tank(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Tank::getLegalMove(){
	}
	Tank::~Tank(){
	}
	int Tank::getvie(){
		return this->vie;
	}
	int Tank::getprix(){
		return this->prix;
	}
	int Tank::getmvt(){
		return this->mvt;
	}
	int Tank::getpuissance(){
		return this->puissance;
	}
}
