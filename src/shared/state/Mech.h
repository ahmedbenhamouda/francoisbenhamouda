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
    int id     = 1;
    // Operations
  public:
    Mech ();
    Mech (Position position, int color);
    std::vector<Position> getLegalMove ();
    int getvie ();
    int getprix ();
    int getmvt ();
    int getpuissance ();
    int getId ();
    int getColor ();
    int getTileId ();
    void setvie (int v);
    void attacker (Unite* unite);
    void setpuissance (int p);
    ~Mech ();
    void move (Position position);
    // Setters and Getters
  };

};

#endif
