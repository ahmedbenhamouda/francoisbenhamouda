#include <string>
#include "BatimentTileSet.h"

namespace render {
	BatimentTileSet::BatimentTileSet() {
	}
	BatimentTileSet::~BatimentTileSet() {
	}
	int const BatimentTileSet::getWidth() {
		//return terrains[0].width;
		return 16;
	}
	int const BatimentTileSet::getHeight() {
		//return terrains[0].height;
		return 31;
	}
	std::string const BatimentTileSet::getImageFile() {
		return "res/batiments.png";
	}
}
