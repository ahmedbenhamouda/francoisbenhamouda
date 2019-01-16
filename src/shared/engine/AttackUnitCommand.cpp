#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include "Engine.h"
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
	void AttackUnitCommand::execute(state::Jeu* jeu, Engine* engine) {
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
				
				jeu->selectedUnit->can_attack = false;
				
				// Get the position of the attacker
				this->objectPos = jeu->selectedUnit->position;
				
				// Get the information on the target
				this->target_life = target->getvie();
				this->target_power = target->getpuissance();
				
				object->attacker(target);
				int life = target->getvie();
				std::cout<<"Enemy's life : "<<life<<std::endl;
				
				/*// Get points for attacking
				if (jeu->simulation>=0 and jeu->selectedUnit->color != jeu->joueurs[jeu->simulation]->color) { // The simulating IA is being attacked
					jeu->joueurs[jeu->simulation]->score -= 2;
				}*/
				
				if (life == 0) {
					/*// Get additional points for killing
					if (jeu->simulation>=0 and jeu->selectedUnit->color != jeu->joueurs[jeu->simulation]->color) { // The simulating IA is being attacked
						jeu->joueurs[jeu->simulation]->score -= 4;
					}*/
					
					engine->addCommand(new DropFlagCommand(targetPos));
					//engine->update();
					engine->addCommand(new DeleteUnitCommand(targetPos));
					//engine->update();
				}

				// end action
				jeu->selectedUnit = nullptr;

				// animation
				if (jeu->simulation < 0) {
					jeu->etatJeu->explosions.push_back(targetPos);
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					jeu->etatJeu->explosions = std::vector<state::Position>();
				}


				
			} else if (target != object) {
				std::cout<<"You cannot attack an ennemy who is not next to you."<<std::endl;
			}
		}
	}
	void AttackUnitCommand::Undo(state::Jeu* jeu, Engine* engine) {
		state::Unite* object = jeu->etatJeu->getUnite(objectPos);
		
		// Check if any unit was attacked
		if (not(object)) {
			return;
		}
		
		jeu->selectedUnit = object;
		object->can_attack = true;
		state::Unite* target = jeu->etatJeu->getUnite(targetPos);
		target->setpuissance(target_power);
		target->setvie(target_life);
	} 
	state::Position AttackUnitCommand::getPos() {
		return this->targetPos;
	}
	int AttackUnitCommand::getId() {
		return this->id;
	}
	Json::Value AttackUnitCommand::toJson(){
		Json::Value cmd;
		cmd[" Type "]=this->getId();
		cmd[" Position_X "]=this->targetPos.getX();
		cmd[" Position_Y "]=this->targetPos.getY();
		return cmd;
	}
}
