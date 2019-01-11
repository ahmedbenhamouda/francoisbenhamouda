#include "MoveUnitCommand.h"
#include "CaptureFlagCommand.h"
#include "DropFlagCommand.h"
#include "Engine.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace engine {
	MoveUnitCommand::MoveUnitCommand (state::Position targetPos) {
		this->targetPos = targetPos;
	}
	MoveUnitCommand::~MoveUnitCommand() {
	}
	bool MoveUnitCommand::isLegalMove(state::Jeu* jeu, state::Unite* unite) {
		std::vector<state::Position> moves = unite->getLegalMove(jeu->etatJeu);
		for (state::Position mv : moves) {
			if (targetPos == mv) {
				return true;
			}
		}
		return false;
	}
	void MoveUnitCommand::execute(state::Jeu* jeu, Engine* engine) {
		state::Unite* object = jeu->selectedUnit;
		
		if (object) {
			this->objectPos = jeu->selectedUnit->position;
			if (not(isLegalMove(jeu, object)) or jeu->etatJeu->getUnite(targetPos)) {
				return;
			}
		}

		// Check if unit can move
		if (not(object->can_move)) {
			std::cout<<"This unit cannot move anymore."<<std::endl;
			jeu->selectedUnit = nullptr;
			return;
		}

		//end action
		jeu->selectedUnit->can_move = false;

		// animation
		if (jeu->simulation < 0) {
			while (not (object-> position == targetPos)) {
				int px = object->position.getX();
				int py = object->position.getY();
				int dx = px < targetPos.getX()?1:-1;
				int dy = py < targetPos.getY()?1:-1;
				if (px != targetPos.getX()) {
					object->move(state::Position(px+dx,py));
				} else {
					object->move(state::Position(px,py+dy));
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		} else {
			object->move(targetPos);
		}

		// On vérifie que l'unité se pose sur son QG et possède un drapeau
		state::Batiment* bat = jeu->etatJeu->getBatiment(targetPos);
		if (bat and bat->getId_b() == 0 and bat->getColor() == object->getColor()) {
			engine->addCommand(new DropFlagCommand(object->position));
			engine->update();
		} else {
			// Try to see if there is any flag to capture
			state::Flag* flag = jeu->etatJeu->getFlag(targetPos);
			if (flag and not(flag->is_owned)) {
				engine->addCommand(new CaptureFlagCommand());
				engine->update(); 
			}
		}

		//end action
		jeu->selectedUnit = nullptr;

	}
	void MoveUnitCommand::Undo(state::Jeu* jeu, Engine* engine) {
		state::Unite* object = jeu->etatJeu->getUnite(targetPos);
		jeu->selectedUnit = object;
		
		// Check if there is any flag to capture
		//CaptureFlagCommand().execute(jeu);
		
		// Move the unit to the previous position
		object->can_move = true;
		MoveUnitCommand(objectPos).execute(jeu, engine);
		
		// reset action
		object->can_move = true;
		jeu->selectedUnit = object;
	}
	state::Position MoveUnitCommand::getPos() {
		return this->targetPos;
	}
	int MoveUnitCommand::getId() {
		return this->id;
	}
}
