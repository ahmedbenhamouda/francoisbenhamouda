#include "HTank.h"
#include "Unite.h"
#include <cmath>

namespace state {
	HTank::HTank(){	
	}
	HTank::HTank(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> HTank::getLegalMove(){
		int mvt = getmvt();
		int x = position.getX();
		int y = position.getY();
		std::vector<Position> list;
		for (int i = x-mvt; i <= x+mvt; i++){
			int dx = std::abs(x-i);
			for (int j = y-mvt; j <= y+mvt; j++){
				int dy = std::abs(y-j);
				if (dx+dy <= mvt){
					list.push_back (Position(i,j));
				}
			}
		}
		return list;
	}
	HTank::~HTank(){
	}
	int HTank::getvie(){
		return this->vie;
	}
	int HTank::getprix(){
		return this->prix;
	}
	int HTank::getmvt(){
		return this->mvt;
	}
	int HTank::getpuissance(){
		return this->puissance;
	}
}
