#include "Engine.h"
#include <iostream>

namespace engine {
	Engine::Engine(state::Jeu* jeu) {
		this->jeu = jeu;
	}
	Engine::~Engine() {
	}
	void Engine::addCommand (Command* command) {
		commands.push_back(command);
	}
	void Engine::update() {
		if (commands.size()>0) {
			if (latest_command != commands[commands.size()-1]) {
				latest_command = commands[commands.size()-1];
				latest_command->execute(jeu);
			}
		}
	}
	void Engine::RollBack() {
		if (commands.size()>0) {
			std::cout<<"Rollback !"<<std::endl;
			Command* cmd = commands[commands.size()-1];
			cmd->Undo(jeu);
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
