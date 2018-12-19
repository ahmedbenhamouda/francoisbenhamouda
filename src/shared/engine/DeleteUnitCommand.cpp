#include "DeleteUnitCommand.h"
#include "state/Unite.h"
#include "state/Infantry.h"
#include "state/Mech.h"
#include "state/Recon.h"
#include "state/Tank.h"
#include "state/HTank.h"
#include <iostream>

namespace engine {
	DeleteUnitCommand::DeleteUnitCommand () {
	}
	DeleteUnitCommand::DeleteUnitCommand (state::Position objectPos) {
		this->objectPos = objectPos;
	}
    	DeleteUnitCommand::~DeleteUnitCommand () {
	}
    	void DeleteUnitCommand::execute (state::Jeu* jeu) {
    		std::cout<<"Delete unit"<<std::endl;
		//this->target_type = target->getId();	
		//this->target_color = target->getColor();
		//std::cout<<"Unit died !"<<std::endl;
		jeu->etatJeu->deleteUnite(objectPos);
	}
	state::Position DeleteUnitCommand::getPos() {
		return this->objectPos;
	}
	int DeleteUnitCommand::getId() {
		return this->id;
	}
	void DeleteUnitCommand::Undo(state::Jeu* jeu){
		std::cout<<"Cancel delete unit"<<std::endl;
		state::Unite* target;
		if (target_type == 1) {
			target = new state::Mech(objectPos, target_color);
		} else if (target_type == 2) {
			target = new state::Recon(objectPos, target_color);
		} else if (target_type == 3) {
			target = new state::Tank(objectPos, target_color);
		} else if (target_type == 4) {
			target = new state::HTank(objectPos, target_color);
		} else {
			target = new state::Infantry(objectPos, target_color);
		}
		// Apply information on target 
		target->setvie(0);
		target->setpuissance(0);		
		// Place new unit to Terrain
		jeu->etatJeu->addUnite(target);
		// Check if dead unit had any flag
		state::Flag* flag = jeu->etatJeu->getFlag(objectPos);
		if (flag) {
			flag->is_owned = true;
			target->has_flag = flag;
		}
	}
}
