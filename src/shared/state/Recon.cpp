#include "Recon.h"
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
	int Recon::getColor(){
		return this->color;
	}
	int Recon::getId(){
		return this->id;
	}
	int Recon::getTileId(){
		return (4*this->getId()+this->getColor());
	}
	void Recon::setpuissance(int p){
		this->puissance = p;
	}
	void Recon::setvie(int v){
		this->vie = v;

	}
	void Recon::attacker(Unite* unite){
		int nvie;
		int npuissance;
		nvie = unite->getvie()-this->getpuissance();
		if (nvie<0) {
			nvie = 0;
		}
		npuissance = this->getpuissance() * (nvie/this->getvie());
		unite->setvie(nvie);
		unite->setpuissance(npuissance);
	}
	void Recon::move(Position position) {
		this->position = position;
	}
	bool Recon::PossedeDrapeau() {
		return false;
	}
}
