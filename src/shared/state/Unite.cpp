#include "Unite.h"
#include <cmath>

namespace state {
	Unite::Unite(){	
	}
	Unite::Unite(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Unite::getLegalMove(){
		int mvt = getmvt();
		int x = position.getX();
		int y = position.getY();
		std::vector<Position> list;
		for (int i = x-mvt; i <= x+mvt; i++){
			int dx = std::fabs(x-i);
			for (int j = y-mvt; j <= y+mvt; j++){
				int dy = std::fabs(y-j);
				if (dx+dy <= mvt){
					list.push_back (Position(i,j));
				}
			}
		}
		return list;
	}
	Unite::~Unite(){
	}
	int Unite::getvie(){
		return this->vie;
	}
	int Unite::getprix(){
		return this->prix;
	}
	int Unite::getmvt(){
		return this->mvt;
	}
	int Unite::getpuissance(){
		return this->puissance;
	}
	int Unite::getColor(){
		return this->color;
	}
	int Unite::getId(){
		return this->id;
	}
	int Unite::getTileId(){
		return (4*this->getId()+this->getColor());
	}
}
