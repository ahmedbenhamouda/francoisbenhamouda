#include "EndTurnCommand.h"
#include <iostream>

namespace engine {
	EndTurnCommand::EndTurnCommand () {
	}
	void EndTurnCommand::execute (state::Jeu* jeu) {
		std::cout<<"End turn"<<std::endl;
		int nb_joueurs = jeu->joueurs.size();
		// deselect unit
		jeu->selectedUnit = nullptr;
		jeu->etatJeu->uniteMoves = std::vector<state::Position>();

		jeu->tour++;
		std::cout<<std::endl<<"Player "<<1+jeu->tour%nb_joueurs<<"'s turn :"<<std::endl;
		
		// all units can move
		for (state::Unite* unite : jeu->etatJeu->getUniteList()) {
			unite->can_move = true;
			unite->can_attack = true;
		}

		// give money to all players
		if (jeu->tour%nb_joueurs == 0) {
			for (state::Joueur* player : jeu->joueurs) {
				player->monnaie.gainTour(1000);
			}
		}
		
	}
	EndTurnCommand::~EndTurnCommand () {
	}
	state::Position EndTurnCommand::getPos() {
		return state::Position(-1,-1);
	}
	int EndTurnCommand::getId() {
		return this->id;
	}
}
