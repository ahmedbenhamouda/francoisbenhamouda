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
}
