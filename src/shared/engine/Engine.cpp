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
		size_t index = 0;
		while (index < commands.size()) {
			commands[index]->execute(jeu, this);
			index++;
		}
		notifyUpdated();
	}
	void Engine::RollBack() {
		if (commands.size()>0) {
			Command* cmd = commands[commands.size()-1];
			commands.pop_back();
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
	void Engine::saveCommand () {
	}
	void Engine::loadCommand () {
	}
}
