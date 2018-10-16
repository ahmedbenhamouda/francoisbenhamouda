// Generated by dia2code
#ifndef STATE__BATIMENT__H
#define STATE__BATIMENT__H

#include <string>

namespace state {
  class Position;
  class Terrain;
}

#include "Position.h"

namespace state {

  /// class Batiment - 
  class Batiment {
    // Associations
    // Attributes
  public:
    Position position;
    int color;
    // Operations
  public:
    Batiment ();
    Batiment (Position position, int color);
    void creerU (int argent, std::string typeUnite, Terrain& terrain);
    ~Batiment ();
    // Setters and Getters
  };

};

#endif