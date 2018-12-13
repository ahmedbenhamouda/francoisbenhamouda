// Generated by dia2code
#ifndef ENGINE__DROPFLAGCOMMAND__H
#define ENGINE__DROPFLAGCOMMAND__H


namespace state {
  class Jeu;
};
namespace engine {
  class Command;
}

#include "Command.h"

namespace engine {

  /// class DropFlagCommand - 
  class DropFlagCommand : public engine::Command {
    // Attributes
  public:
    state::Position targetPos;
    int id     = 7;
    // Operations
  public:
    DropFlagCommand ();
    DropFlagCommand (state::Position targetPos);
    ~DropFlagCommand ();
    void execute (state::Jeu* jeu);
    state::Position getPos ();
    int getId ();
    void Undo (state::Jeu* jeu);
    // Setters and Getters
  };

};

#endif
