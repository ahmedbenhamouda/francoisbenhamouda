#include "Mech.h"
#include "Unite.h"

namespace state {
	Mech::Mech(){	
	}
	Mech::Mech(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Mech::getLegalMove(){
	}
	Mech::~Mech(){
	}
	int Mech::getvie(){
		return this->vie;
	}
	int Mech::getprix(){
		return this->prix;
	}
	int Mech::getmvt(){
		return this->mvt;
	}
	int Mech::getpuissance(){
		return this->puissance;
	}
}
