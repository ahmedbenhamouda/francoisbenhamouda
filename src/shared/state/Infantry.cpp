#include "Infantry.h"
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
			int dx = std::abs(x-i);
			for (int j = y-mvt; j <= y+mvt; j++){
				int dy = std::abs(y-j);
				if (dx+dy <= mvt){
					if ((i<8 && i>=0) && (j<8 && j>=0)){
						list.push_back (Position(i,j));
					}
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
	int Infantry::getColor(){
		return this->color;
	}
	int Infantry::getId(){
		return this->id;
	}
	int Infantry::getTileId(){
		return (4*this->getId()+this->getColor());
	}
	void Infantry::setpuissance(int p){
		this->puissance = p;
	}
	void Infantry::setvie(int v){
		this->vie = v;

	}
	void Infantry::attacker(Unite* unite){
		int nvie;
		int np;
		nvie = unite->getvie()-this->getpuissance();
		if (nvie<0) {
			nvie = 0;
		}
		np = int(unite->getpuissance()*float(nvie)/unite->getvie());
		unite->setvie(nvie);
		unite->setpuissance(np);
	}
	void Infantry::move(Position position) {
		this->position = position;
	}
	bool Infantry::PossedeDrapeau() {
		return false;
	}
}
