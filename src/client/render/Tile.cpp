#include "Tile.h"

namespace render {
	Tile::Tile() {
	}
	Tile::Tile(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
	}
	Tile::~Tile() {
	}
	int Tile::getX() const  {
		return x;
	}
	int Tile::getY() const  {
		return y;
	}
	int Tile::getWidth() const  {
		return width;
	}
	int Tile::getHeight() const  {
		return height;
	}
}
