#include <string>
#include "UniteTileSet.h"

namespace render {
	UniteTileSet::UniteTileSet() {
	}
	UniteTileSet::~UniteTileSet() {
	}
	int const UniteTileSet::getWidth() {
		//return terrains[0].width;
		return 16;
	}
	int const UniteTileSet::getHeight() {
		//return terrains[0].height;
		return 16;
	}
	std::string const UniteTileSet::getImageFile() {
		return "res/units.png";
	}
}
