#include "QG.h"
#include "Batiment.h"


namespace state {
	QG::QG(){	
	}
	bool QG::Drapeau_E(){
		return false;
	}
	bool QG::Drapeau(){
		return false;
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
