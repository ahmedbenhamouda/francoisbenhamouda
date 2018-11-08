#include "Layers.h"
#include <memory>
#include <iostream>

namespace render {
	Layers::Layers() {
	}
	Layers::Layers(state::Terrain* terrain, Tileset<state::Unite>* uniteTileset, Tileset<state::Batiment>* batimentTileset, Tileset<state::TerrainTile>* terrainTileset) {
		this->terrain = terrain;
		this->uniteTileset = uniteTileset;
		this->batimentTileset = batimentTileset;
		this->terrainTileset = terrainTileset;
		uniteSurface.loadTexture(uniteTileset->getImageFile());
		batimentSurface.loadTexture(batimentTileset->getImageFile());
		terrainSurface.loadTexture(terrainTileset->getImageFile());
	}
	Layers::~Layers() {
	}
	void Layers::setUniteSurface () {		
		uniteSurface.initQuads(256);
		for (state::Unite* unite : terrain->getUniteList()) {
			if (unite) {
				int posx = unite->position.getX();
				int posy = unite->position.getY();
				uniteSurface.setSpriteLocation(posx,posy,8,32,false);
    				uniteSurface.setSpriteTexture(posx,posy,8,uniteTileset->getTile(unite));
			}
		}
	}
	void Layers::setBatimentSurface () {
		batimentSurface.initQuads(256);
		for (state::Batiment* batiment : terrain->getBatimentList()) {
			if (batiment) {
				int posx = batiment->position.getX();
				int posy = batiment->position.getY();
				batimentSurface.setSpriteLocation(posx,posy,8,32,true);
    				batimentSurface.setSpriteTexture(posx,posy,8,batimentTileset->getTile(batiment));
			}
		}
	}
	void Layers::setTerrainSurface () {
		terrainSurface.initQuads(256);		
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				std::unique_ptr<state::TerrainTile> tt(new state::TerrainTile(terrain->getGround(state::Position(j,i))));
				terrainSurface.setSpriteLocation(j,i,8,32,false);
    				terrainSurface.setSpriteTexture(j,i,8,terrainTileset->getTile(tt.get()));
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
