#import <string>
#import "TerrainTileSet.h"

namespace render {
	TerrainTileSet::TerrainTileSet() {
	}
	TerrainTileSet::~TerrainTileSet() {
	}
	int const TerrainTileSet::getCellWidth() {
		//return terrains[0].width;
		return 16;
	}
	int const TerrainTileSet::getCellHeight() {
		//return terrains[0].height;
		return 16;
	}
	std::string const TerrainTileSet::getImageFile() {
		return "res/terrain.png";
	}
}
