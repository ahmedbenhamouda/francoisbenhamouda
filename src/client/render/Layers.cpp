#include "Layers.h"
#include <memory>
#include <iostream>

namespace render {
	Layers::Layers() {
	}
	Layers::Layers(state::Terrain* terrain) {
		this->terrain = terrain;
	}
	Layers::~Layers() {
	}
	void Layers::setUniteSurface () {
		//Create a Tileset
		render::Tileset<state::Unite> uniteTileset("res/units.png");
		//Initialise the Unite Surface
		uniteSurface.loadTexture(uniteTileset.getImageFile());
		uniteSurface.initQuads(256);
		for (state::Unite* unite : terrain->getUniteList()) {
			if (unite) {
				int posx = unite->position.getX();
				int posy = unite->position.getY();
				uniteSurface.setSpriteLocation(posx,posy,8,32,false);
    				uniteSurface.setSpriteTexture(posx,posy,8,uniteTileset.getTile(unite));
			}
		}
	}
	void Layers::setBatimentSurface () {
		//Create a Tileset
		render::Tileset<state::Batiment> batimentTileset("res/batiments.png");
		//Initialise the Batiment Surface
		batimentSurface.loadTexture(batimentTileset.getImageFile());
		batimentSurface.initQuads(256);
		for (state::Batiment* batiment : terrain->getBatimentList()) {
			if (batiment) {
				int posx = batiment->position.getX();
				int posy = batiment->position.getY();
				batimentSurface.setSpriteLocation(posx,posy,8,32,true);
    				batimentSurface.setSpriteTexture(posx,posy,8,batimentTileset.getTile(batiment));
			}
		}
	}
	void Layers::setTerrainSurface () {
		//Create a Tileset
		render::Tileset<state::TerrainTile> terrainTileset("res/terrain.png");
		//Initialise the Batiment Surface
		terrainSurface.loadTexture(terrainTileset.getImageFile());
		terrainSurface.initQuads(256);		
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				//state::Position pos(j,i);
				std::unique_ptr<state::TerrainTile> tt(new state::TerrainTile(terrain->getGround(state::Position(j,i))));
				terrainSurface.setSpriteLocation(j,i,8,32,false);
    				terrainSurface.setSpriteTexture(j,i,8,terrainTileset.getTile(tt.get()));
			}
		}
	}
	void Layers::displayLayers(sf::RenderWindow* window) {
		window->clear();
		window->draw(terrainSurface);
		window->draw(batimentSurface);
		window->draw(uniteSurface);
		window->display();

	}
}
