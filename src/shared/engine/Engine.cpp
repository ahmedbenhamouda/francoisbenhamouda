#include "Engine.h"

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
		for (int i=0; i<commands.size(); i++) {
			commands[i]->execute(jeu);
		}
	}
}
