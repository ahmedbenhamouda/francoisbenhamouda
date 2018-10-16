#include "Infantry.h"
#include "Unite.h"
#include <cmath>

namespace state {
	Infantry::Infantry(){	
	}
	Infantry::Infantry(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Infantry::getLegalMove(){
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
	Infantry::~Infantry(){
	}
	int Infantry::getvie(){
		return this->vie;
	}
	int Infantry::getprix(){
		return this->prix;
	}
	int Infantry::getmvt(){
		return this->mvt;
	}
	int Infantry::getpuissance(){
		return this->puissance;
	}
}
