#include "Terrain.h"

namespace state {
	Terrain::Terrain(std::map<Position, Unite> unites, std::map<Position, Batiment> batiments, TerrainTab sol) {
		this->unites = unites;
		this->batiments = batiments;
		this->sol = sol;
	}
	Unite& Terrain::getUnite(Position position) {
		if (unites.count(position)>0) {
			return unites[position];
		} 
		return;
	}
	Batiment& Terrain::getBatiment(Position position) {
		if (batiments.count(position)>0) {
			return batiments[position];
		} 
		return;
	}
	TerrainTypeId Terrain::getGround(Position position) {
		return sol.get(position);
	}
	Terrain::~Terrain() {
	}
}
