// Generated by dia2code
#ifndef STATE__RECON__H
#define STATE__RECON__H

#include <vector>

namespace state {
  class Position;
  class Unite;
}

#include "Position.h"
#include "Unite.h"

namespace state {

  /// class Recon - 
  class Recon : public state::Unite {
    // Attributes
  public:
    int vie     = 150;
    int prix     = 4500;
    int mvt     = 4;
    int puissance;
    // Operations
  public:
    Recon (Position position, int color);
    std::vector<Position> getLegalMove ();
    // Setters and Getters
  };

};

#endif
