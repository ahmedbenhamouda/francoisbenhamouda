#include <string>
#include "TerrainTileSet.h"

namespace render {
	TerrainTileSet::TerrainTileSet() {
		Tile route(400,0,16,16);
		Tile plaine(16,16,16,16);
		Tile foret(240,16,16,16);
		Tile montagne(48,0,16,16);
		std::vector<Tile> newTiles {route,plaine,foret,montagne};
		terrains = newTiles;
	}
	TerrainTileSet::~TerrainTileSet() {
	}
	int const TerrainTileSet::getCellWidth() {
		return terrains[0].getWidth();
	}
	int const TerrainTileSet::getCellHeight() {
		return terrains[0].getHeight();
	}
	std::string const TerrainTileSet::getImageFile() {
		return "res/terrain.png";
	}
}
