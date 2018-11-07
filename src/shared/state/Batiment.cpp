#include "Batiment.h"


namespace state {
	Batiment::Batiment(){	
	}
	Batiment::Batiment(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	int Batiment::getId_b(){
		return this->id_b;
	}
	int Batiment::getColor(){
		return this->color;
	}
	int Batiment::getTileId(){
		return (4*this->getId_b()+this->getColor());
	}
	Batiment::~Batiment(){
	}
	Unite* Batiment::creerU (int id){
		return nullptr;
	}
}
