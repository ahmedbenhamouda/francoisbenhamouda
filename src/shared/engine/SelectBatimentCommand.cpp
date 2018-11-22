#include "SelectBatimentCommand.h"
#include <iostream>

namespace engine {
	SelectBatimentCommand::SelectBatimentCommand() {
	}
	SelectBatimentCommand::SelectBatimentCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
	void SelectBatimentCommand::execute(state::Jeu* jeu) {
		int nb_joueurs = jeu->joueurs.size();
		state::Batiment* batiment = jeu->etatJeu->getBatiment(objectPos);
		if (batiment->getColor() == jeu->joueurs[jeu->tour%nb_joueurs]->color) {
			jeu->selectedBatiment = batiment;
		} else {
			std::cout<<"This building is not yours."<<std::endl;
		}
		
	}
	SelectBatimentCommand::~SelectBatimentCommand() {
	}
	state::Position SelectBatimentCommand::getPos() {
		return objectPos;
	}
}