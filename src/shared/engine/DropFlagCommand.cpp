#include "DropFlagCommand.h"
#include <iostream>

namespace engine {
	DropFlagCommand::DropFlagCommand() {
	}
	DropFlagCommand::DropFlagCommand(state::Position targetPos) {
		this->targetPos = targetPos;
	}
	void DropFlagCommand::execute (state::Jeu* jeu) {
		state::Unite* unite = jeu->etatJeu->getUnite(targetPos);
		if (unite and unite->has_flag) {
			state::Flag* flag = unite->has_flag;
			flag->position = unite->position;
			flag->is_owned = false;
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
}
