#include "Recon.h"
#include "Unite.h"

namespace state {
	Recon::Recon(){	
	}
	Recon::Recon(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Recon::getLegalMove(){
	}
	Recon::~Recon(){
	}
	int Recon::getvie(){
		return this->vie;
	}
	int Recon::getprix(){
		return this->prix;
	}
	int Recon::getmvt(){
		return this->mvt;
	}
	int Recon::getpuissance(){
		return this->puissance;
	}
}
