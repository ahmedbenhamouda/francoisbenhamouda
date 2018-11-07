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
		jeu->etatJeu->deleteUnite(objectPos);
	}
}
