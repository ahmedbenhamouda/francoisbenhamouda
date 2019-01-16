// Generated by dia2code
#ifndef ENGINE__CAPTUREFLAGCOMMAND__H
#define ENGINE__CAPTUREFLAGCOMMAND__H

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

  /// class CaptureFlagCommand - 
  class CaptureFlagCommand : public engine::Command {
    // Attributes
  public:
    state::Position targetPos;
    int id     = 6;
    // Operations
  public:
    CaptureFlagCommand ();
    CaptureFlagCommand (state::Position targetPos);
    ~CaptureFlagCommand ();
    void execute (state::Jeu* jeu, Engine* engine);
    state::Position getPos ();
    int getId ();
    void Undo (state::Jeu* jeu, Engine* engine);
    Json::Value toJson ();
    // Setters and Getters
  };

};

#endif
