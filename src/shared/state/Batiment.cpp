#include "Batiment.h"

namespace state {
	Batiment::Batiment(){	
	}
	Batiment::Batiment(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	Batiment::~Batiment(){
	}
}
