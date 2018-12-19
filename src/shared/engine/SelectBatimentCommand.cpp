#include "SelectBatimentCommand.h"
#include <iostream>

namespace engine {
	SelectBatimentCommand::SelectBatimentCommand() {
	}
	SelectBatimentCommand::SelectBatimentCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
	void SelectBatimentCommand::execute(state::Jeu* jeu) {
		std::cout<<"Select batiment"<<std::endl;
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
	void SelectBatimentCommand::Undo(state::Jeu* jeu){
		std::cout<<"Cancel select batiment"<<std::endl;
		jeu->selectedBatiment = nullptr;
	}
}
