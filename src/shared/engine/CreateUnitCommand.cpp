#include "CreateUnitCommand.h"

namespace engine {
	CreateUnitCommand::CreateUnitCommand() {
	}
	CreateUnitCommand::CreateUnitCommand(state::Position objectPos, int unit_id) {
		this->objectPos = objectPos;
		this->unit_id = unit_id;
	}
	CreateUnitCommand::~CreateUnitCommand() {
	}
	void CreateUnitCommand::execute (state::Jeu* jeu) {
		state::Batiment* usine = jeu->etatJeu->getBatiment(objectPos);
		// TODO : Penser à vérifier si le joueur a l'argent nécessaire
		state::Unite* unite = usine->creerU(unit_id);
		jeu->etatJeu->setUnite(objectPos, unite);
	}
}
