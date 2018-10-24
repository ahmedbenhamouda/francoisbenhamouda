#include "Surface.h"
#include <exception>

namespace render {
	Surface::Surface () {
	}
	Surface::~Surface () {
	}
	void Surface::loadTexture (std::string& image_file) {
		if (!texture.loadFromFile(image_file)) {
			throw std::runtime_error("No such file");
		}
	}
	void Surface::initQuads (int count) {
		quads.setPrimitiveType(sf::Quads);
		quads.resize(count);
	}
	//void Surface::setSpriteLocation (int i, int x, int y) {

	//}
}
