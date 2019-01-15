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
		notifyUpdating();
		if (commands.size()>0) {
			//std::cout<<" -- Update de l'engine"<<std::endl;
			if (not(latest_command) or latest_command != commands[commands.size()-1]) {
				latest_command = commands[commands.size()-1];
				//std::cout<<" -- Execution de la commande "<<latest_command<<" dont l'ID est : "<<latest_command->getId()<<std::endl;
				latest_command->execute(jeu, this);
				/*if (jeu->simulation == -1) {
					std::cout<<"Command executed with id "<<commands[commands.size()-1]->getId()<<std::endl;
					std::cout<<"Position : x="<<commands[commands.size()-1]->getPos().getX()<<", y="<<commands[commands.size()-1]->getPos().getY()<<std::endl;
				}*/
				//std::cout<<" -- Execution de la commande : fait"<<std::endl;
			}
		} else {
			latest_command = 0;
		}
		notifyUpdated();
	}
	void Engine::RollBack() {
		if (commands.size()>0) {
			Command* cmd = commands[commands.size()-1];
			commands.pop_back();
			//std::cout<<"Rollback command "<<cmd<<" with id : "<<cmd->getId()<<std::endl;
			cmd->Undo(jeu, this);
			delete cmd;
		}
	}
	void Engine::Clear() {
		for (Command* cmd : commands) {
			delete cmd;
		}
		commands = std::vector<Command*>();
	}
}
