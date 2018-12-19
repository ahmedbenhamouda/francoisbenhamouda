#include "EndTurnCommand.h"
#include <iostream>

namespace engine {
	EndTurnCommand::EndTurnCommand () {
	}
	void EndTurnCommand::execute (state::Jeu* jeu) {
		// initialize all units' possible moves
		this->possible_moves = std::vector<std::vector<bool>>();

		std::cout<<"End turn"<<std::endl;
		int nb_joueurs = jeu->joueurs.size();
		// deselect unit
		jeu->selectedUnit = nullptr;
		jeu->selectedBatiment = nullptr;

		jeu->tour++;
		//std::cout<<std::endl<<"Player "<<1+jeu->tour%nb_joueurs<<"'s turn :"<<std::endl;
		
		for (state::Unite* unite : jeu->etatJeu->getUniteList()) {
			// store possible moves before ending the turn
			possible_moves.push_back({unite->can_move, unite->can_attack});
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
	void EndTurnCommand::Undo (state::Jeu* jeu) {
		std::cout<<"Cancel end turn"<<std::endl;
		// Restore all units' possible moves before ending
		std::vector<state::Unite*> unite_list = jeu->etatJeu->getUniteList();
		for (size_t i=0; i<unite_list.size(); i++) {
			unite_list[i]->can_move = possible_moves[i][0];
			unite_list[i]->can_move = possible_moves[i][1];
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
