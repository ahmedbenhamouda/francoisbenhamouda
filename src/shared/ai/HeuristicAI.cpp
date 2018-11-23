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
	std::vector<state::Position> HeuristicAI::enemyCote(state::Position pos) {
		int px = pos.getX();
		int py = pos.getY();
		std::vector<state::Position> liste;
		for (int i=0;i<2;i++) {
			for (int j=0;j<2;j++) {
				state::Unite* ennemi = jeu->etatJeu->getUnite(state::Position(px+1-2*j,py+1-2*i));
				// check if an ennemy is around
				if (ennemi and ennemi->getColor() != jeu->selectedUnit->getColor()) {
					liste.push_back(state::Position(px+1-2*j,py+1-2*i));
				}
			}
		}
		return liste;
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
		// reset flags list
		liste_flags_ennemie = std::vector<state::Flag*>();

		for (state::Flag* flag : jeu->etatJeu->getFlagList()){
			if (color != flag->color and not(flag->is_owned)){
				liste_flags_ennemie.push_back(flag);					
			}
		}
	}
	void HeuristicAI::fillCommandList() {
		// reset commands list
		for (engine::Command* cmd : liste_commands) {
			delete cmd;
		}
		liste_commands = std::vector<engine::Command*>();

		// TODO : check segmentation fault by here 
		if (jeu->selectedUnit) {
			// Check all possible movements
			std::vector<state::Position> moves = jeu->selectedUnit->getLegalMove();
			for (state::Position mv : moves) {
				if (not(jeu->etatJeu->getUnite(mv))) {
					liste_commands.push_back(new engine::MoveUnitCommand(mv));
				}
			}
			// Check if any attack is possible
			std::vector<state::Position> enemyNearby = enemyCote(jeu->selectedUnit->position);
			for (state::Position enemyPos : enemyNearby) {
				liste_commands.push_back(new engine::AttackUnitCommand(enemyPos));
			}
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
			switch (liste_commands[i]->id) {
				case 0 : //creerUnite
					liste_poids[i] = 6;
				case 2 : //selectUnite
					liste_poids[i] = 2;
				case 4 : //attackUnite
					liste_poids[i] = 7;
				case 8 : //endTurn
					liste_poids[i] = 1;
			}
		}
	}
	void HeuristicAI::poidDistance() {
		state::Position pos(0,0);
		
		if (jeu->selectedUnit->has_flag){
			for (size_t k=0; k<liste_batiments.size();k++){
				if  (liste_batiments[k]->getId_b() == 0){
					pos = liste_batiments[k]->position;
				}
			}	
		}else{	
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
		}
		for (size_t i =0; i<liste_poids.size(); i++) {
			if (liste_commands[i]->id == 3) {	
				state::Position poscom = liste_commands[i]->getPos();	
				if (enemyCote(poscom).size()>0 and (jeu->selectedUnit->position - pos)>(pos - poscom)){
					liste_poids[i] = 5;
				}
				else if ((jeu->selectedUnit->position - pos) > (pos - poscom)){	
					liste_poids[i] = 4;
				}
				else {
					liste_poids[i] = 3;
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
			std::cout<<"Nombre de commandes : "<<liste_commands.size()<<std::endl;
			std::cout<<"Pour chaque commande :"<<std::endl;
			
			

			// select only the maximum weight commands
			std::vector<int> max_commands_index;
			for (size_t i=0; i<liste_poids.size(); i++) {
				std::cout<<" - poids : "<<liste_poids[i]<<std::endl;
				if (liste_poids[i] == max_val) {
					max_commands_index.push_back(i);
				}
			}

			std::cout<<"max : "<<max_val<<std::endl;

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
