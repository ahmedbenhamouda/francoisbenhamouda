#include "CaptureFlagCommand.h"
#include "DropFlagCommand.h"
#include <iostream>

namespace engine {
	CaptureFlagCommand::CaptureFlagCommand() {
	}
	CaptureFlagCommand::CaptureFlagCommand(state::Position targetPos) {
		this->targetPos = targetPos;
	}
	void CaptureFlagCommand::execute(state::Jeu* jeu, Engine* engine) {
		state::Unite* unite;
		if (jeu->selectedUnit) {
			unite = jeu->selectedUnit;
			targetPos = jeu->selectedUnit->position;
			
		} else {
			unite = jeu->etatJeu->getUnite(targetPos);
		}
		// On vérifie que l'unité ne tente pas de capturer son drapeau sur son QG
		state::Batiment* bat = jeu->etatJeu->getBatiment(targetPos);
		if (bat and bat->getId_b() == 0 and bat->getColor() == unite->getColor()) {
			return;
		}
		state::Flag* flag = jeu->etatJeu->getFlag(targetPos);
		if (flag and not(flag->is_owned)) {
			// Check if it is your flag
			if (flag->color == unite->getColor()) {
				std::cout<<"Your flag has been retrieved."<<std::endl;
			} else {
				std::cout<<"The flag has been captured."<<std::endl;
			}
			// Capture the flag
			unite->has_flag = flag;
			flag->is_owned = true;
		}
	}
	CaptureFlagCommand::~CaptureFlagCommand() {
	}
	state::Position CaptureFlagCommand::getPos() {
		return this->targetPos;
	}
	int CaptureFlagCommand::getId() {
		return this->id;
	}
	void CaptureFlagCommand::Undo(state::Jeu* jeu, Engine* engine){
		DropFlagCommand(targetPos).execute(jeu, engine);
	}
}
