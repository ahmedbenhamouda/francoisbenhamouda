#include "Terrain.h"
#include <algorithm>

namespace state {
	Terrain::Terrain(std::vector<Batiment*> batiments, std::vector<Flag*> flags, TerrainTab sol) {
		Terrain();
		this->batiments = batiments;
		this->flags = flags;
		this->sol = sol;
	}
	// Constructeur par defaut
	Terrain::Terrain() {
		unites = std::vector<Unite*>();
	}

	Unite* Terrain::getUnite(Position position) {
		for (Unite* unit : unites) {
			if (unit and unit->position == position) {
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
	Flag* Terrain::getFlag(Position position) {
		for (Flag* flag : flags) {
			if (flag->position == position) {
				return flag;
			}
		}
		return nullptr;
	}
	TerrainTypeId Terrain::getGround(Position position) {
		return sol.get(position);
	}
	std::vector<Unite*> Terrain::getUniteList() {
		return unites;
	}
	std::vector<Batiment*> Terrain::getBatimentList() {
		return batiments;
	}
	std::vector<Flag*> Terrain::getFlagList() {
		return flags;
	}
	void Terrain::addUnite(Unite* unite){
		unites.push_back(unite);
	}
	void Terrain::deleteUnite(Position pos) {
		Unite* unite = getUnite(pos);
		delete unite;
		unites.erase(std::remove(unites.begin(), unites.end(), unite));
	}
	Terrain::~Terrain() {
	}
}
