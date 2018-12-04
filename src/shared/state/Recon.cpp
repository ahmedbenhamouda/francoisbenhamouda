#include "Recon.h"
#include <cmath>

namespace state {
	Recon::Recon(){	
	}
	Recon::Recon(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	std::vector<Position> Recon::getLegalMove(Terrain* terrain){
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
		int mod=0;
		if (this->has_flag) {
			mod=40;
		}
		return (8*this->getId()+this->getColor()+mod);
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
	bool Recon::isLegalMove(Position pos, Terrain* terrain) {
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
