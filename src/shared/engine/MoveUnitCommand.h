// Generated by dia2code
#ifndef ENGINE__MOVEUNITCOMMAND__H
#define ENGINE__MOVEUNITCOMMAND__H

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

  /// class MoveUnitCommand - 
  class MoveUnitCommand : public engine::Command {
    // Attributes
  public:
    state::Position objectPos;
    state::Position targetPos;
    int id     = 3;
    // Operations
  public:
    MoveUnitCommand ();
    MoveUnitCommand (state::Position targetPos);
    ~MoveUnitCommand ();
    bool isLegalMove (state::Jeu* jeu, state::Unite* unite);
    void execute (state::Jeu* jeu, Engine* engine);
    state::Position getPos ();
    int getId ();
    void Undo (state::Jeu* jeu, Engine* engine);
    Json::Value toJson ();
    // Setters and Getters
  };

};

#endif
