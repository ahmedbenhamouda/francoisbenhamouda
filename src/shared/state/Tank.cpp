#include "Tank.h"
#include "Unite.h"
#include <cmath>

namespace state {
	Tank::Tank(){	
	}
	Tank::Tank(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Tank::getLegalMove(){
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
	Tank::~Tank(){
	}
	int Tank::getvie(){
		return this->vie;
	}
	int Tank::getprix(){
		return this->prix;
	}
	int Tank::getmvt(){
		return this->mvt;
	}
	int Tank::getpuissance(){
		return this->puissance;
	}
	int Tank::getColor(){
		return this->color;
	}
	int Tank::getId(){
		return this->id;
	}
	int Tank::getTileId(){
		return (4*this->getId()+this->getColor());
	}
}
