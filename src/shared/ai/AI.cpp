#include "AI.h"
#include "engine/CreateUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/MoveUnitCommand.h"
#include "engine/AttackUnitCommand.h"
#include "engine/EndTurnCommand.h"

namespace ai {
	void AI::fillStateLists(){
		for (state::Unite* unit:jeu->etatJeu->getUniteList()){
			if (color == unit->getColor()){
				liste_unites.push_back(unit);		
			}
		}
		for (state::Batiment* bat:jeu->etatJeu->getBatimentList()){
			if (color == bat->getColor()){
				liste_batiments.push_back(bat);							
			}
		}
	}
	void AI::fillCommandList() {
		// Check for createUnit
		int nb_joueurs = jeu->joueurs.size();
		state::Joueur* currentPlayer = jeu->joueurs[jeu->tour%nb_joueurs];
		// Check if player has enough money
		if (currentPlayer->monnaie.getArgent()>=1000) {
			for (state::Batiment* bat : liste_batiments) {
				// batiment is usine and no unit stands on it
				if (bat->getId_b() == 1 and not(jeu->etatJeu->getBatiment(bat->position))) {
					liste_commands.push_back(new engine::CreateUnitCommand(bat->position, 0));
				}
			}
		}
		if (jeu->selectedUnit) {
			// Check all possible movements
			std::vector<state::Position> moves = jeu->selectedUnit->getLegalMove();
			for (state::Position mv : moves) {
				liste_commands.push_back(new engine::MoveUnitCommand(mv));
			}
			// Check if any attack is possible
			int px = jeu->selectedUnit->position.getX();
			int py = jeu->selectedUnit->position.getY();
			for (int i=0;i<1;i++) {
				for (int j=0;j<2;i++) {
					state::Unite* ennemi = jeu->etatJeu->getUnite(state::Position(px+1-2*j,py+1-2*i));
					// check if an ennemy is around
					if (ennemi and ennemi->getColor() != jeu->selectedUnit->getColor()) {
						liste_commands.push_back(new engine::AttackUnitCommand(state::Position(px+1-2*j,py+1-2*i)));
					}
				}
			}
		} else {
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
}
