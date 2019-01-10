#include "EndTurnCommand.h"
#include <iostream>

namespace engine {
	EndTurnCommand::EndTurnCommand () {
	}
	void EndTurnCommand::execute(state::Jeu* jeu, Engine* engine) {
		int nb_joueurs = jeu->joueurs.size();
		// deselect unit
		jeu->selectedUnit = nullptr;
		jeu->selectedBatiment = nullptr;

		jeu->tour++;
		//std::cout<<std::endl<<"Player "<<1+jeu->tour%nb_joueurs<<"'s turn :"<<std::endl;
		
		for (state::Unite* unite : jeu->etatJeu->getUniteList()) {
			// all units can move and attack
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
	void EndTurnCommand::Undo(state::Jeu* jeu, Engine* engine) {
		int nb_joueurs = jeu->joueurs.size();
	
		// We assume all units couldn't move anymore before ending the turn
		std::vector<state::Unite*> unite_list = jeu->etatJeu->getUniteList();
		for (size_t i=0; i<unite_list.size(); i++) {
			unite_list[i]->can_move = false;
			unite_list[i]->can_move = false;
		}
		
		// Remove money to all players
		if (jeu->tour%nb_joueurs == 0) {
			for (state::Joueur* player : jeu->joueurs) {
				player->monnaie.gainTour(-1000);
			}
		}
		
		// Reset turn
		jeu->tour--;
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
