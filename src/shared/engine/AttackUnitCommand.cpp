#include "AttackUnitCommand.h"
#include "DeleteUnitCommand.h"
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
		jeu->etatJeu->setUniteMoves(std::vector<state::Position>()); // reset unite moves
		if (object and target) {
			if (std::fabs((object->position)-(target->position)) == 1){
				object->attacker(target);
				int life = target->getvie();
				std::cout<<"Enemy's life : "<<life<<std::endl;
				if (life == 0) {
					DeleteUnitCommand(targetPos).execute(jeu);
				}
				// animation
				jeu->etatJeu->explosions.push_back(targetPos);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				jeu->etatJeu->explosions = std::vector<state::Position>();
				
			} else {
				std::cout<<"You cannot attack an ennemy who is not next to you."<<std::endl;
			}
		}
		jeu->selectedUnit = nullptr;
	}
}
