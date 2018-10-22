#include <string>
#include "Tile.h"

namespace render {
	Tile::Tile() {
	}
	Tile::~Tile() {
	}
	Tile::Tile(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
	}
	int Tile::getX() const {
		return x;
	}
	int Tile::getY() const {
		return y;
	}
	int Tile::getHeight() const {
		return height;
	}
	int Tile::getWidth() const {
		return width;
	}
}
