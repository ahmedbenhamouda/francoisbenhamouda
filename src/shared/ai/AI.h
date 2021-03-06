// Generated by dia2code
#ifndef AI__AI__H
#define AI__AI__H

#include <vector>

namespace engine {
  class Engine;
};
namespace state {
  class Jeu;
};
namespace engine {
  class Command;
}

#include "engine/Command.h"
#include "engine/Engine.h"
#include "state/Jeu.h"

namespace ai {

  /// class AI - 
  class AI {
    // Attributes
  public:
    int color;
    engine::Engine* engine;
    state::Jeu* jeu;
    std::vector<state::Unite*> liste_unites;
    std::vector<state::Batiment*> liste_batiments;
    std::vector<engine::Command*> liste_commands;
    // Operations
  public:
    virtual void fillStateLists ();
    virtual void fillCommandList ();
    virtual void run () = 0;
    virtual ~AI ();
    // Setters and Getters
  };

};

#endif
