#include "Client.h"

namespace client {
	Client::Client() {
	}
	Client::Client(state::Jeu* jeu) {
		this->jeu = jeu;
		this->engine = new engine::Engine(jeu);
		this->ai1 = new HeuristicAI(jeu->joueurs[0]->color,engine,jeu);
		this->ai2 = new HeuristicAI(jeu->joueurs[2]->color,engine,jeu);
	}
	
	void Client::EngineUpdating(){
		ai1->run();
		ai2->run();
	}
	void Client::EngineUpdated(){
		engine->Clear();
	}
	void Client::run(){
	}
	
	Client::~Client() {
		delete ai1;
		delete ai2;
		delete engine;
	}
}
