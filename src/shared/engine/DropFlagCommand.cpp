#include "DropFlagCommand.h"
#include "CaptureFlagCommand.h"
#include <iostream>

namespace engine {
	DropFlagCommand::DropFlagCommand() {
	}
	DropFlagCommand::DropFlagCommand(state::Position targetPos) {
		this->targetPos = targetPos;
	}
	void DropFlagCommand::execute(state::Jeu* jeu, Engine* engine) {
		state::Unite* unite = jeu->etatJeu->getUnite(targetPos);
		if (unite and unite->has_flag) {
			state::Flag* flag = unite->has_flag;
			flag->position = unite->position;
			flag->is_owned = false;
			unite->has_flag = nullptr;
			std::cout<<"The flag has been dropped."<<std::endl;
		}
	}
	DropFlagCommand::~DropFlagCommand() {
	}
	state::Position DropFlagCommand::getPos() {
		return this->targetPos;
	}
	int DropFlagCommand::getId() {
		return this->id;
	}
	void DropFlagCommand::Undo(state::Jeu* jeu, Engine* engine){
		CaptureFlagCommand(targetPos).execute(jeu, engine);
	}
}
