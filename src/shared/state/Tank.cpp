#include "Tank.h"
#include <cmath>

namespace state {
	Tank::Tank(){	
	}
	Tank::Tank(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Tank::getLegalMove(Terrain* terrain){
		int mvt = getmvt();
		int x = position.getX();
		int y = position.getY();
		std::vector<Position> list;
		if (not(can_move)) {
			list.push_back(position);
			return list;
		}
		for (int i = x-mvt; i <= x+mvt; i++){
			int dx = std::fabs(x-i);
			for (int j = y-mvt; j <= y+mvt; j++){
				int dy = std::fabs(y-j);
				if (dx+dy <= mvt){
					if ((i<20 && i>=0) && (j<20 && j>=0) and isLegalMove(Position(i,j), terrain)){
						list.push_back (Position(i,j));
					}
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
		int mod=0;
		if (this->has_flag) {
			mod=40;
		}
		return (8*this->getId()+this->getColor()+mod);
	}
	void Tank::setpuissance(int p){
		this->puissance = p;
	}
	void Tank::setvie(int v){
		this->vie = v;

	}
	void Tank::attacker(Unite* unite){
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
	void Tank::move(Position position) {
		this->position = position;
	}
	bool Tank::isLegalMove(Position pos, Terrain* terrain) {
		if (terrain->getUnite(pos)) {
			return false;
		}
		TerrainTypeId tti = terrain->getGround(pos);
		if (tti == montagne) {
			return false;
		}
		return true;
	}
}
