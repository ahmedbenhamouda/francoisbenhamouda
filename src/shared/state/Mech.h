// Generated by dia2code
#ifndef STATE__MECH__H
#define STATE__MECH__H

#include <vector>

namespace state {
  class Position;
  class Unite;
}

#include "Position.h"
#include "Unite.h"

namespace state {

  /// class Mech - 
  class Mech : public state::Unite {
    // Attributes
  public:
    int vie     = 120;
    int prix     = 3500;
    int mvt     = 3;
    int puissance     = 150;
    // Operations
  public:
    Mech ();
    Mech (Position position, int color);
    std::vector<Position> getLegalMove ();
    ~Mech ();
    // Setters and Getters
  };

};

#endif