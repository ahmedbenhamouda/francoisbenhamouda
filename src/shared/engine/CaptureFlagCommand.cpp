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
