#include "HTank.h"
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
					if ((i<20 && i>=0) && (j<20 && j>=0)){
						list.push_back (Position(i,j));
					}
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
	int HTank::getColor(){
		return this->color;
	}
	int HTank::getId(){
		return this->id;
	}
	int HTank::getTileId(){
		return (4*this->getId()+this->getColor());
	}
	void HTank::setpuissance(int p){
		this->puissance = p;
	}
	void HTank::setvie(int v){
		this->vie = v;

	}
	void HTank::attacker(Unite* unite){
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
	void HTank::move(Position position) {
		this->position = position;
	}
	bool HTank::PossedeDrapeau() {
		return false;
	}
}
