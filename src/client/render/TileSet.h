// Generated by dia2code
#ifndef RENDER__TILESET__H
#define RENDER__TILESET__H

#include <string>

namespace render {
  class Tile;
}

#include "Tile.h"

namespace render {

  /// class TileSet - 
  class TileSet {
    // Associations
    // Operations
  public:
    TileSet ();
    ~TileSet ();
    int const getCellWidth ();
    int const getCellHeigth ();
    std::string const getImageFile ();
    // Setters and Getters
  };

};

#endif