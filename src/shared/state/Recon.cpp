#include "Recon.h"
#include "Unite.h"
#include <cmath>

namespace state {
	Recon::Recon(){	
	}
	Recon::Recon(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Recon::getLegalMove(){
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
	Recon::~Recon(){
	}
	int Recon::getvie(){
		return this->vie;
	}
	int Recon::getprix(){
		return this->prix;
	}
	int Recon::getmvt(){
		return this->mvt;
	}
	int Recon::getpuissance(){
		return this->puissance;
	}
}
