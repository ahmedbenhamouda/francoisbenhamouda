// Generated by dia2code
#ifndef RENDER__BATIMENTTILESET__H
#define RENDER__BATIMENTTILESET__H

#include <vector>
#include <string>

namespace render {
  class Tile;
  class TileSet;
}

#include "Tile.h"
#include "TileSet.h"

namespace render {

  /// class BatimentTileSet - 
  class BatimentTileSet : public render::TileSet {
    // Attributes
  private:
    std::vector<Tile> batiments;
    // Operations
  public:
    BatimentTileSet ();
    ~BatimentTileSet ();
    int const getWidth ();
    int const getHeigth ();
    std::string const getImageFile ();
    // Setters and Getters
  };

};

#endif