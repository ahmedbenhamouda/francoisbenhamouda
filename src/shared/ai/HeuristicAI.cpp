#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "HeuristicAI.h"
#include "engine/CreateUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/MoveUnitCommand.h"
#include "engine/AttackUnitCommand.h"
#include "engine/EndTurnCommand.h"

namespace ai {
	HeuristicAI::HeuristicAI () {
		randeng = std::mt19937(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	HeuristicAI::HeuristicAI (int color, engine::Engine* engine, state::Jeu* jeu) {
		HeuristicAI();
		this->color = color;
		this->engine = engine;
		this->jeu = jeu;
	}
	void HeuristicAI::fillStateList(){
		// reset unite list
		liste_unites = std::vector<state::Unite*>();

		for (state::Unite* unit : jeu->etatJeu->getUniteList()){
			if (color == unit->getColor()){
				liste_unites.push_back(unit);		
			}
		}
		// reset batiment list
		liste_batiments = std::vector<state::Batiment*>();

		for (state::Batiment* bat:jeu->etatJeu->getBatimentList()){
			if (color == bat->getColor()){
				liste_batiments.push_back(bat);					
			}
		}
	}
	void HeuristicAI::fillCommandList() {
		// reset commands list
		for (engine::Command* cmd : liste_commands) {
			delete cmd;
		}
		liste_commands = std::vector<engine::Command*>();

		if (jeu->selectedUnit) {
			// Check all possible movements
			std::vector<state::Position> moves = jeu->selectedUnit->getLegalMove();
			for (state::Position mv : moves) {
				if (not(jeu->etatJeu->getUnite(mv))) {
					liste_commands.push_back(new engine::MoveUnitCommand(mv));
				}
			}
			// Check if any attack is possible
			std::vector<state::Position> enemyNearby = enemyCote();
			for (state::Position enemyPos : enemyNearby) {
				liste_commands.push_back(new engine::AttackUnitCommand(enemyPos));
			}
			/*int px = jeu->selectedUnit->position.getX();
			int py = jeu->selectedUnit->position.getY();
			for (int i=0;i<2;i++) {
				for (int j=0;j<2;j++) {
					state::Unite* ennemi = jeu->etatJeu->getUnite(state::Position(px+1-2*j,py+1-2*i));
					// check if an ennemy is around
					if (ennemi and ennemi->getColor() != jeu->selectedUnit->getColor()) {
						liste_commands.push_back(new engine::AttackUnitCommand(state::Position(px+1-2*j,py+1-2*i)));
					}
				}
			}*/
		} else {
			// Check for createUnit
			int nb_joueurs = jeu->joueurs.size();
			state::Joueur* currentPlayer = jeu->joueurs[jeu->tour%nb_joueurs];
			// Check if player has enough money
			if (currentPlayer->monnaie.getArgent()>=1000) {
				for (state::Batiment* bat : liste_batiments) {
					// batiment is usine and no unit stands on it
					if (bat->getId_b() == 1 and not(jeu->etatJeu->getUnite(bat->position))) {
						liste_commands.push_back(new engine::CreateUnitCommand(bat->position, 0));
					}
				}
			}

			// Check for selectUnit
			for (state::Unite* unite : liste_unites) {
				// Check if unit can move or immediately attack
				std::vector<state::Position> enemyNearby = enemyCote();
				if (unite->can_move or (unite->can_attack and enemyNearby.size()>0)) {
					liste_commands.push_back(new engine::SelectUnitCommand(unite->position));
				}
			}
		}
		liste_commands.push_back(new engine::EndTurnCommand());
	}
	void HeuristicAI::poidCommande() {
		// reset weight list
		liste_poids = std::vector<int>(liste_commands.size(),0);

		// Get all weights for non-move commands
		for (size_t i =0; i<liste_poids.size(); i++) {
			switch (liste_commands[i]->id) {
				case 0 : //creerUnite
					liste_poids[i] = 4;
					break;
				case 2 : //selectUnite
					liste_poids[i] = 2;
					break;
				case 4 : //attackUnite
					liste_poids[i] = 5;
					break;
				case 8 : //endTurn
					liste_poids[i] = 1;
					break;
				default:
					break;
			}
		}
	}
	void HeuristicAI::run () {
		int nb_joueurs = jeu->joueurs.size();
		if (jeu->joueurs[jeu->tour%nb_joueurs]->color == color) {
			//It's time to play !
			fillStateList ();
			fillCommandList ();
			poidCommande();
			poidDistance();

			// evaluate maximum weight command
			int max_val = *std::max_element(liste_poids.begin(), liste_poids.end());

			// select only the maximum weight commands
			std::vector<int> max_commands_index;
			for (size_t i=0; i<liste_poids.size(); i++) {
				if (liste_poids[i] == max_val) {
					max_commands_index.push_back(i);
				}
			}

			// random number generation
			std::uniform_int_distribution<int> index(0,max_commands_index.size()-1);

			// add command
			int id = index(randeng);
			engine->addCommand(liste_commands[max_commands_index[id]]);
			liste_commands.erase(liste_commands.begin()+max_commands_index[id]);
		}
	}
}
