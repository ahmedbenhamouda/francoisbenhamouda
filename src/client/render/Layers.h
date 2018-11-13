// Generated by dia2code
#ifndef RENDER__LAYERS__H
#define RENDER__LAYERS__H

#include <SFML/Graphics.hpp>

namespace state {
  class Jeu;
};
namespace engine {
  class Engine;
};
namespace render {
  class Surface;
};
class Tileset;
#include "Surface.h"
#include "engine/Engine.h"
#include "state/Jeu.h"
#include "Tileset.h"

namespace render {

  /// class Layers - 
  class Layers {
    // Associations
    // Attributes
  public:
    state::Jeu* jeu;
    engine::Engine* engine;
    Surface uniteSurface;
    Tileset<state::Unite>* uniteTileset;
    Surface batimentSurface;
    Tileset<state::Batiment>* batimentTileset;
    Surface terrainSurface;
    Tileset<state::TerrainTile>* terrainTileset;
    Surface miscSurface;
    Tileset<state::MiscTile>* miscTileset;
    // Operations
  public:
    Layers ();
    Layers (state::Jeu* jeu, engine::Engine* engine, Tileset<state::Unite>* uniteTileset, Tileset<state::Batiment>* batimentTileset, Tileset<state::TerrainTile>* terrainTileset, Tileset<state::MiscTile>* miscTileset);
    ~Layers ();
    void setUniteSurface ();
    void setBatimentSurface ();
    void setTerrainSurface ();
    void setMiscSurface ();
    void displayLayers (sf::RenderWindow* window);
    void sendUnitCommand (state::Position position);
    void sendTurnCommand ();
    // Setters and Getters
  };

};

#endif
