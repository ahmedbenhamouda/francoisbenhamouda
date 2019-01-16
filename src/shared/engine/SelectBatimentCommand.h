// Generated by dia2code
#ifndef ENGINE__SELECTBATIMENTCOMMAND__H
#define ENGINE__SELECTBATIMENTCOMMAND__H

#include <json/json.h>

namespace state {
  class Jeu;
};
namespace engine {
  class Engine;
  class Command;
}

#include "Command.h"

namespace engine {

  /// class SelectBatimentCommand - 
  class SelectBatimentCommand : public engine::Command {
    // Attributes
  public:
    state::Position objectPos;
    int id     = 5;
    // Operations
  public:
    SelectBatimentCommand ();
    SelectBatimentCommand (state::Position objectPos);
    ~SelectBatimentCommand ();
    void execute (state::Jeu* jeu, Engine* engine);
    state::Position getPos ();
    int getId ();
    void Undo (state::Jeu* jeu, Engine* engine);
    Json::Value toJson ();
    // Setters and Getters
  };

};

#endif
