#include "SelectUnitCommand.h"

namespace engine {
	SelectUnitCommand::SelectUnitCommand() {
	}
	SelectUnitCommand::SelectUnitCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
	void SelectUnitCommand::execute(state::Jeu* jeu) {
		state::Unite* unite = jeu->etatJeu->getUnite(objectPos);
		jeu->etatJeu->setUniteMoves(unite->getLegalMove());
	}
	SelectUnitCommand::~SelectUnitCommand() {
	}
}
