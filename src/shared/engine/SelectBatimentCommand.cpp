#include "SelectBatimentCommand.h"
#include <iostream>

namespace engine {
	SelectBatimentCommand::SelectBatimentCommand() {
	}
	SelectBatimentCommand::SelectBatimentCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
	void SelectBatimentCommand::execute(state::Jeu* jeu, Engine* engine) {
		int nb_joueurs = jeu->joueurs.size();
		state::Batiment* batiment = jeu->etatJeu->getBatiment(objectPos);
		if (batiment == jeu->selectedBatiment) {
			jeu->selectedBatiment = nullptr;
		} else if (batiment->getColor() == jeu->joueurs[jeu->tour%nb_joueurs]->color) {
			jeu->selectedBatiment = batiment;
			jeu->selectedUnit = nullptr;
		} else {
			std::cout<<"This building is not yours."<<std::endl;
		}
		
	}
	SelectBatimentCommand::~SelectBatimentCommand() {
	}
	state::Position SelectBatimentCommand::getPos() {
		return objectPos;
	}
	int SelectBatimentCommand::getId() {
		return this->id;
	}
	void SelectBatimentCommand::Undo(state::Jeu* jeu, Engine* engine){
		jeu->selectedBatiment = nullptr;
	}
	Json::Value SelectBatimentCommand::toJson(){
		Json::Value cmd;
		cmd[" Type "]=this->getId();
		cmd[" Position_X "]=this->objectPos.getX();
		cmd[" Position_Y "]=this->objectPos.getY();
		return cmd;
	}
}
