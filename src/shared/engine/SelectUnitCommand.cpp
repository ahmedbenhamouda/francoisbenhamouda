#include "SelectUnitCommand.h"
#include <iostream>

namespace engine {
	SelectUnitCommand::SelectUnitCommand() {
	}
	SelectUnitCommand::SelectUnitCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
	void SelectUnitCommand::execute(state::Jeu* jeu) {
		int nb_joueurs = jeu->joueurs.size();
		state::Unite* unite = jeu->etatJeu->getUnite(objectPos);
		if (unite->getColor() == jeu->joueurs[jeu->tour%nb_joueurs]->color) {
			jeu->etatJeu->uniteMoves = unite->getLegalMove();
			jeu->selectedUnit = unite;
		} else {
			std::cout<<"This unit is not yours."<<std::endl;
		}
		
	}
	SelectUnitCommand::~SelectUnitCommand() {
	}
	state::Position SelectUnitCommand::getPos() {
	}
}
