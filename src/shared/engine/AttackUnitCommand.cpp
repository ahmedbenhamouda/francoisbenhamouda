#include "AttackUnitCommand.h"
#include <cmath>
namespace engine {
	AttackUnitCommand::AttackUnitCommand (state::Position objectPos, state::Position targetPos) {
		this->objectPos = objectPos;
		this->targetPos = targetPos;
	}
	AttackUnitCommand::~AttackUnitCommand() {
	}
	void AttackUnitCommand::execute(state::Jeu* jeu) {
		state::Unite* object = jeu->etatJeu->getUnite(objectPos);
		state::Unite* target = jeu->etatJeu->getUnite(objectPos);
		//if (std::fabs((object->position)-(target->position)) == 1){
			object->attacker(target);
		//}
	}
}
