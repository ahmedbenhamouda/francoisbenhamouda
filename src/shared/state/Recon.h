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
    int puissance     = 80;
    int id     = 1;
    // Operations
  public:
    Recon ();
    Recon (Position position, int color);
    std::vector<Position> getLegalMove ();
    int getvie ();
    int getprix ();
    int getmvt ();
    int getpuissance ();
    int getId ();
    int getColor ();
    int getTileId ();
    void attacker (Unite* unite);
    void setvie (int v);
    void setpuissance (int p);
    ~Recon ();
    // Setters and Getters
  };

};

#endif
