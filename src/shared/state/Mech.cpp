#include "Mech.h"
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
					if ((i<8 && i>=0) && (j<8 && j>=0)){
						list.push_back (Position(i,j));
					}
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
	int Mech::getColor(){
		return this->color;
	}
	int Mech::getId(){
		return this->id;
	}
	int Mech::getTileId(){
		return (4*this->getId()+this->getColor());
	}
	void Mech::setpuissance(int p){
		this->puissance = p;
	}
	void Mech::setvie(int v){
		this->vie = v;

	}
	void Mech::attacker(Unite* unite){
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
	void Mech::move(Position position) {
		this->position = position;
	}
	bool Mech::PossedeDrapeau() {
		return false;
	}
}
