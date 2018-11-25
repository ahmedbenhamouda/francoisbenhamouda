#include "DeleteUnitCommand.h"
#include <iostream>

namespace engine {
	DeleteUnitCommand::DeleteUnitCommand () {
	}
	DeleteUnitCommand::DeleteUnitCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
    	DeleteUnitCommand::~DeleteUnitCommand () {
	}
    	void DeleteUnitCommand::execute (state::Jeu* jeu) {
		std::cout<<"Unit died !"<<std::endl;
		jeu->etatJeu->deleteUnite(objectPos);
	}
	state::Position DeleteUnitCommand::getPos() {
		return this->objectPos;
	}
	int DeleteUnitCommand::getId() {
		return this->id;
	}
}
