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
		//std::cout<<"Capture the flag !"<<std::endl;
		state::Unite* unite;
		if (jeu->selectedUnit) {
			unite = jeu->selectedUnit;
			targetPos = jeu->selectedUnit->position;
			
		} else {
			unite = jeu->etatJeu->getUnite(targetPos);
		}
		
		std::vector<state::Flag*> flag = jeu->etatJeu->getFlag(targetPos);
		
		if (flag.size() != 0){
			for(size_t i=0; i<flag.size(); i++){
				state::Batiment* bat = jeu->etatJeu->getBatiment(targetPos);
				// On vérifie que l'unité ne tente pas de capturer son drapeau sur son QG
				if (not(bat and bat->getId_b() == 0 and bat->getColor() == unite->getColor()) or (flag[i]->color != unite->getColor())) {
					// Check if it is your flag
					if (flag[i]->color == unite->getColor()) {
						
						std::cout<<"Your flag has been retrieved."<<std::endl;
					} else {
						std::cout<<"The flag has been captured."<<std::endl;
					}
					// Capture the flag
					unite->has_flag = flag[i];
					flag[i]->is_owned = true;
				}
			}
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
	Json::Value CaptureFlagCommand::toJson(){
		Json::Value cmd;
		cmd[" Type "]=this->getId();
		cmd[" Position_X "]=this->targetPos.getX();
		cmd[" Position_Y "]=this->targetPos.getY();
		return cmd;
	}
}
