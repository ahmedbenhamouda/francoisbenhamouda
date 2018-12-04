#include "HTank.h"
#include <cmath>

namespace state {
	HTank::HTank(){	
	}
	HTank::HTank(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> HTank::getLegalMove(Terrain* terrain){
		int mvt = getmvt();
		int x = position.getX();
		int y = position.getY();
		std::vector<Position> list;
		if (not(can_move)) {
			list.push_back(position);
			return list;
		}
		for (int i = x-mvt; i <= x+mvt; i++){
			int dx = std::abs(x-i);
			for (int j = y-mvt; j <= y+mvt; j++){
				int dy = std::abs(y-j);
				if (dx+dy <= mvt){
					if ((i<20 && i>=0) && (j<20 && j>=0) and isLegalMove(Position(i,j), terrain)){
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
		int mod=0;
		if (this->has_flag) {
			mod=40;
		}
		return (8*this->getId()+this->getColor()+mod);
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
	bool HTank::isLegalMove(Position pos, Terrain* terrain) {
		if (terrain->getUnite(pos)) {
			return false;
		}
		TerrainTypeId tti = terrain->getGround(pos);
		if (tti == foret or tti == montagne) {
			return false;
		}
		return true;
	}
}
