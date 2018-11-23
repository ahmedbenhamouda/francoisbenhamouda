#include "CreateUnitCommand.h"
#include <iostream>


namespace engine {
	CreateUnitCommand::CreateUnitCommand() {
	}
	CreateUnitCommand::CreateUnitCommand(state::Position objectPos, int unit_id) {
		this->objectPos = objectPos;
		this->unit_id = unit_id;
	}
	CreateUnitCommand::~CreateUnitCommand() {
	}
	void CreateUnitCommand::execute (state::Jeu* jeu) {
		std::cout<<"Create unit"<<std::endl;
  		int nb_joueurs = jeu->joueurs.size();
		state::Batiment* usine = jeu->etatJeu->getBatiment(objectPos);
		if (usine->getColor() == jeu->joueurs[jeu->tour%nb_joueurs]->color) {
			state::Unite* unite = usine->creerU(unit_id);
			// Check if player has enough money
			int money = jeu->joueurs[jeu->tour%nb_joueurs]->monnaie.getArgent();
			int price = unite->getprix();
			if (money < price) {
				std::cout<<"You don't have enough money."<<std::endl;
				delete unite;
				return;
			}
			jeu->etatJeu->addUnite(unite);
			jeu->joueurs[jeu->tour%nb_joueurs]->monnaie.achat(price);
			std::cout<<"Money remaining : "<<money-price<<std::endl;
		} else {
			std::cout<<"This building is not yours."<<std::endl;
		}
	}
	state::Position CreateUnitCommand::getPos() {
		return this->objectPos;
	}
}
