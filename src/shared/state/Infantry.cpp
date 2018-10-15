#include "Infantry.h"
#include "Unite.h"

namespace state {
	Infantry::Infantry(Position position, int color) {
		this->position = position;
		this->color = color;
		vie = 100;
		prix = 1000;
		mvt = 3;
		puissance = 60;
	}
	std::vector<Position> Infantry::getLegalMove(){
		if 
	}
}
