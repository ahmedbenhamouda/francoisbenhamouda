#include "Tile.h"

namespace render {
	Tile::Tile() {
	}
	Tile::Tile(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
	}
	Tile::~Tile() {
	}
	int Tile::getWidth() {
		return width;
	}
	int Tile::getHeight() {
		return height;
	}
}
