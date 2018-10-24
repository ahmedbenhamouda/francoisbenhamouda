#include "TerrainTile.h"

namespace state {
	TerrainTile::TerrainTile() {
	}
	TerrainTile::TerrainTile(TerrainTypeId tti) {
		this->terraintypeid = tti;
	}
	TerrainTile::~TerrainTile() {
	}
	int TerrainTile::getTileId() {
		return terraintypeid;
	}
}
