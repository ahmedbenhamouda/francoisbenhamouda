#include "Engine.h"
#include "Command.h"
#include <iostream>

namespace engine {
	Engine::Engine(state::Jeu* jeu) {
		commands = std::vector<Command*>();
		this->jeu = jeu;
	}
	Engine::~Engine() {
	}
	void Engine::addCommand (Command* command) {
		commands.push_back(command);
		/*if (jeu->simulation == -1) {
			std::cout<<"Command received with id : "<<command->getId()<<std::endl;
		}*/
	}
	void Engine::update() {
		if (commands.size()>0) {
			if (not(latest_command) or latest_command != commands[commands.size()-1]) {
				latest_command = commands[commands.size()-1];
				latest_command->execute(jeu, this);
				/*if (jeu->simulation == -1) {
					std::cout<<"Command executed with id "<<commands[commands.size()-1]->getId()<<std::endl;
					std::cout<<"Position : x="<<commands[commands.size()-1]->getPos().getX()<<", y="<<commands[commands.size()-1]->getPos().getY()<<std::endl;
				}*/
			}
		} else {
			latest_command = 0;
		}
	}
	void Engine::RollBack() {
		if (commands.size()>0) {
			Command* cmd = commands[commands.size()-1];
			//std::cout<<"Rollback command "<<cmd<<" with id : "<<cmd->getId()<<std::endl;
			cmd->Undo(jeu, this);
			delete cmd;
			commands.pop_back();
		}
	}
	void Engine::Clear() {
		for (Command* cmd : commands) {
			delete cmd;
		}
		commands = std::vector<Command*>();
	}
}
