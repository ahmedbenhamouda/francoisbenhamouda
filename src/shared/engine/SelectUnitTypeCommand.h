// Generated by dia2code
#ifndef ENGINE__SELECTUNITTYPECOMMAND__H
#define ENGINE__SELECTUNITTYPECOMMAND__H

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

  /// class SelectUnitTypeCommand - 
  class SelectUnitTypeCommand : public engine::Command {
    // Attributes
  public:
    int unit_id;
    int id     = 9;
    // Operations
  public:
    SelectUnitTypeCommand ();
    SelectUnitTypeCommand (int unit_id);
    void execute (state::Jeu* jeu, Engine* engine);
    state::Position getPos ();
    int getId ();
    ~SelectUnitTypeCommand ();
    void Undo (state::Jeu* jeu, Engine* engine);
    Json::Value toJson ();
    // Setters and Getters
  };

};

#endif
