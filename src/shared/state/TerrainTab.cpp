#include "TerrainTab.h"

namespace state {
	TerrainTab::TerrainTab(std::vector<std::vector<TerrainTypeId>> grid) {
		this->grid = grid;
	}
	// Constructeur par defaut
	TerrainTab::TerrainTab() {
		std::vector<std::vector<TerrainTypeId>> defaultVector;
		this->grid = defaultVector;
	}
	TerrainTypeId TerrainTab::get(Position position) {
		return this->grid[position.getX()][position.getY()];
	}
	TerrainTab::~TerrainTab() {
	}
}
