#include "AttackUnitCommand.h"
#include <cmath>
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
			}
		}
		jeu->selectedUnit = nullptr;
	}
}
