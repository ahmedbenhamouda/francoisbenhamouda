// Generated by dia2code
#ifndef STATE__USINE__H
#define STATE__USINE__H


namespace state {
  class Position;
  class Unite;
  class Batiment;
}

#include "Position.h"
#include "Batiment.h"

namespace state {

  /// class Usine - 
  class Usine : public state::Batiment {
    // Attributes
  public:
    int id_b     = 1;
    // Operations
  public:
    Usine ();
    Usine (Position position, int color);
    Unite* creerU (int id);
    int getId_b ();
    int getColor ();
    int getTileId ();
    ~Usine ();
    // Setters and Getters
  };

};

#endif
