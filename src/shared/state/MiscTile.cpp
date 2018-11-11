#include "MiscTile.h"

using namespace state;

MiscTile::MiscTile() {
}

MiscTile::MiscTile(int tile_id, Position position) {
	this->tile_id = tile_id;
	this->position = position;
}
int MiscTile::getTileId() {
	return tile_id;
}
MiscTile::~MiscTile() {
}
