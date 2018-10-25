#include "Layers.h"

namespace render {
	Layers::Layers() {
	}
	Layers::~Layers() {
	}
	void Layers::setUniteSurface (std::vector<std::vector<state::Unite*>> unites) {
		//Creat the Unite Tileset
		render::TileSet<state::Unite> uniteTileSet("res/units.png");
		//Initialise the Unite Surface
		uniteSurface.loadTexture(uniteTileSet.getImageFile());
		uniteSurface.initQuads(64);
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				uniteSurface.setSpriteLocation(j,i,8,16);
    				uniteSurface.setSpriteTexture(j,i,8,uniteTileSet.getTile(unites[i][j]));
			}
		}
	}
	void Layers::setBatimentSurface (std::vector<std::vector<state::Batiment*>> batiments) {
		//Creat the Batiment Tileset
		render::TileSet<state::Batiment> batimentTileSet("res/batiments.png");
		//Initialise the Batiment Surface
		batimentSurface.loadTexture(batimentTileSet.getImageFile());
		batimentSurface.initQuads(64);
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				batimentSurface.setSpriteLocation(j,i,8,16);
    				batimentSurface.setSpriteTexture(j,i,8,batimentTileSet.getTile(batiments[i][j]));
			}
		}
	}
	void Layers::setTerrainSurface (state::TerrainTab terrainTab) {
		//Creat the terrain Tileset
		render::TileSet<state::TerrainTile> terrainTileSet("res/terrain.png");
		//Initialise the Terrain Surface
		terrainSurface.loadTexture(terrainTileSet.getImageFile());
		terrainSurface.initQuads(64);
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				std::unique_ptr<state::Position> pos(new state::Position(j,i));
				std::unique_ptr<state::TerrainTile> tt(new state::TerrainTile(terrainTab.get(*pos)));
				terrainSurface.setSpriteLocation(j,i,8,16);
    				terrainSurface.setSpriteTexture(j,i,8,terrainTileSet.getTile(tt.get()));
			}
		}
	}
	void Layers::displayLayers() {
		sf::RenderWindow window(sf::VideoMode(800,600), "window");
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
