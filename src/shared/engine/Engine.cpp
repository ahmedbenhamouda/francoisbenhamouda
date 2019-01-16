#include "Engine.h"
#include "Command.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

namespace engine {
	Engine::Engine(state::Jeu* jeu) {
		this->jeu = jeu;
	}
	Engine::~Engine() {
	}
	void Engine::addCommand (Command* command) {
		record.append(command->toJson());
		commands.push_back(command);
		/*if (jeu->simulation == -1) {
			std::cout<<"Command received with id : "<<command->getId()<<std::endl;
		}*/
	}
	void Engine::update() {
		
		if (commands.size()==0) notifyUpdating();
		size_t index = 0;
		
		while (index < commands.size()) {
			commands[index]->execute(jeu, this);
			index++;
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
	void Engine::saveCommand() {
		std::ofstream fichier("replay.txt", std::ios::out|std::ios::out);
		if (fichier) {
			fichier<<record.toStyledString();
			fichier.close();
		} else {
			std::cerr<<"Pas de fichier \"replay.txt\""<<std::endl;
		}
		//record["commands"] = Json::Value::Array(json_commands);
	}
}
