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
}
