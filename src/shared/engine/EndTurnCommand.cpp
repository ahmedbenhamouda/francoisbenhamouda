#include "EndTurnCommand.h"
#include <iostream>

namespace engine {
	EndTurnCommand::EndTurnCommand () {
		cannot_move_list = std::vector<state::Position>();
		cannot_attack_list = std::vector<state::Position>();
	}
	void EndTurnCommand::execute(state::Jeu* jeu, Engine* engine) {
		int nb_joueurs = jeu->joueurs.size();
		// deselect unit
		jeu->selectedUnit = nullptr;
		jeu->selectedBatiment = nullptr;

		jeu->tour++;
		
		for (state::Unite* unite : jeu->etatJeu->getUniteList()) {
			//save can_move for all units
			if (!unite->can_move) cannot_move_list.push_back(unite->position);
			if (!unite->can_attack) cannot_attack_list.push_back(unite->position);
			
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
	
		// Rétablir les droits de mouvement pour toutes les unités
		for (state::Position pos : cannot_move_list) {
			state::Unite* unit = jeu->etatJeu->getUnite(pos);
			if (unit) unit->can_move = false;
		}
		
		// Rétablir les droits d'attaque pour toutes les unités
		for (state::Position pos : cannot_attack_list) {
			state::Unite* unit = jeu->etatJeu->getUnite(pos);
			if (unit) unit->can_attack = false;
		}
		/*std::vector<state::Unite*> unite_list = jeu->etatJeu->getUniteList();
		for (size_t i=0; i<unite_list.size(); i++) {
			unite_list[i]->can_move = false;
			unite_list[i]->can_move = false;
		}*/
		
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
	Json::Value EndTurnCommand::toJson() {
	}
}
