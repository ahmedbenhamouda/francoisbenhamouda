// Generated by dia2code
#ifndef STATE__HTANK__H
#define STATE__HTANK__H

#include <vector>

namespace state {
  class Position;
  class Unite;
}

#include "Position.h"
#include "Unite.h"

namespace state {

  /// class HTank - 
  class HTank : public state::Unite {
    // Attributes
  public:
    int vie     = 250;
    int prix     = 10000;
    int mvt     = 2;
    int puissance     = 200;
    // Operations
  public:
    HTank ();
    HTank (Position position, int color);
    std::vector<Position> getLegalMove ();
    ~HTank ();
    // Setters and Getters
  };

};

#endif