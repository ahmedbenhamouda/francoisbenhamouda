#include "client.h"


namespace render {
	Client::Client() {
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
}
