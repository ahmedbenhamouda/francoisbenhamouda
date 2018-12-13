#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include "AttackUnitCommand.h"
#include "DeleteUnitCommand.h"
#include "DropFlagCommand.h"
#include "state/Unite.h"
#include "state/Infantry.h"
#include "state/Mech.h"
#include "state/Recon.h"
#include "state/Tank.h"
#include "state/HTank.h"

namespace engine {
	AttackUnitCommand::AttackUnitCommand (state::Position targetPos) {
		this->targetPos = targetPos;
		this->target_life = 0;
	}
	AttackUnitCommand::~AttackUnitCommand() {
	}
	void AttackUnitCommand::execute(state::Jeu* jeu) {
		state::Unite* object = jeu->selectedUnit;
		state::Unite* target = jeu->etatJeu->getUnite(targetPos);
		if (object and target) {
			// Own caracter selected
			if (object == target) {
				jeu->selectedUnit = nullptr;
			}
			if (std::fabs((object->position)-(target->position)) == 1){
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
				// Get the information on the target
				this->target_life = target->getvie();
				this->target_color = target->getColor();
				this->target_power = target->getpuissance();
				this->target_type = target->getId();
				
				object->attacker(target);
				int life = target_life;
				std::cout<<"Enemy's life : "<<life<<std::endl;
				if (life == 0) {
					DropFlagCommand(targetPos).execute(jeu);
					DeleteUnitCommand(targetPos).execute(jeu);
				}

				// end action
				jeu->selectedUnit->can_attack = false;
				jeu->selectedUnit = nullptr;

				// animation
				jeu->etatJeu->explosions.push_back(targetPos);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				jeu->etatJeu->explosions = std::vector<state::Position>();


				
			} else if (target != object) {
				std::cout<<"You cannot attack an ennemy who is not next to you."<<std::endl;
			}
		}
	}
	void AttackUnitCommand::Undo(state::Jeu* jeu) {
		// Check if any unit was attacked
		if (target_life == 0) {
			return;
		}
		state::Unite* object = jeu->etatJeu->getUnite(objectPos);
		jeu->selectedUnit = object;
		object->can_attack = true;
		
		// Check if enemy unit was killed
		if (not(jeu->etatJeu->getUnite(targetPos)) {
			state::Unite* unite;
			if (target_type == 0) {
				unite = new state::Infantry(targetPos, target_color);
			}
			if (target_type == 1) {
				unite = new state::Mech(targetPos, target_color);
			}
			if (target_type == 2) {
				unite = new state::Recon(targetPos, target_color);
			}
			if (target_type == 3) {
				unite = new state::Tank(targetPos, target_color);
			}
			if (target_type == 3) {
				unite = new state::HTank(targetPos, target_color);
			}
		}
		// TODO : la suite
	} 
	state::Position AttackUnitCommand::getPos() {
		return this->targetPos;
	}
	int AttackUnitCommand::getId() {
		return this->id;
	}
}
