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
		jeu->etatJeu->setUniteMoves(unite->getLegalMove());
		jeu->selectedUnit = unite;
		
	}
	SelectUnitCommand::~SelectUnitCommand() {
	}
}
