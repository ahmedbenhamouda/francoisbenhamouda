#include <iostream>
#include <thread>
#include <chrono>
#include "RandomAI.h"
#include "engine/CreateUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/MoveUnitCommand.h"
#include "engine/AttackUnitCommand.h"
#include "engine/EndTurnCommand.h"

namespace ai {
	RandomAI::RandomAI () {
		randeng = std::mt19937(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	RandomAI::RandomAI (int color, engine::Engine* engine, state::Jeu* jeu) {
		RandomAI();
		this->color = color;
		this->engine = engine;
		this->jeu = jeu;
	}
	void RandomAI::fillStateList(){
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
	void RandomAI::fillCommandList() {
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
			int px = jeu->selectedUnit->position.getX();
			int py = jeu->selectedUnit->position.getY();
			for (int i=0;i<2;i++) {
				for (int j=0;j<2;j++) {
					state::Unite* ennemi = jeu->etatJeu->getUnite(state::Position(px+1-2*j,py+1-2*i));
					// check if an ennemy is around
					if (ennemi and ennemi->getColor() != jeu->selectedUnit->getColor()) {
						liste_commands.push_back(new engine::AttackUnitCommand(state::Position(px+1-2*j,py+1-2*i)));
					}
				}
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
				// Check if unit can move
				if (unite->can_move) {
					liste_commands.push_back(new engine::SelectUnitCommand(unite->position));
				}
			}
		}
		liste_commands.push_back(new engine::EndTurnCommand());
	}
	void RandomAI::run () {
		int nb_joueurs = jeu->joueurs.size();
		if (jeu->joueurs[jeu->tour%nb_joueurs]->color == color) {
			//It's time to play !
			fillStateList ();
			fillCommandList ();
			// init random number generation
			std::uniform_int_distribution<int> index(0,liste_commands.size()-1);
			// add command
			int id = index(randeng);
			engine->addCommand(liste_commands[id]);
			liste_commands.erase(liste_commands.begin()+id);
		}
	}
	RandomAI::~RandomAI () {
	}
}
