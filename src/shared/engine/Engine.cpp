#include "Engine.h"
#include "Command.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>

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
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
	void Engine::loadCommand() {
		std::ifstream fichier("replay.txt", std::ios::in);
		if (fichier) {
			std::string json_str;
			fichier>>json_str;
			record = Json::Value(json_str);
		} else {
			std::cerr<<"Pas de fichier \"replay.txt\""<<std::endl;
		}
		for (Json::Value cmd : record) {
			if (cmd[" Type "] == 8) commands.push_back(new EndTurnCommand());
			else if (cmd[" Type "] == 9) commands.push_back(new SelectUnitTypeCommand((int)cmd[" Unite "]));
			else {
				state::Position pos((int)cmd[" Position_X "],(int)cmd[" Position_X "]);
				if (cmd[" Type "] == 0) commands.push_back(new CreateUnitCommand(pos));
				if (cmd[" Type "] == 1) commands.push_back(new DeleteUnitCommand(pos));
				if (cmd[" Type "] == 2) commands.push_back(new SelectUnitCommand(pos));
				if (cmd[" Type "] == 3) commands.push_back(new MoveUnitCommand(pos));
				if (cmd[" Type "] == 4) commands.push_back(new AttackUnitCommand(pos));
				if (cmd[" Type "] == 5) commands.push_back(new SelectBatimentCommand(pos));
				if (cmd[" Type "] == 6) commands.push_back(new CaptureFlagCommand(pos));
				if (cmd[" Type "] == 7) commands.push_back(new DropFlagCommand(pos));
			}
		}
	}
}
