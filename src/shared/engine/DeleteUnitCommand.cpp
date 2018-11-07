#include "DeleteUnitCommand.h"

namespace engine {
	DeleteUnitCommand::DeleteUnitCommand () {
	}
	DeleteUnitCommand::DeleteUnitCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
    	DeleteUnitCommand::~DeleteUnitCommand () {
	}
    	void DeleteUnitCommand::execute (state::Jeu* jeu) {
		state::Unite* unit = jeu->etatJeu->getUnite(objectPos);
		delete unit;
		jeu->etatJeu->setUnite(objectPos, nullptr);
	}
}
