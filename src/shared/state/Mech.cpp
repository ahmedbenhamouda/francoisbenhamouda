#include "Mech.h"
#include "Unite.h"
#include <cmath>

namespace state {
	Mech::Mech(){	
	}
	Mech::Mech(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Mech::getLegalMove(){
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
	Mech::~Mech(){
	}
	int Mech::getvie(){
		return this->vie;
	}
	int Mech::getprix(){
		return this->prix;
	}
	int Mech::getmvt(){
		return this->mvt;
	}
	int Mech::getpuissance(){
		return this->puissance;
	}
}
