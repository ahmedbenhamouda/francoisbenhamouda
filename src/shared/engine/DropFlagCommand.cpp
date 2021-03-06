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
		if (unite and unite->has_flag) { // On vérifie quand-même que l'unité possède un drapeau
			state::Flag* flag = unite->has_flag;
			flag->position = unite->position;
			flag->is_owned = false;
			unite->has_flag = nullptr;
			std::cout<<"The flag has been dropped."<<std::endl;
			state::Batiment* bat = jeu->etatJeu->getBatiment(targetPos);
			if (bat and bat->color != flag->color) {
				jeu->fin = true;
				std::cout<<"End of game !"<<std::endl;
			}
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
	Json::Value DropFlagCommand::toJson(){
		Json::Value cmd;
		cmd[" Type "]=this->getId();
		cmd[" Position_X "]=this->targetPos.getX();
		cmd[" Position_Y "]=this->targetPos.getY();
		return cmd;
	}
}
