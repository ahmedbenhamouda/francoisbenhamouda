// Generated by dia2code
#ifndef ENGINE__COMMAND__H
#define ENGINE__COMMAND__H


namespace state {
  class Jeu;
}

#include "state/Jeu.h"

namespace engine {

  /// class Command - 
  class Command {
    // Operations
  public:
    Command ();
    virtual ~Command ();
    virtual void execute (state::Jeu* jeu) = 0;
    // Setters and Getters
  };

};

#endif
