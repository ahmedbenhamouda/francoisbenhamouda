#include "Terrain.h"

namespace state {
	Terrain::Terrain(std::vector<std::vector<Unite*>> unites, std::vector<std::vector<Batiment*>> batiments, TerrainTab sol) {
		this->unites = unites;
		this->batiments = batiments;
		this->sol = sol;
	}
	// Constructeur par defaut
	Terrain::Terrain() {
	}

	Unite* Terrain::getUnite(Position position) {
		return unites[position.getY()][position.getX()];
	}
	Batiment* Terrain::getBatiment(Position position) {
		return batiments[position.getY()][position.getX()];
	}
	TerrainTypeId Terrain::getGround(Position position) {
		return sol.get(position);
	}
	void Terrain::moveUnite(Position pos_init, Position pos_final){
		Unite* unite = this->getUnite(pos_init);
		setUnite(pos_final, unite);
		setUnite(pos_init, nullptr); 
	}
	Terrain::~Terrain() {
	}
	void Terrain::setUnite(Position position, Unite* unite){
		unites[position.getY()][position.getX()] = unite;
	}
}
