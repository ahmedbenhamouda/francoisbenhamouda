// Generated by dia2code
#ifndef STATE__JOUEUR__H
#define STATE__JOUEUR__H


namespace state {
  class PorteMonnaie;
}

#include "PorteMonnaie.h"

namespace state {

  /// class Joueur - 
  class Joueur {
    // Associations
    // Attributes
  public:
    int color;
    PorteMonnaie monnaie;
    bool is_AI;
    // Operations
  public:
    Joueur ();
    Joueur (int color, bool is_AI);
    ~Joueur ();
    // Setters and Getters
  };

};

#endif