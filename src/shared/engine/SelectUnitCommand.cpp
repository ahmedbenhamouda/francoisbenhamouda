#include "SelectUnitCommand.h"
#include <iostream>

namespace engine {
	SelectUnitCommand::SelectUnitCommand() {
	}
	SelectUnitCommand::SelectUnitCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
	void SelectUnitCommand::execute(state::Jeu* jeu) {
		//std::cout<<"unit selected"<<std::endl;
		state::Unite* unite = jeu->etatJeu->getUnite(objectPos);
		if (unite->getColor() == jeu->joueurs[jeu->tour%2]->color) {
			jeu->etatJeu->uniteMoves = unite->getLegalMove();
			jeu->selectedUnit = unite;
		} else {
			std::cout<<"This unit is not yours."<<std::endl;
		}
		
	}
	SelectUnitCommand::~SelectUnitCommand() {
	}
}
