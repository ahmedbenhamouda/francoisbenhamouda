#include "Flag.h"

namespace state {
	Flag::Flag() {
	}
	Flag::Flag(Position position, int color) {
		this->position = position;
		this->color = color;
	}
	int Flag::getTileId() {
		return color;
	}
	Flag::~Flag() {
	}
}
