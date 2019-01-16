#include "SelectUnitCommand.h"
#include <iostream>

namespace engine {
	SelectUnitCommand::SelectUnitCommand() {
	}
	SelectUnitCommand::SelectUnitCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
	void SelectUnitCommand::execute(state::Jeu* jeu, Engine* engine) {
		int nb_joueurs = jeu->joueurs.size();
		//std::cout<<"unit selected"<<std::endl;
		state::Unite* unite = jeu->etatJeu->getUnite(objectPos);
		if (unite->getColor() == jeu->joueurs[jeu->tour%nb_joueurs]->color) {
			jeu->selectedUnit = unite;
			jeu->selectedBatiment = nullptr;
		} else {
			std::cout<<"This unit is not yours."<<std::endl;
		}
	}
	void SelectUnitCommand::Undo(state::Jeu* jeu, Engine* engine) {
		jeu->selectedUnit = nullptr;
	}
	SelectUnitCommand::~SelectUnitCommand() {
	}
	state::Position SelectUnitCommand::getPos() {
		return this->objectPos;
	}
	int SelectUnitCommand::getId() {
		return this->id;
	}
	Json::Value SelectUnitCommand::toJson(){
		Json::Value cmd;
		cmd[" Type "]=this->getId();
		cmd[" Position_X "]=this->objectPos.getX();
		cmd[" Position_Y "]=this->objectPos.getY();
		return cmd;
	}
}
