// Generated by dia2code
#ifndef ENGINE__ATTACKUNITCOMMAND__H
#define ENGINE__ATTACKUNITCOMMAND__H


namespace state {
  class Jeu;
};
namespace engine {
  class Command;
}

#include "Command.h"

namespace engine {

  /// class AttackUnitCommand - 
  class AttackUnitCommand : public engine::Command {
    // Attributes
  public:
    state::Position targetPos;
    int id     = 4;
    // Operations
  public:
    AttackUnitCommand ();
    AttackUnitCommand (state::Position targetPos);
    ~AttackUnitCommand ();
    void execute (state::Jeu* jeu);
    state::Position getPos ();
    // Setters and Getters
  };

};

#endif
