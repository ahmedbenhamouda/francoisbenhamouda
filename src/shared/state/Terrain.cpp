#include "Terrain.h"

namespace state {
	Terrain::Terrain(std::vector<Unite*> unites, std::vector<Batiment*> batiments, TerrainTab sol) {
		this->unites = unites;
		this->batiments = batiments;
		this->sol = sol;
	}
	// Constructeur par defaut
	Terrain::Terrain() {
	}

	Unite* Terrain::getUnite(Position position) {
		for (Unite* unit : unites) {
			if (unit->position == position) {
				return unit;
			}
		}
		return nullptr;
	}
	Batiment* Terrain::getBatiment(Position position) {
		for (Batiment* bat : batiments) {
			if (bat->position == position) {
				return bat;
			}
		}
		return nullptr;
	}
	TerrainTypeId Terrain::getGround(Position position) {
		return sol.get(position);
	}
	std::vector<Unite*>& Terrain::getUniteList() {
		return unites;
	}
	std::vector<Batiment*>& Terrain::getBatimentList() {
		return batiments;
	}
	void Terrain::addUnite(Unite* unite){
		unites.push_back(unite);
	}
	void Terrain::deleteUnite(Position pos) {
		Unite* unite = getUnite(pos);
		delete unite;
	}
	Terrain::~Terrain() {
	}
}
