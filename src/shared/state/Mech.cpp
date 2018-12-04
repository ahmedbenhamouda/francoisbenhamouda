#include "Mech.h"
#include <cmath>

namespace state {
	Mech::Mech(){	
	}
	Mech::Mech(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Mech::getLegalMove(Terrain* terrain){
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
		int mod=0;
		if (this->has_flag) {
			mod=40;
		}
		return (8*this->getId()+this->getColor()+mod);
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
	bool Mech::isLegalMove(Position pos, Terrain* terrain) {
		if (terrain->getUnite(pos)) {
			return false;
		}
		return true;
	}
}
