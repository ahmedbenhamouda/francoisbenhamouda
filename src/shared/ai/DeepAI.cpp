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
		liste_position_cmd = std::vector<state::Position>();
		liste_type_score = std::vector<std::vector<int>>(); // [id_commande, score]
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
	
	void DeepAI::scoreDeplacement(engine::Command* command) {
		state::Position objectif;
		int nb_joueurs = jeu->joueurs.size();
		
		if (jeu->selectedUnit->has_flag) {
			// Le QG est l'objectif si l'unite a un drapeau
			for (size_t k=0; k<liste_batiments.size();k++){
				if  (liste_batiments[k]->getId_b() == 0){
					objectif = liste_batiments[k]->position;
				}
			}
		} else {
			// Le drapeau ennemi le plus proche est l'objectif
			int shortest_distance = 10000;
			for (state::Flag* flag : liste_flags_ennemie){
				if  (not(flag->is_owned) and flag->position - jeu->selectedUnit->position < shortest_distance) {
					shortest_distance = flag->position - jeu->selectedUnit->position;
					objectif = flag->position;
				}
			}
			// L'unité la plus proche qui possède un drapeau est l'objectif
			for (state::Unite* unit : jeu->etatJeu->getUniteList()){
				if  (unit->has_flag and (unit->position - jeu->selectedUnit->position > 1) and (unit->position - jeu->selectedUnit->position < shortest_distance)) {
					shortest_distance = unit->position - jeu->selectedUnit->position;
					objectif = unit->position;
				}
			}
		}
		
		// Maintenant, on calcule la distance entre l'objectif et la commande
		state::Position new_pos = command->getPos();
		int delta_pos = (jeu->selectedUnit->position - objectif) - (new_pos - objectif);
		jeu->joueurs[jeu->tour%nb_joueurs]->score += jeu->selectedUnit->getmvt() + delta_pos;
		// Score de l'attaque si possible
		std::vector<state::Position> enemyNearby = enemyCote(jeu->selectedUnit->position);
		int ET = 0; //enemies qu'on peut tuer
		if (jeu->selectedUnit->can_attack and enemyNearby.size() > 0){
			jeu->joueurs[jeu->tour%nb_joueurs]->score += 2;
			for (size_t k=0;k<enemyNearby.size(); k++){
				if (jeu->selectedUnit->getpuissance() >= jeu->etatJeu->getUnite(enemyNearby[k])->getvie()){
					jeu->joueurs[jeu->tour%nb_joueurs]->score += 8;
					ET += 1;
				}
				if (ET>1){
					jeu->joueurs[jeu->tour%nb_joueurs]->score -= 8*(ET-1);
				}	
			}
		}
	}
	//Score de l'attaque
	void DeepAI::scoreAttack(engine::Command* command) {
		int nb_joueurs = jeu->joueurs.size();
		jeu->joueurs[jeu->tour%nb_joueurs]->score += 2;
		if (not(jeu->etatJeu->getUnite(command->getPos()))){
			jeu->joueurs[jeu->tour%nb_joueurs]->score += 4;
		}
	}
	void DeepAI::runMinMax() {
		bool skip = false;			
		int nb_joueurs = jeu->joueurs.size();
		jeu->simulation = jeu->tour%nb_joueurs;
		
		if (liste_position_cmd.size() == 0) { // Use the minmax function for the first time
			engine->Clear();
			liste_position_cmd = std::vector<state::Position>(liste_commands.size(), state::Position(0,0));
			liste_type_score = std::vector<std::vector<int>>(liste_commands.size(), {-1, -1000});
			std::cout<<"Nombre de commandes : "<<liste_type_score.size()<<std::endl;
		}
		
		//std::cout<<" -- Etapes du minmax :"<<std::endl;
		if (liste_commands[command_iter]->getId() == 3) { // Deplacement
			scoreDeplacement(liste_commands[command_iter]);
			// Si on atteint un score inferieur au score max, on abandonne le mouvement
			if (jeu->joueurs[jeu->tour%nb_joueurs]->score < max_score) {
				skip = true;
			}
		}
		
		//std::cout<<" -- Calcul du deplacement fait"<<std::endl;
		
		if (liste_commands[command_iter]->getId() != 8 and !skip) {
			engine->addCommand(liste_commands[command_iter]);
			liste_commands.erase(liste_commands.begin()+command_iter);
			engine->update();
		}
		
		//std::cout<<" -- Commande effectuee"<<std::endl;
		
		if (liste_commands[command_iter]->getId() == 4) { // Attaque
			scoreAttack(liste_commands[command_iter]);
		}
		
		//std::cout<<" -- Calcul de l'attaque fait"<<std::endl;

		command_iter++;
		
		if (!skip) {
			// End turn
			engine->addCommand(new engine::EndTurnCommand());
		}
		
		//std::cout<<" -- Fin du test"<<std::endl;
		
	}
	
	void DeepAI::run () {
		int nb_joueurs = jeu->joueurs.size();
		if (jeu->joueurs[jeu->tour%nb_joueurs]->color == color) { //It's time to play !
		
			fillStateList ();
			fillCommandList ();
			
			if (jeu->simulation < 0) { // No one is simulating right now			
				if (jeu->selectedUnit) {
					if (liste_position_cmd.size()>0 and (size_t)command_iter >= liste_position_cmd.size()) { // Last level of the minmax tree
					
						engine->Clear();
						selectFinalCommand();
						std::cout<<"End of simulation."<<std::endl;
						
					} else {
						// Use minmax algorithm for move
						std::cout<<" * Test numero "<<command_iter<<std::endl;
						runMinMax();
					}
				} else {
					runHeuristic();
				}
				
			} else if (jeu->joueurs[jeu->simulation]->color == color) { // You are currently simulating
					
					// Rollback
					ListeScore();
					
			} else { // Someone else is simulating
			
				runHeuristic();
			}
		}
	}
	
	void DeepAI::runHeuristic() {
		cloneAI->run();
	}
	
	//lister les score de chaque mouvement
	void DeepAI::ListeScore(){
		//std::cout<<" -- Etapes du rollback :"<<std::endl;
		int nb_joueurs = jeu->joueurs.size();
		if (engine->commands.size()>0) { // Vérifier qu'une commande n'a pas été passée car pas intéressante
			liste_position_cmd[command_iter-1] = engine->commands[0]->getPos();
			liste_type_score[command_iter-1] = {engine->commands[0]->getId(), jeu->joueurs[jeu->tour%nb_joueurs]->score};
		}/* else {
			liste_position_cmd[command_iter-1] = state::Position(0,0);
			liste_type_score[command_iter-1] = {-1, -1000};
		}*/
		//std::cout<<" -- Ajout du score de la commande testee : fait"<<std::endl;
		
		// Rechercher le score max
		if (jeu->joueurs[jeu->tour%nb_joueurs]->score > max_score) {
			max_score = jeu->joueurs[jeu->tour%nb_joueurs]->score;
		}
		//std::cout<<" -- Recherche du score max : fait"<<std::endl;
		while(engine->commands.size() > 0) {
			//std::cout<<" -- Nombre de commandes restantes : "<<engine->commands.size()<<std::endl;
			//std::cout<<" --- Commande annulee  : "<<engine->commands[engine->commands.size()-1]<<std::endl;
			//std::cout<<" --- ID de la commande annulee  : "<<engine->commands[engine->commands.size()-1]->getId()<<std::endl;
			//state::Position pos = engine->commands[engine->commands.size()-1]->getPos();
			//std::cout<<" --- Position  : x="<<pos.getX()<<", y="<<pos.getY()<<std::endl;
			engine->RollBack();
		}
		//std::cout<<" -- Rollback des commandes suivantes : fait"<<std::endl;
		//std::cout<<"Checkpoint 2"<<std::endl;
		jeu->joueurs[jeu->tour%nb_joueurs]->score = 0;
		jeu->simulation = -2; // etat intermediaire entre la fin d'exploration de deux etats
		//std::cout<<" -- Fin du rollback"<<std::endl;
	}
	
	//choisir le meilleur score possible
	void DeepAI::selectFinalCommand(){
		jeu->simulation = -1;
		std::cout<<"select final command"<<std::endl;
		
		std::vector<int> list_aleatoire;
		
		//std::cout<<"Nombre de scores : "<<liste_type_score.size()<<std::endl;
		for(size_t i=0; i<liste_type_score.size(); i++){
			//std::cout<<"Liste type score "<<i<<" : "<<liste_type_score[i][1]<<std::endl;
			if (liste_type_score[i][1] >= max_score){
				list_aleatoire.push_back(i);
			}
		}
		
		// Selection aleatoire de la meilleure commande		
		std::uniform_int_distribution<int> index(0,list_aleatoire.size()-1);
		int id = list_aleatoire[index(randeng)];
		
		if (liste_type_score[id][0] == 3) { // deplacement
			engine->addCommand(new engine::MoveUnitCommand(liste_position_cmd[id]));
		} else if (liste_type_score[id][0] == 4) { // attaque
			std::cout<<"Time to attack."<<std::endl;
			engine->addCommand(new engine::AttackUnitCommand(liste_position_cmd[id]));
		}
		
		// Fin de la simulation
		command_iter = 0;
		//jeu->simulation = -1;
		max_score = -1000;
		liste_position_cmd = std::vector<state::Position>();
		liste_type_score = std::vector<std::vector<int>>();
	}
	DeepAI::~DeepAI() {
	}
}
