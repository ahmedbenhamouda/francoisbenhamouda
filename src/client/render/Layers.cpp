#include "Layers.h"
#include "engine/AttackUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/MoveUnitCommand.h"
#include "engine/CreateUnitCommand.h"
#include "engine/EndTurnCommand.h"
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
		// affichage des explosions
		for (state::Position pos : jeu->etatJeu->explosions) {
			int posx = pos.getX();
			int posy = pos.getY();
			std::unique_ptr<state::MiscTile> explosion(new state::MiscTile(1,pos));
			miscSurface.setSpriteLocation(posx,posy,8,32,false);
	    		miscSurface.setSpriteTexture(posx,posy,8,miscTileset->getTile(explosion.get()));
		}
		// affichage des cases de deplacement
		for (state::Position pos : jeu->etatJeu->uniteMoves) {
			int posx = pos.getX();
			int posy = pos.getY();
			std::unique_ptr<state::MiscTile> carre(new state::MiscTile(0,pos));
			miscSurface.setSpriteLocation(posx,posy,8,32,false);
    			miscSurface.setSpriteTexture(posx,posy,8,miscTileset->getTile(carre.get()));
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
	void Layers::sendUnitCommand(state::Position position) {
		//std::cout<<"sendCommand"<<std::endl;
		if (jeu->etatJeu->getUnite(position)) {
			if (jeu->selectedUnit) {
				engine::Command* cmd = new engine::AttackUnitCommand(position);
				engine->addCommand(cmd);
			} else {
				engine::Command* cmd = new engine::SelectUnitCommand(position);
				engine->addCommand(cmd);
			}
		} else if (jeu->selectedUnit) {
			engine::Command* cmd = new engine::MoveUnitCommand(position);
			engine->addCommand(cmd);
		} else {
			state::Batiment* bat = jeu->etatJeu->getBatiment(position);		
			if (bat and bat->getId_b() == 1) {
				engine::Command* cmd = new engine::CreateUnitCommand(position,0);
				engine->addCommand(cmd);
			}
		}
	}
	void Layers::sendTurnCommand() {
		//std::cout<<"sendCommand"<<std::endl;
		engine::Command* cmd = new engine::EndTurnCommand();
		engine->addCommand(cmd);
	}
}
