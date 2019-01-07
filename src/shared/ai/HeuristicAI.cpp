#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "HeuristicAI.h"
#include "engine/CreateUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/SelectBatimentCommand.h"
#include "engine/SelectUnitTypeCommand.h"
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
	std::vector<state::Position> HeuristicAI::enemyCote(state::Position pos) {
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
	void HeuristicAI::fillStateList(){
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
	void HeuristicAI::fillCommandList() {
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
	void HeuristicAI::poidCommande() {
		// reset weight list
		liste_poids = std::vector<int>(liste_commands.size(),0);

		// Get all weights for non-move commands
		for (size_t i =0; i<liste_poids.size(); i++) {
			if (liste_commands[i]->getId() == 0) { //creerUnite
				liste_poids[i] = 1;
			}
			if (liste_commands[i]->getId() == 2) { //selectUnite
				liste_poids[i] = 2;
			}
			if (liste_commands[i]->getId() == 4) { //attackUnite
				liste_poids[i] = 7;
			}
			if (liste_commands[i]->getId() == 5) { //selectBatiment
				// The more units you have, the less likely you will choose to create one
				liste_poids[i] = 1+3/(1+liste_unites.size());
			}
			if (liste_commands[i]->getId() == 8) { //endTurn
				liste_poids[i] = 1;
			}
			if (liste_commands[i]->getId() == 9) { //selectUnitType
				// Note : random choice between select an unit or end the turn
				// The more units you have, the less likely you will choose to end your turn
				liste_poids[i] = 1+liste_commands[i]->getPos().getX();
			}
		}
	}
	void HeuristicAI::poidDistance() {
		state::Position pos;
		// Default position : QG
		/*for (size_t k=0; k<liste_batiments.size();k++){
			if  (liste_batiments[k]->getId_b() == 0){
				pos = liste_batiments[k]->position;
			}
		}*/
		// Current unit has flag, then has to go home
		if (jeu->selectedUnit->has_flag) {
			for (size_t k=0; k<liste_batiments.size();k++){
				if  (liste_batiments[k]->getId_b() == 0){
					pos = liste_batiments[k]->position;
				}
			}
		}
		// Flag captured by ennemy
		else if (flag_allies->is_owned) {
			for (state::Unite* unite : liste_ennemies) {
				if (unite->has_flag == flag_allies) {
					pos = unite->position;
				}
			}
		} else {
			// Flag is not in QG
			state::Batiment* bat = jeu->etatJeu->getBatiment(flag_allies->position);
			if (not(bat) or bat->getId_b() != 0) {
				pos = flag_allies->position;
			} else {
				// Look for the closest enemy flag
				if (liste_flags_ennemie.size() > 0){
					int imp = (jeu->selectedUnit->position - liste_flags_ennemie[0]->position);
					pos = liste_flags_ennemie[0]->position;	
			
					if (liste_flags_ennemie.size() > 1){
						for (size_t i=1;i<liste_flags_ennemie.size();i++){
							if (imp > (jeu->selectedUnit->position - liste_flags_ennemie[i]->position)){
								imp = jeu->selectedUnit->position - liste_flags_ennemie[i]->position;
								pos = liste_flags_ennemie[i]->position;
							}
						}	
					}
				} else {
					 // Look for anyone carrying a flag (escort ally or attack enemy)
					 for (state::Unite* unite : jeu->etatJeu->getUniteList()) {
						if (unite->has_flag) {
							pos = unite->position;
						}
					}
				}
			}
		}

		// evaluate the distance between each command and the goal
		for (size_t i =0; i<liste_poids.size(); i++) {
			if (liste_commands[i]->getId() == 3) {	
				state::Position poscom = liste_commands[i]->getPos();
				// Scores how close to the target the next position is
				int delta_pos = (jeu->selectedUnit->position - pos) - (poscom - pos);
				liste_poids[i] = jeu->selectedUnit->getmvt() + delta_pos;
				if (pos == poscom) { // going to the goal
					liste_poids[i] += 2;
				} else if (enemyCote(poscom).size()>0){ // engage combat
					liste_poids[i] += 1;
				}
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
			if (jeu->selectedUnit) {
				poidDistance();
			}

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
	HeuristicAI::~HeuristicAI() {
	}
}
