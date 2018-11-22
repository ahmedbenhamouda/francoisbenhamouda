#include "SelectUnitTypeCommand.h"

namespace engine {
	SelectUnitTypeCommand::SelectUnitTypeCommand () {
	}
	SelectUnitTypeCommand::SelectUnitTypeCommand (int unit_id) {
		this->unit_id = unit_id;
	}
	SelectUnitTypeCommand::~SelectUnitTypeCommand () {
	}
	void SelectUnitTypeCommand::execute (state::Jeu* jeu) {
		jeu->unit_type = unit_id;
	}
	state::Position SelectUnitTypeCommand::getPos () {
	}
}
