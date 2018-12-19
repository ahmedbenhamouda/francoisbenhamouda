// Generated by dia2code
#ifndef ENGINE__CAPTUREFLAGCOMMAND__H
#define ENGINE__CAPTUREFLAGCOMMAND__H


namespace state {
  class Jeu;
};
namespace engine {
  class Command;
}

#include "Command.h"

namespace engine {

  /// class CaptureFlagCommand - 
  class CaptureFlagCommand : public engine::Command {
    // Attributes
  public:
    state::Position targetPos;
    int id     = 6;
    // Operations
  public:
    CaptureFlagCommand ();
    ~CaptureFlagCommand ();
    void execute (state::Jeu* jeu);
    state::Position getPos ();
    int getId ();
    void Undo (state::Jeu* jeu);
    // Setters and Getters
  };

};

#endif
