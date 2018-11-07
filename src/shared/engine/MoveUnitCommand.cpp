#include "MoveUnitCommand.h"

namespace engine {
	MoveUnitCommand::MoveUnitCommand (state::Position objectPos, state::Position targetPos) {
		this->objectPos = objectPos;
		this->targetPos = targetPos;
	}
	MoveUnitCommand::~MoveUnitCommand() {
	}
	bool MoveUnitCommand::isLegalMove(state::Unite* unite) {
		std::vector<state::Position> moves = unite->getLegalMove();
		for (int i=0; i<moves.size();i++) {
			//if (targetPos == moves[i]) {
			if (targetPos.getX() == moves[i].getX() and targetPos.getY() == moves[i].getY()) {
				return true;
			}
		}
		return false;
	}
	void MoveUnitCommand::execute(state::Jeu* jeu) {
		state::Unite* object = jeu->etatJeu->getUnite(objectPos);
		if (isLegalMove(object)) {
			//object->move(targetPos);
		}
	}
}
