#include "AttackUnitCommand.h"
#include "DeleteUnitCommand.h"
#include "DropFlagCommand.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

namespace engine {
	AttackUnitCommand::AttackUnitCommand (state::Position targetPos) {
		this->targetPos = targetPos;
	}
	AttackUnitCommand::~AttackUnitCommand() {
	}
	void AttackUnitCommand::execute(state::Jeu* jeu) {
		state::Unite* object = jeu->selectedUnit;
		state::Unite* target = jeu->etatJeu->getUnite(targetPos);
		if (object and target) {
			// Own caracter selected
			if (object == target) {
				jeu->etatJeu->uniteMoves = std::vector<state::Position>();
				jeu->selectedUnit = nullptr;
			}
			if (std::fabs((object->position)-(target->position)) == 1){
				// reset unite moves
				jeu->etatJeu->uniteMoves = std::vector<state::Position>();

				// Check if unit can attack
				if (not(jeu->selectedUnit->can_attack)) {
					std::cout<<"This unit cannot attack anymore."<<std::endl;
					jeu->selectedUnit = nullptr;
					return;
				}

				// Check if no friendly fire
				if (object->getColor() == target->getColor()) {
					std::cout<<"Do not betray your comrades."<<std::endl;
					jeu->selectedUnit = nullptr;
					return;
				}

				object->attacker(target);
				int life = target->getvie();
				std::cout<<"Enemy's life : "<<life<<std::endl;
				if (life == 0) {
					DropFlagCommand(targetPos).execute(jeu);
					DeleteUnitCommand(targetPos).execute(jeu);
				}
				// animation
				jeu->etatJeu->explosions.push_back(targetPos);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				jeu->etatJeu->explosions = std::vector<state::Position>();


				// end action
				jeu->selectedUnit->can_attack = false;
				jeu->selectedUnit = nullptr;
				
			} else if (target != object) {
				std::cout<<"You cannot attack an ennemy who is not next to you."<<std::endl;
			}
		}
	}
	state::Position AttackUnitCommand::getPos() {
	}
}
