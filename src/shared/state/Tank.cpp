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
		int mvt = getmvt()+1;
		std::vector<Position> list;
		if (not(can_move)) {
			list.push_back(position);
			return list;
		}
		std::vector<std::vector<int>> liste_moves(2*mvt+1, std::vector<int>(2*mvt+1, 0));
		liste_moves[mvt][mvt] = 1;
		// On crée une position de référence de coordonnées égales au coin supérieur gauche du morceau de map traité
		Position posRef(position.getX()-mvt, position.getY()-mvt);
		processMoves(posRef, mvt, mvt, liste_moves, mvt, terrain);
		
		for (std::size_t i = 0; i<liste_moves.size(); i++) {
			for (std::size_t j = 0; j<liste_moves.size(); j++) {
				if (liste_moves[i][j] == 1) {
					list.push_back(Position(posRef.getX()+i,posRef.getY()+j));
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
