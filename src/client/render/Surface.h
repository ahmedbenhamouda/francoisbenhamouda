#ifndef RENDER__SURFACE__H
#define RENDER__SURFACE__H

#include <SFML/Graphics.hpp>
#include <string>

namespace sf {
  class Texture;
  class VertexArray;
};
namespace render {
  class Tile;
};
namespace sf {
  class Drawable;
  class Transformable;
}

#include "Tile.h"

namespace render {

  /// class Surface - 
  class Surface : public sf::Drawable, public sf::Transformable {
    // Associations
    // Attributes
  private:
    sf::Texture texture;
    sf::VertexArray quads;
    // Operations
  public:
    Surface ();
    ~Surface ();
    void loadTexture (std::string image_file);
    void initQuads (int count);
    void setSpriteLocation (int posx, int posy, int map_size, int tile_size);
    void setSpriteTexture (int posx, int posy, int map_size, const Tile& tex);
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
    // Setters and Getters
  };

};

#endif
