// Generated by dia2code
#ifndef ENGINE__SELECTUNITTYPECOMMAND__H
#define ENGINE__SELECTUNITTYPECOMMAND__H


namespace state {
  class Jeu;
};
namespace engine {
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
    ~SelectUnitTypeCommand ();
    void execute (state::Jeu* jeu);
    state::Position getPos ();
    // Setters and Getters
  };

};

#endif