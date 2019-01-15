#include "Client.h"
#include "State.h"
#include "Engine.h"
#include "AI.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
/*#include "engine/AttackUnitCommand.h"
#include "engine/SelectUnitCommand.h"
#include "engine/MoveUnitCommand.h"
#include "engine/SelectBatimentCommand.h"
#include "engine/SelectUnitTypeCommand.h"
#include "engine/CreateUnitCommand.h"
#include "engine/EndTurnCommand.h"
#include <memory>
#include <iostream>*/

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
