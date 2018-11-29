#include "Usine.h"
#include "Infantry.h"
#include "Recon.h"
#include "Mech.h"
#include "Tank.h"
#include "HTank.h"

namespace state {
	Usine::Usine(){	
	}
	Usine::Usine(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	Unite* Usine::creerU(int id){
		if (id == 0){
			return (new Infantry(this->position, this->color));
		}
		else if (id == 1){
			return (new Mech(this->position, this->color));
		}
		else if (id == 2){
			return (new Recon(this->position, this->color));
		}
		else if (id == 3){
			return (new Tank(this->position, this->color));
		}
		else if (id == 4){
			return (new HTank(this->position, this->color));
		}
		else{
			return nullptr;
		}
	}
	int Usine::getId_b(){
		return this->id_b;
	}
	int Usine::getColor(){
		return this->color;
	}
	int Usine::getTileId(){
		return (4*this->getId_b()+this->getColor());
	}
	Usine::~Usine(){
	}
}
