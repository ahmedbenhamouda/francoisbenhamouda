#include "CaptureFlagCommand.h"
#include <iostream>

namespace engine {
	CaptureFlagCommand::CaptureFlagCommand() {
	}
	void CaptureFlagCommand::execute (state::Jeu* jeu) {
		state::Unite* unite = jeu->selectedUnit;
		state::Flag* flag = jeu->etatJeu->getFlag(unite->position);
		if (flag and not(flag->is_owned)) {
			// Check if it is your flag
			if (flag->color == unite->getColor()) {
				state::Batiment* bat = jeu->etatJeu->getBatiment(unite->position);
				// Check if you flag is in your base
				if (bat and bat->getId_b() == 0 and bat->getColor() == unite->getColor()) {
					std::cout<<"Your flag is ok."<<std::endl;
					return;
				} else {
					std::cout<<"Your flag has been retrieved."<<std::endl;
				}
			} else {
				std::cout<<"The flag has been captured."<<std::endl;
			}
			// Capture the flag
			jeu->selectedUnit->has_flag = flag;
			flag->is_owned = true;
		}
	}
	CaptureFlagCommand::~CaptureFlagCommand() {
	}
	state::Position CaptureFlagCommand::getPos() {
		return state::Position(-1,-1);
	}
	int CaptureFlagCommand::getId() {
		return this->id;
	}
}
