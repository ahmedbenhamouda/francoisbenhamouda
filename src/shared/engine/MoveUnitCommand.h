// Generated by dia2code
#ifndef ENGINE__MOVEUNITCOMMAND__H
#define ENGINE__MOVEUNITCOMMAND__H


namespace state {
  class Jeu;
};
namespace engine {
  class Command;
}

#include "Command.h"

namespace engine {

  /// class MoveUnitCommand - 
  class MoveUnitCommand : public engine::Command {
    // Attributes
  public:
    state::Position targetPos;
    int id     = 3;
    // Operations
  public:
    MoveUnitCommand ();
    MoveUnitCommand (state::Position targetPos);
    ~MoveUnitCommand ();
    bool isLegalMove (state::Jeu* jeu, state::Unite* unite);
    void execute (state::Jeu* jeu);
    state::Position getPos ();
    int getId ();
    void Undo ();
    // Setters and Getters
  };

};

#endif
