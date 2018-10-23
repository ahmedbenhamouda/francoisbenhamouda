
#ifndef RENDER__TILESET__H
#define RENDER__TILESET__H

#include <string>
#include <vector>

namespace render {
  class Tile;
}

#include "Tile.h"

namespace render {

  /// class TileSet - 
  template <  class T>
  class TileSet {
    // Associations
    // Attributes
    std::vector<Tile> tiles;
    std::string filename;
  public:
    T t;
    // Operations
  public:
    TileSet (std::string filename);
    int const getCellWidth ();
    int const getCellHeight ();
    std::string const getImageFile ();
    Tile& getTile (T& t);
    // Setters and Getters
  };

template<class T>
TileSet<T>::TileSet (std::string filename) : filename(filename) {
    // peuplement de tiles

}

template<class T>
Tile& TileSet<T>::getTile(T& t) {
    int i = t;
    return this->tiles[i];
};

#endif
