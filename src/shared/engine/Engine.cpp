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
		for (Command* cmd : commands) {
			cmd->execute(jeu);
			delete cmd;
		}
		commands = std::vector<Command*>();
	}
}
