// Generated by dia2code
#ifndef STATE__TERRAINTILE__H
#define STATE__TERRAINTILE__H


#include "TerrainTypeId.h"

namespace state {

  /// class TerrainTile - 
  class TerrainTile {
    // Associations
    // Attributes
  public:
    TerrainTypeId terraintypeid;
    // Operations
  public:
    TerrainTile ();
    int getTileId ();
    ~TerrainTile ();
    TerrainTile (TerrainTypeId tti);
    // Setters and Getters
  };

};

#endif
