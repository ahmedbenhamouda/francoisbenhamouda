// Generated by dia2code
#ifndef AI__RANDOMAI__H
#define AI__RANDOMAI__H

#include <random>

namespace engine {
  class Engine;
};
namespace state {
  class Jeu;
};
namespace ai {
  class AI;
}

#include "AI.h"

namespace ai {

  /// class RandomAI - 
  class RandomAI : public ai::AI {
    // Attributes
  public:
    std::mt19937 randeng;
    int player_id;
    /// 			
    engine::Engine* engine;
    state::Jeu* jeu;
    // Operations
  public:
    RandomAI ();
    RandomAI (int color, engine::Engine* engine, state::Jeu* jeu);
    void run ();
    ~RandomAI ();
    // Setters and Getters
  };

};

#endif
