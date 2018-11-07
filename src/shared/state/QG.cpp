#include "QG.h"


namespace state {
	QG::QG(){	
	}
	QG::QG(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	bool QG::Drapeau_E(){
		return false;
	}
	bool QG::Drapeau(){
		return true;
	}
	int QG::getId_b(){
		return this->id_b;
	}
	int QG::getColor(){
		return this->color;
	}
	int QG::getTileId(){
		return (4*this->getId_b()+this->getColor());
	}
	QG::~QG(){
	}
}
