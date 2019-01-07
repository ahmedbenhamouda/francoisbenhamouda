#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "DeepAI.h"
#include "HeuristicAI.h"
#include "engine/CreateUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/SelectBatimentCommand.h"
#include "engine/SelectUnitTypeCommand.h"
#include "engine/MoveUnitCommand.h"
#include "engine/AttackUnitCommand.h"
#include "engine/EndTurnCommand.h"

namespace ai {
	DeepAI::DeepAI () {
		randeng = std::mt19937(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	DeepAI::DeepAI (int color, engine::Engine* engine, state::Jeu* jeu) {
		DeepAI();
		this->color = color;
		this->engine = engine;
		this->jeu = jeu;
		cloneAI = new HeuristicAI(color, engine, jeu);
	}
	
	std::vector<state::Position> DeepAI::enemyCote(state::Position pos) {
		int px = pos.getX();
		int py = pos.getY();
		std::vector<state::Position> check_position {state::Position(px+1,py),state::Position(px-1,py),state::Position(px,py+1),state::Position(px,py-1)};
		std::vector<state::Position> liste;
		for (state::Position pos_check : check_position) {
			// Check if selected position is not out of bounds
			int check_x = pos_check.getX();
			int check_y = pos_check.getY();
			if ((check_x<20 && check_x>=0) && (check_y<20 && check_y>=0)){
				state::Unite* unit = jeu->etatJeu->getUnite(pos);
				state::Unite* ennemi = jeu->etatJeu->getUnite(pos_check);
				// check if an ennemy is around
				if (unit and ennemi and ennemi->getColor() != unit->getColor()) {
					liste.push_back(pos_check);
				}
			}
		}
		return liste;
	}
	
	void DeepAI::fillStateList(){
		// reset unite list
		liste_unites = std::vector<state::Unite*>();
		liste_ennemies = std::vector<state::Unite*>();

		for (state::Unite* unit : jeu->etatJeu->getUniteList()){
			if (color == unit->getColor()){
				liste_unites.push_back(unit);		
			}else{
				liste_ennemies.push_back(unit);
			}
		}
		// reset batiment list
		liste_batiments = std::vector<state::Batiment*>();

		for (state::Batiment* bat:jeu->etatJeu->getBatimentList()){
			if (color == bat->getColor()){
				liste_batiments.push_back(bat);					
			}
		}
		// reset flags list
		liste_flags_ennemie = std::vector<state::Flag*>();

		for (state::Flag* flag : jeu->etatJeu->getFlagList()){
			if (color != flag->color and not(flag->is_owned)){
				liste_flags_ennemie.push_back(flag);					
			} else if (color == flag->color){
				flag_allies = flag;
			}
		}
	}
	void DeepAI::fillCommandList() {
		// reset commands list
		for (engine::Command* cmd : liste_commands) {
			delete cmd;
		}
		liste_commands = std::vector<engine::Command*>();

		int nb_joueurs = jeu->joueurs.size();
		state::Joueur* currentPlayer = jeu->joueurs[jeu->tour%nb_joueurs];

		if (jeu->selectedBatiment) {
			// Select all possible units to create
			if (currentPlayer->monnaie.getArgent()>=10000 and jeu->unit_type < 4) {
				liste_commands.push_back(new engine::SelectUnitTypeCommand(4));
			} 
			if (currentPlayer->monnaie.getArgent()>=7000 and jeu->unit_type < 3) {
				liste_commands.push_back(new engine::SelectUnitTypeCommand(3));
			}
			if (currentPlayer->monnaie.getArgent()>=4500 and jeu->unit_type < 2) {
				liste_commands.push_back(new engine::SelectUnitTypeCommand(2));
			}
			if (currentPlayer->monnaie.getArgent()>=3500 and jeu->unit_type < 1) {
				liste_commands.push_back(new engine::SelectUnitTypeCommand(1));
			}
		
			// add unit
			liste_commands.push_back(new engine::CreateUnitCommand());
		} else if (jeu->selectedUnit) {
			// Check all possible movements
			std::vector<state::Position> moves = jeu->selectedUnit->getLegalMove(jeu->etatJeu);
			for (state::Position mv : moves) {
				liste_commands.push_back(new engine::MoveUnitCommand(mv));
			}
			// Check if any attack is possible
			if (jeu->selectedUnit->can_attack) {
				std::vector<state::Position> enemyNearby = enemyCote(jeu->selectedUnit->position);
				for (state::Position enemyPos : enemyNearby) {
					liste_commands.push_back(new engine::AttackUnitCommand(enemyPos));
				}
			}
		} else {
			// Check for createUnit
			// Check if player has enough money
			if (currentPlayer->monnaie.getArgent()>=1000) {
				for (state::Batiment* bat : liste_batiments) {
					// batiment is usine and no unit stands on it
					if (bat->getId_b() == 1 and not(jeu->etatJeu->getUnite(bat->position))) {
						liste_commands.push_back(new engine::SelectBatimentCommand(bat->position));
					}
				}
			}
			// Check for selectUnit
			for (state::Unite* unite : liste_unites) {
				// Check if unit can move or immediately attack
				std::vector<state::Position> enemyNearby = enemyCote(unite->position);
				if (unite->can_move or (unite->can_attack and enemyNearby.size()>0)) {
					liste_commands.push_back(new engine::SelectUnitCommand(unite->position));
				}
			}
			liste_commands.push_back(new engine::EndTurnCommand());
		}
	}
	
	void DeepAI::runMinMax() {
		// simulation mode
		state::Position targetPos;
		int nb_joueurs = jeu->joueurs.size();
		jeu->simulation = jeu->tour%nb_joueurs;
		// Try out each non-EndTurn command
		if (liste_commands[command_iter]->getId() != 8) {
			if (liste_commands[command_iter]->getId() == 3) {
				targetPos = liste_commands[command_iter]->getPos();
			}
			// execute commande
			engine->addCommand(liste_commands[command_iter]);
			engine->update();
			
			// Check if any attack is possible
			if (enemyCote(targetPos).size()) {
				// Add a point to the player to encourage attack
				int nb_joueurs = jeu->joueurs.size();
				jeu->joueurs[jeu->tour%nb_joueurs]->score += 1; // arbitrary value
			}
			
			// End turn
			engine->addCommand(new engine::EndTurnCommand());
			engine->update();
		}
	}
	
	void DeepAI::run () {
		int nb_joueurs = jeu->joueurs.size();
		if (jeu->joueurs[jeu->tour%nb_joueurs]->color == color) {
			//It's time to play !
			fillStateList ();
			fillCommandList ();
			
			if (jeu->simulation == -1) {
				// No one is simulating right now
				if (jeu->selectedUnit) {
					// Use minmax algorithm for move
					runMinMax();		
				} else {
					runHeuristic();
				}
			} else if (jeu->joueurs[jeu->simulation]->color == color) {
				// You are currently simulating
				selectFinalCommand();
				
			} else {
				// Someone else is simulating
				runHeuristic();
			}
		}
	}
	
	void DeepAI::runHeuristic() {
		cloneAI->run();
	}
	//lister les score de chaque mouvement
	void DeepAI::ListeScore(){
		int nb_joueurs = jeu->joueurs.size();
		score = jeu->joueurs[jeu->tour%nb_joueurs]->score;
		liste_score.push_back(score);
		while(engine->commands.size()) {
			engine->RollBack();
		}
		jeu->joueurs[jeu->tour%nb_joueurs]->score = 0;	
	}
	//choisir le meilleur score possible
	void DeepAI::selectFinalCommand(){
		int plus_haut_score = 0;
		std::vectror<int> list_aleatoire;
		for(k=0; k<liste_score.size();k++){
			if (liste_score[k]>= plus_haut_score){
				plus_haut_score = liste_score[k];
			} 
		}
		for(i=0; i<liste_score.size();i++){
			if (liste_score[i] == plus_haut_score){
				list_aleatoire.push_back(liste_score[i]);
			}
		}
		std::uniform_int_distribution<int> index(0,list_aleatoire.size()-1);
	}
	DeepAI::~DeepAI() {
	}
}
