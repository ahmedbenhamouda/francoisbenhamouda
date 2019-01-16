#include "Client.h"


namespace client {
	Client::Client() {
	}
	Client::Client(state::Jeu* jeu) {
		this->jeu = jeu;
		this->engine = new engine::Engine(jeu);
		this->engine->registerObserver(this);
		this->ai1 = new ai::HeuristicAI(jeu->joueurs[0]->color,engine,jeu);
		this->ai2 = new ai::HeuristicAI(jeu->joueurs[1]->color,engine,jeu);
	}
	
	void Client::engineUpdating(){
		ai1->run();
		ai2->run();
	}
	void Client::engineUpdated(){
		engine->Clear();
	}
	void Client::run(){
		engine->update();
	}
	
	Client::~Client() {
		delete ai1;
		delete ai2;
		delete engine;
	}
}
