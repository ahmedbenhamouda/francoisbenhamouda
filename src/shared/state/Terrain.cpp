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
		return unites[position.getX()][position.getY()];
	}
	Batiment* Terrain::getBatiment(Position position) {
		return batiments[position.getX()][position.getY()];
	}
	TerrainTypeId Terrain::getGround(Position position) {
		return sol.get(position);
	}
	Terrain::~Terrain() {
	}
}