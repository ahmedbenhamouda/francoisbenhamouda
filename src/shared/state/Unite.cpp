#include "Unite.h"

namespace state {
	Unite::Unite(){	
	}
	Unite::Unite(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Unite::getLegalMove(){
		
	}
	Unite::~Unite(){
	}
	int Unite::getvie(){
		return this->vie;
	}
	int Unite::getprix(){
		return this->prix;
	}
	int Unite::getmvt(){
		return this->mvt;
	}
	int Unite::getpuissance(){
		return this->puissance;
	}
}
