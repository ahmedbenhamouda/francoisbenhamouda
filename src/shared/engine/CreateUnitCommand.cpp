#include "CreateUnitCommand.h"
#include "DeleteUnitCommand.h"
#include <iostream>


namespace engine {
	CreateUnitCommand::CreateUnitCommand() {
	}
	CreateUnitCommand::~CreateUnitCommand() {
	}
	void CreateUnitCommand::execute (state::Jeu* jeu) {
		std::cout<<"Create unit"<<std::endl;
  		int nb_joueurs = jeu->joueurs.size();
		state::Batiment* usine = jeu->selectedBatiment;
		if (not(usine)) {
			std::cout<<"No building was selected."<<std::endl;
			return;
		}
		if (usine->getColor() == jeu->joueurs[jeu->tour%nb_joueurs]->color) {
			state::Unite* unite = usine->creerU(jeu->unit_type);
			// Check if player has enough money
			money = jeu->joueurs[jeu->tour%nb_joueurs]->monnaie.getArgent();
			price = unite->getprix();
			if (money < price) {
				std::cout<<"You don't have enough money."<<std::endl;
				delete unite;
				return;
			}
			jeu->etatJeu->addUnite(unite);
			jeu->joueurs[jeu->tour%nb_joueurs]->monnaie.achat(price);
			jeu->selectedBatiment = nullptr;
			jeu->unit_type = 0;
			std::cout<<"Money remaining : "<<money-price<<std::endl;
		} else {
			std::cout<<"This building is not yours."<<std::endl;
		}
	}
	void CreateUnitCommand::Undo (state::Jeu* jeu) {
	}
	state::Position CreateUnitCommand::getPos() {
		return this->objectPos;
	}
	int CreateUnitCommand::getId() {
		return this->id;
	}
	void CreateUnitCommand::Undo(state::Jeu* jeu){
		DeleteUnitCommand(objectPos).execute(jeu);
		money = money + price;
	}
}
