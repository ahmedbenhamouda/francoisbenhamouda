#include "HTank.h"
#include "Unite.h"

namespace state {
	HTank::HTank(){	
	}
	HTank::HTank(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> HTank::getLegalMove(){
	}
	HTank::~HTank(){
	}
	int HTank::getvie(){
		return this->vie;
	}
	int HTank::getprix(){
		return this->prix;
	}
	int HTank::getmvt(){
		return this->mvt;
	}
	int HTank::getpuissance(){
		return this->puissance;
	}
}
