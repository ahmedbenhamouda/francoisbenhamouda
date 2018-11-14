#include "MoveUnitCommand.h"
#include "CaptureFlagCommand.h"
#include "DropFlagCommand.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace engine {
	MoveUnitCommand::MoveUnitCommand (state::Position targetPos) {
		this->targetPos = targetPos;
	}
	MoveUnitCommand::~MoveUnitCommand() {
	}
	bool MoveUnitCommand::isLegalMove(state::Unite* unite) {
		std::vector<state::Position> moves = unite->getLegalMove();
		for (state::Position mv : moves) {
			if (targetPos == mv) {
			//if (targetPos.getX() == moves[i].getX() and targetPos.getY() == moves[i].getY()) {
				return true;
			}
		}
		return false;
	}
	void MoveUnitCommand::execute(state::Jeu* jeu) {
		state::Unite* object = jeu->selectedUnit;
		if (object) {
			if (not(isLegalMove(object)) or jeu->etatJeu->getUnite(targetPos)) {
				return;
			}
		}
		jeu->etatJeu->uniteMoves = std::vector<state::Position>(); // reset unite moves

		// Check if unit can move
		if (not(object->can_move)) {
			std::cout<<"This unit cannot move anymore."<<std::endl;
			jeu->selectedUnit = nullptr;
			return;
		}

		// animation
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
		// Check if the flag has been sent to a HQ
		state::Batiment* bat = jeu->etatJeu->getBatiment(targetPos);
		if (bat and bat->getId_b() == 0) {
			DropFlagCommand(object->position).execute(jeu);
		}
		CaptureFlagCommand().execute(jeu);

		//end action
		jeu->selectedUnit->can_move = false;
		jeu->selectedUnit = nullptr;
	}
}
