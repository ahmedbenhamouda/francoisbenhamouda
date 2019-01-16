#include "SelectUnitTypeCommand.h"
#include <iostream>

namespace engine {
	SelectUnitTypeCommand::SelectUnitTypeCommand () {
	}
	SelectUnitTypeCommand::SelectUnitTypeCommand (int unit_id) {
		this->unit_id = unit_id;
	}
	SelectUnitTypeCommand::~SelectUnitTypeCommand () {
	}
	void SelectUnitTypeCommand::execute(state::Jeu* jeu, Engine* engine) {
		jeu->unit_type = unit_id;
	}
	void SelectUnitTypeCommand::Undo(state::Jeu* jeu, Engine* engine) {
		jeu->unit_type = 0;
	}
	state::Position SelectUnitTypeCommand::getPos () {
		// Petite astuce pour obtenir le type d'unité à créer
		return state::Position(unit_id,-1);
	}
	int SelectUnitTypeCommand::getId() {
		return this->id;
	}
	Json::Value SelectUnitTypeCommand::toJson() {
	}
}
