#include "Layers.h"
#include "engine/AttackUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/MoveUnitCommand.h"
#include <memory>
#include <iostream>

namespace render {
	Layers::Layers() {
	}
	Layers::Layers (state::Jeu* jeu, engine::Engine* engine, Tileset<state::Unite>* uniteTileset, Tileset<state::Batiment>* batimentTileset, Tileset<state::TerrainTile>* terrainTileset, Tileset<state::MiscTile>* miscTileset) {
		this->jeu = jeu;
		this->engine = engine;
		this->uniteTileset = uniteTileset;
		this->batimentTileset = batimentTileset;
		this->terrainTileset = terrainTileset;
		this->miscTileset = miscTileset;
		uniteSurface.loadTexture(uniteTileset->getImageFile());
		batimentSurface.loadTexture(batimentTileset->getImageFile());
		terrainSurface.loadTexture(terrainTileset->getImageFile());
		miscSurface.loadTexture(miscTileset->getImageFile());
	}
	Layers::~Layers() {
	}
	void Layers::setUniteSurface () {		
		uniteSurface.initQuads(256);
		for (state::Unite* unite : jeu->etatJeu->getUniteList()) {
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
		for (state::Batiment* batiment : jeu->etatJeu->getBatimentList()) {
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
				std::unique_ptr<state::TerrainTile> tt(new state::TerrainTile(jeu->etatJeu->getGround(state::Position(j,i))));
				terrainSurface.setSpriteLocation(j,i,8,32,false);
    				terrainSurface.setSpriteTexture(j,i,8,terrainTileset->getTile(tt.get()));
			}
		}
	}
	void Layers::setMiscSurface () {
		miscSurface.initQuads(256);
		for (state::Position pos : jeu->etatJeu->getUniteMoves()) {
			int posx = pos.getX();
			int posy = pos.getY();
			std::unique_ptr<state::MiscTile> mt(new state::MiscTile(0,pos));
			miscSurface.setSpriteLocation(posx,posy,8,32,false);
    			miscSurface.setSpriteTexture(posx,posy,8,miscTileset->getTile(mt.get()));
		}
	}
	void Layers::displayLayers(sf::RenderWindow* window) {
		window->clear();
		window->draw(terrainSurface);
		window->draw(batimentSurface);
		window->draw(uniteSurface);
		window->draw(miscSurface);
		window->display();

	}
	void Layers::sendCommand(state::Position position) {
		if (jeu->etatJeu->getUnite(position)) {
			if (jeu->selectedUnit) {
				std::unique_ptr<engine::AttackUnitCommand> cmd(new engine::AttackUnitCommand(position));
				engine->addCommand(cmd.get());
				engine->update();
			} else {
				std::unique_ptr<engine::SelectUnitCommand> cmd(new engine::SelectUnitCommand(position));
				engine->addCommand(cmd.get());
				engine->update();
			}
		} else {
			if (jeu->selectedUnit) {
				std::unique_ptr<engine::MoveUnitCommand> cmd(new engine::MoveUnitCommand(position));
				engine->addCommand(cmd.get());
				engine->update();
			}
		}
			
	}
}
