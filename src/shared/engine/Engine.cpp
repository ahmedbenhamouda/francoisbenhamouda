#include "Engine.h"
#include <iostream>

namespace engine {
	Engine::Engine(state::Jeu* jeu) {
		this->jeu = jeu;
	}
	Engine::~Engine() {
	}
	void Engine::addCommand (Command* command) {
		//std::cout<<"addCommand"<<std::endl;
		commands.push_back(command);
		//std::cout<<commands.size()<<std::endl;
	}
	void Engine::update() {
		//std::cout<<"update"<<std::endl;
		for (Command* cmd : commands) {
			cmd->execute(jeu);
			delete cmd;
		}
		commands = std::vector<Command*>();
	}
}
