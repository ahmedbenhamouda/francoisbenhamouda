#include "TerrainIdGen.h"

namespace state {
	TerrainIdGen::TerrainIdGen() {
	}
	TerrainIdGen::TerrainIdGen(TerrainTypeId sol) {
		this->sol = sol;
	}
	int TerrainIdGen::getId() {
		return sol;
	}
	TerrainIdGen::~TerrainIdGen() {
	}
}
