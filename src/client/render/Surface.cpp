#include "Surface.h"
#include <exception>

namespace render {
	Surface::Surface () {
	}
	Surface::~Surface () {
	}
	void Surface::loadTexture (std::string image_file) {
		if (!texture.loadFromFile(image_file)) {
			throw std::runtime_error("No such file");
		}
	}
	void Surface::initQuads (int count) {
		quads.setPrimitiveType(sf::Quads);
		quads.resize(count);
	}
	void Surface::setSpriteLocation (int posx, int posy, int map_size, int tile_size) {
		sf::Vertex* quad = &quads[(posx+posy*map_size)*4];
		quad[0].position = sf::Vector2f(posx*map_size,posy*map_size);
		quad[1].position = sf::Vector2f((posx+1)*map_size,posy*map_size);
		quad[2].position = sf::Vector2f((posx+1)*map_size,(posy+1)*map_size);
		quad[3].position = sf::Vector2f(posx*map_size,(posy+1)*map_size);
	}
	void Surface::setSpriteTexture (int posx, int posy, int map_size, const Tile& tex) {
		sf::Vertex* quad = &quads[(posx+posy*map_size)*4];
		quad[0].texCoords = sf::Vector2f(tex.getX(),tex.getY());
		quad[1].texCoords = sf::Vector2f(tex.getX()+tex.getWidth(),tex.getY());
		quad[2].texCoords = sf::Vector2f(tex.getX()+tex.getWidth(),tex.getY()+tex.getHeight());
		quad[3].texCoords = sf::Vector2f(tex.getX(),tex.getY()+tex.getHeight());
	}
	void Surface::draw (sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		states.texture = &texture;

		// et on dessine enfin le tableau de vertex
		target.draw(quads, states);
	}
}
