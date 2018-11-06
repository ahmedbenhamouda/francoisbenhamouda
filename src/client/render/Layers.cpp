#include "Layers.h"
#include <memory>
#include <iostream>

namespace render {
	Layers::Layers() {
	}
	Layers::~Layers() {
	}
	void Layers::setUniteSurface (state::Terrain* terrain) {
		//Create a Tileset
		render::Tileset<state::Unite> uniteTileset("res/units.png");
		//Initialise the Unite Surface
		uniteSurface.loadTexture(uniteTileset.getImageFile());
		uniteSurface.initQuads(256);
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				state::Position pos(j,i);
				if (terrain->getUnite(pos)) {
					uniteSurface.setSpriteLocation(j,i,8,16);
    					uniteSurface.setSpriteTexture(j,i,8,uniteTileset.getTile(terrain->getUnite(pos)));
				}
			}
		}
	}
	void Layers::setBatimentSurface (state::Terrain* terrain) {
		//Create a Tileset
		render::Tileset<state::Batiment> batimentTileset("res/batiments.png");
		//Initialise the Batiment Surface
		batimentSurface.loadTexture(batimentTileset.getImageFile());
		batimentSurface.initQuads(256);
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				state::Position pos(j,i);
				if (terrain->getBatiment(pos)) {
					batimentSurface.setSpriteLocation(j,i,8,16);
    					batimentSurface.setSpriteTexture(j,i,8,batimentTileset.getTile(terrain->getBatiment(pos)));
				}
			}
		}
	}
	void Layers::setTerrainSurface (state::Terrain* terrain) {
		//Create a Tileset
		render::Tileset<state::TerrainTile> terrainTileset("res/terrain.png");
		//Initialise the Batiment Surface
		terrainSurface.loadTexture(terrainTileset.getImageFile());
		terrainSurface.initQuads(256);		
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				//state::Position pos(j,i);
				std::unique_ptr<state::TerrainTile> tt(new state::TerrainTile(terrain->getGround(state::Position(j,i))));
				terrainSurface.setSpriteLocation(j,i,8,16);
    				terrainSurface.setSpriteTexture(j,i,8,terrainTileset.getTile(tt.get()));
			}
		}
	}
	void Layers::displayLayers() {
		sf::RenderWindow window(sf::VideoMode(64,64), "Advance Wars");
		//window.setVerticalSyncEnabled(false);
		while(window.isOpen()) {
			sf::Event event;
			while(window.pollEvent(event)) {
				if(event.type == sf::Event::Closed) {
					window.close();
				}
				window.clear();
				window.draw(terrainSurface);
				window.draw(batimentSurface);
				window.draw(uniteSurface);
				window.display();
			}
		}
	}
}
