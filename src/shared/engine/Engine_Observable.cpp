#include <stdio.h>
#include "engine.h"

namespace engine{
	Engine_Observable::~Engine_Observable(){
	}
	void Engine_Observable::registerObserver(Engine_Observer* Obs) const{
   		this->observers.push_back(Obs);
	}
	void Engine_Observable::notifyUpdated() const{
		auto beginList = this->observers.begin();
		auto endList = this->observers.end();
		for ( auto k = beginList; k<endList; k++){
			(*k)->engineUpdated();
		}
	}
	void Engine_Observable::notifyUpdating() const{
		auto beginList = this->observers.begin();
		auto endList = this->observers.end();
		for ( auto k = beginList; k<endList; k++){
			(*k)->engineUpdating();
		}
	}
}
