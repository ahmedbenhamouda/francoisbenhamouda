#include "Infantry.h"
#include "Unite.h"

namespace state {
	Infantry::Infantry(){	
	}
	Infantry::Infantry(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Infantry::getLegalMove(){
	}
	Infantry::~Infantry(){
	}
	int Infantry::getvie(){
		return this->vie;
	}
	int Infantry::getprix(){
		return this->prix;
	}
	int Infantry::getmvt(){
		return this->mvt;
	}
	int Infantry::getpuissance(){
		return this->puissance;
	}
}
