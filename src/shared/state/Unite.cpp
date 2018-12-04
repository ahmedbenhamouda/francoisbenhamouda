#include "Unite.h"
#include <cmath>

namespace state {
	Unite::Unite(){	
	}
	Unite::Unite(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Unite::getLegalMove(Terrain* terrain){
		int mvt = getmvt();
		int x = position.getX();
		int y = position.getY();
		std::vector<Position> list;
		for (int i = x-mvt; i <= x+mvt; i++){
			int dx = std::fabs(x-i);
			for (int j = y-mvt; j <= y+mvt; j++){
				int dy = std::fabs(y-j);
				if (dx+dy <= mvt){
					if ((i<20 && i>=0) && (j<20 && j>=0)){
						list.push_back (Position(i,j));
					}
				}
			}
		}
		return list;
	}
	Unite::~Unite(){
	}
	int Unite::getvie(){
		return this->vie;
	}
	int Unite::getprix(){
		return this->prix;
	}
	int Unite::getmvt(){
		return this->mvt;
	}
	int Unite::getpuissance(){
		return this->puissance;
	}
	int Unite::getColor(){
		return this->color;
	}
	int Unite::getId(){
		return this->id;
	}
	int Unite::getTileId(){
		int mod=0;
		if (this->has_flag) {
			mod=40;
		}
		return (8*this->getId()+this->getColor()+mod);
	}
	void Unite::setpuissance(int p){
		this->puissance = p;
	}
	void Unite::setvie(int v){
		this->vie = v;
	}
	void Unite::attacker(Unite* unite){
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
	void Unite::move(Position position) {
		this->position = position;
	}
	Flag* Unite::PossedeDrapeau() {
		return has_flag;
	}
	// This method is virtual anyway
	bool Unite::isLegalMove(Position pos, Terrain* terrain) {
		return true;
	}
	void Unite::processMoves(Position posInit, int dx, int dy, std::vector<std::vector<int>>& processed, int moves_left, Terrain* terrain) {
		if (moves_left > 0) {
			Position newPos(posInit.getX()+dx, posInit.getY()+dy);
			int px = newPos.getX();
			int py = newPos.getY();
			// Out of bounds
			if (px < 0 or px >= 20 or py < 0 or py >= 20) {
				processed[dx][dy] -= 1;
				return;
			} 
			if (processed[dx][dy] == 1 or isLegalMove(newPos,terrain)) {
				processed[dx][dy] = 1;
				processMoves(posInit, dx+1, dy, processed, moves_left-1, terrain);
				processMoves(posInit, dx-1, dy, processed, moves_left-1, terrain);
				processMoves(posInit, dx, dy+1, processed, moves_left-1, terrain);
				processMoves(posInit, dx, dy-1, processed, moves_left-1, terrain);
			} else {
				processed[dx][dy] = -1;
			}
		}
	}
}
